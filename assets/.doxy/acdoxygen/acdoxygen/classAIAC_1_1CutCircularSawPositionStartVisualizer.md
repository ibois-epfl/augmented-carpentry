

# Class AIAC::CutCircularSawPositionStartVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CutCircularSawPositionStartVisualizer**](classAIAC_1_1CutCircularSawPositionStartVisualizer.md)



_This visualizer gives guidance on the start position of the lateral cuts for the circular saw._ 

* `#include <CutCircularSawFeedback.h>`



Inherits the following classes: [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  float | [**ToleranceStartThreshold**](#variable-tolerancestartthreshold)   = `0.2f`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CutCircularSawPositionStartVisualizer**](#function-cutcircularsawpositionstartvisualizer) () <br> |


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






































## Public Attributes Documentation




### variable ToleranceStartThreshold 

```C++
float AIAC::CutCircularSawPositionStartVisualizer::ToleranceStartThreshold;
```




<hr>
## Public Functions Documentation




### function CutCircularSawPositionStartVisualizer 

```C++
AIAC::CutCircularSawPositionStartVisualizer::CutCircularSawPositionStartVisualizer () 
```




<hr>## Friends Documentation





### friend CutCircularSawFeedback 

```C++
class AIAC::CutCircularSawPositionStartVisualizer::CutCircularSawFeedback (
    CutCircularSawFeedback
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutCircularSawFeedback.h`

