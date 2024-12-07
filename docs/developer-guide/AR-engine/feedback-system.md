# Feedback system

![Dataflow for the functioning of the Augmented Carpentry's feedback system. ><](../../assets/images/AR_engine/fig_feedback-sys.svg){align=center width=100% style='fill-color: #000000; filter: invert(100%);'}

<br>

The [`LayerFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/LayerFeedback.h) module handles the computation of all essential data required to deliver visual guidance to the user during the fabrication process. To compute feedback, information is primarily retrieved from two preceding layers: 

1. [`LayerModel.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/LayerModel.h): Contains the execution model and the geometries associated with the currently active hole or cut (via `AC_FF_COMP` macro).
2. [`LayerToolhead.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/LayerToolhead.h): Provides similar information, but specific to the current toolhead attached to the tool (via `AC_FF_TOOL` macro).

The [LayerFeedback::OnFrameStart()](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/LayerFeedback.cpp#L23-L54) from the [`LayerFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/LayerFeedback.h) simply activates the feedback set based on the correct toolhead based on the current fabrication element.

| Toolhead       | Hole           | Cut            |
| -------------- | -------------- | -------------- |
| Chainsaw       | ❌             | ✅            |
| Circualr Saw   | ❌             | ✅            |
| Drill meshes   | ✅             | ❌            |

Once the correct feedback is indetified, we have all the geometries of the joint or hole we are working on, as well as the geometries of the toolhead attached to the tool, we can compute all the relevant computations to build the feedback set: starting distance, depth, orientation, etc. In the layer [`LayerFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/LayerFeedback.h) not only we calculate these values but we generate all the necessary [GOs](geometry-framework.md) to visualize them in the AR scene.

## `FabFeedback` interface

Feedback is categorized by similar operations:

- drilling ([`HoleFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Feedback/HoleFeedback.h)),
- circular cutting ([`CutCircularSawFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Feedback/CutCircularSawFeedback.h)),
- and chainsaw cutting ([`CutChainSawFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Feedback/CutChainSawFeedback.h)).

Each feedback category inherits from an interface class ([`AIAC/Feedback/FabFeedback.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Feedback/FabFeedback.h)), which provides top-level control functions such as `Update()`, `Activate()`, and `Deactivate()`.


``` cpp title="src/AIAC/Feedback/FabFeedback.h" linenums="1"  hl_lines="5-6 16-18"
--8<-- "src/AIAC/Feedback/FabFeedback.h"
```

!!! Tip
    The `Update()` function is called at each frame to update the feedback data, while `Activate()` and `Deactivate()` are used to enable/disable the feedback visualization.


## `FeedbackVisualizer` widgets
<!-- TODO: correct this paragraph -->
Each tool's visual guidance might consists of multiple visual cues, most of which are built on the template [`FeedbackVisualizer.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Feedback/FeedbackVisualizer.h). All the feedback values are computed but also visualized as GOs, and stored inside (`m_AllPrimitives`). This is convinient as we can easily toggle the visibility of the feedback by calling the `Activate()`/`Deactivate()` functions.

``` cpp title="src/AIAC/Feedback/FeedbackVisualizer.h" linenums="1"  hl_lines="15-19 21-25 30"
#ifndef AC_FEEDBACKVISUALIZER_H
#define AC_FEEDBACKVISUALIZER_H

#include "vector"
#include "memory"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC{
    class FeedbackVisualizer {
    public:
        FeedbackVisualizer() = default;
        ~FeedbackVisualizer() = default;

        inline virtual void Activate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(true);
            }
        }

        inline virtual void Deactivate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(false);
            }
        }

        // ...

    protected:
        std::vector<std::shared_ptr<GOPrimitive>> m_AllPrimitives;
    };

}
```

!!! Example
    As an example, the circular saw feedback has several `VisualFeedback` classes that inherit from `FeedbackVisualizer` to manage the visualization of the feedback. In the case of the circular saw, we have the following `VisualFeedback` classes:

    | VisualFeedback class | Description |
    |----------------------|-------------|
    | [`class CutCircularSawDepthVisualizer`](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/Feedback/CutCircularSawFeedback.h#L22C5-L22C40) | it visualizes the height of the blade in relation to the lap joint |
    | [`class CutCircularSawPositionStartVisualizer`](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/Feedback/CutCircularSawFeedback.h#L42C11-L42C48) | it visualizes the starting position of the cut as a text in millimeters and as a green line for graphical correction |
    | [`class CutCircularOrientationVisualizer`](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/Feedback/CutCircularSawFeedback.h#L66C5-L66C43) | it visualizes the correct orientation of the cut as a text in millimeters and as a green line for graphical correction |
    | [`class CircularSawCutPlaneVisualizer : public CutPlaneVisualizer`](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/Feedback/CutCircularSawFeedback.h#L92C5-L92C68) | in this case it still inherits from `FeedbackVisualizer` the `CutPlaneVisualizer`, but since it is employed also by other tools (e.g. chainsaw), the sub-class already presents some common parameters and visual cues for the plane corresponding to the blade |
    | [`class CircularSawCutBladeThicknessVisualizer`](https://github.com/ibois-epfl/augmented-carpentry/blob/1ba7928970b9dfe6bbe2e32b8321b5dcfddf5ac4/src/AIAC/Feedback/CutCircularSawFeedback.h#L105C5-L105C49) | it visualizes the thickness of the blade as two red lines |

    All the `VisualFeedback` are not active all the time at the same time during a fabrication. Depending on which scenario is detected, they are activated (visible) or deactivated (not visible).

    Here's an example of the `CutCircularSawFeedback` class in action for a typical circular saw cutting sequence:

    <div style="padding:56.25% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/1025909182?badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture; clipboard-write" style="position:absolute;top:0;left:0;width:100%;height:100%;" title="Augmented Carpentry: Single Augmented Ciruclar Saw Sequence"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

This composite system allows for a flexible and modular feedback system that can be easily extended with new feedback types and visualizations.