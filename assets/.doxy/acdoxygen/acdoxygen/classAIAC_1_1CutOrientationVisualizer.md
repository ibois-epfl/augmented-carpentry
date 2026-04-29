

# Class AIAC::CutOrientationVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CutOrientationVisualizer**](classAIAC_1_1CutOrientationVisualizer.md)



_This visualizer gives a bit of guidance on the cut orientation. Although it is not possible to determine the exact orientation of the cut, this visualizer gives a rough idea of the pitch and roll. The way this is done is by projecting the blade normal onto the face normal, and then projecting the resulting vector onto the face normal. If we close the triangle of these two lines we can monitor the angle that must be 45\*. This way we can also have the direction towards which the blade needs to be tilted._ 

* `#include <CutChainSawFeedback.h>`



Inherits the following classes: [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CutOrientationVisualizer**](#function-cutorientationvisualizer) () <br> |


## Public Functions inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](classAIAC_1_1FeedbackVisualizer.md#function-activate) () <br> |
| virtual void | [**Deactivate**](classAIAC_1_1FeedbackVisualizer.md#function-deactivate) () <br> |
|   | [**FeedbackVisualizer**](classAIAC_1_1FeedbackVisualizer.md#function-feedbackvisualizer) () = default<br> |
|   | [**~FeedbackVisualizer**](classAIAC_1_1FeedbackVisualizer.md#function-feedbackvisualizer) () = default<br> |




## Public Static Functions inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::string | [**toString**](classAIAC_1_1FeedbackVisualizer.md#function-tostring) (double val) <br>_Convert a double value to the real world scale in mm and return a string with 2 digits. If the value in mm is &gt; 99, return "99"._  |












## Protected Attributes inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](classAIAC_1_1FeedbackVisualizer.md#variable-m_allprimitives)  <br> |






































## Public Functions Documentation




### function CutOrientationVisualizer 

```C++
AIAC::CutOrientationVisualizer::CutOrientationVisualizer () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutChainSawFeedback.h`

