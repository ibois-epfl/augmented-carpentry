

# File CutChainSawFeedback.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Feedback**](dir_2e808e595a766fe55342199a604574e7.md) **>** [**CutChainSawFeedback.h**](CutChainSawFeedback_8h.md)

[Go to the source code of this file](CutChainSawFeedback_8h_source.md)



* `#include "AIAC/Feedback/CutPlaneVisualizer.h"`
* `#include "AIAC/Feedback/FeedbackVisualizer.h"`
* `#include "AIAC/Feedback/FabFeedback.h"`
* `#include <vector>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**ChainSawCutPlaneVisualizer**](classAIAC_1_1ChainSawCutPlaneVisualizer.md) <br> |
| class | [**CutChainSawAngleFeedVisualizer**](classAIAC_1_1CutChainSawAngleFeedVisualizer.md) <br> |
| class | [**CutChainSawDepthFeedVisualizer**](classAIAC_1_1CutChainSawDepthFeedVisualizer.md) <br> |
| class | [**CutChainSawFeedVisualizer**](classAIAC_1_1CutChainSawFeedVisualizer.md) <br> |
| class | [**CutChainSawFeedback**](classAIAC_1_1CutChainSawFeedback.md) <br> |
| class | [**CutOrientationVisualizer**](classAIAC_1_1CutOrientationVisualizer.md) <br>_This visualizer gives a bit of guidance on the cut orientation. Although it is not possible to determine the exact orientation of the cut, this visualizer gives a rough idea of the pitch and roll. The way this is done is by projecting the blade normal onto the face normal, and then projecting the resulting vector onto the face normal. If we close the triangle of these two lines we can monitor the angle that must be 45\*. This way we can also have the direction towards which the blade needs to be tilted._  |



















































------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutChainSawFeedback.h`

