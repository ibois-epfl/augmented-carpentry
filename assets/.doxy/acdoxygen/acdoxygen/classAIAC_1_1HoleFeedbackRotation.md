

# Class AIAC::HoleFeedbackRotation



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**HoleFeedbackRotation**](classAIAC_1_1HoleFeedbackRotation.md)



_The UI widget for providing feedback on rotation._ 

* `#include <HoleFeedback.h>`



Inherits the following classes: [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**HoleFeedbackRotation**](#function-holefeedbackrotation) () <br> |


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




### function HoleFeedbackRotation 

```C++
AIAC::HoleFeedbackRotation::HoleFeedbackRotation () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/HoleFeedback.h`

