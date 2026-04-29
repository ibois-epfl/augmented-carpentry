

# File CutCircularSawFeedback.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Feedback**](dir_2e808e595a766fe55342199a604574e7.md) **>** [**CutCircularSawFeedback.h**](CutCircularSawFeedback_8h.md)

[Go to the source code of this file](CutCircularSawFeedback_8h_source.md)



* `#include "AIAC/GOSys/GOPrimitive.h"`
* `#include "AIAC/ACInfoModel.h"`
* `#include "FeedbackVisualizer.h"`
* `#include "CutPlaneVisualizer.h"`
* `#include "CutBladeThicknessVisualizer.h"`
* `#include "FabFeedback.h"`
* `#include "utils/GeometryUtils.h"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**CircularSawCutBladeThicknessVisualizer**](classAIAC_1_1CircularSawCutBladeThicknessVisualizer.md) <br>_This is an inherited class to show the thickness of the blade on circular saws._  |
| class | [**CircularSawCutPlaneVisualizer**](classAIAC_1_1CircularSawCutPlaneVisualizer.md) <br> |
| class | [**CutCircularOrientationVisualizer**](classAIAC_1_1CutCircularOrientationVisualizer.md) <br>_This visualizer ggdb ives a bit of guidance on the cut orientation. Although it is not possible to determine the exact orientation of the cut, this visualizer gives a rough idea of the pitch and roll. The way this is done is by projecting the blade normal onto the face normal, and then projecting the resulting vector onto the face normal. If we close the triangle of these two lines we can monitor the angle that must be 45\*. This way we can also have the direction towards which the blade needs to be tilted._  |
| class | [**CutCircularSawDepthVisualizer**](classAIAC_1_1CutCircularSawDepthVisualizer.md) <br>_Visualizer for showing the depth of the cut._  |
| class | [**CutCircularSawFeedback**](classAIAC_1_1CutCircularSawFeedback.md) <br> |
| class | [**CutCircularSawPositionStartVisualizer**](classAIAC_1_1CutCircularSawPositionStartVisualizer.md) <br>_This visualizer gives guidance on the start position of the lateral cuts for the circular saw._  |



















































------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutCircularSawFeedback.h`

