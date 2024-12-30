

# Class AIAC::FeedbackVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**FeedbackVisualizer**](classAIAC_1_1FeedbackVisualizer.md)










Inherited by the following classes: [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md),  [AIAC::CutChainSawAngleFeedVisualizer](classAIAC_1_1CutChainSawAngleFeedVisualizer.md),  [AIAC::CutChainSawDepthFeedVisualizer](classAIAC_1_1CutChainSawDepthFeedVisualizer.md),  [AIAC::CutChainSawFeedVisualizer](classAIAC_1_1CutChainSawFeedVisualizer.md),  [AIAC::CutCircularOrientationVisualizer](classAIAC_1_1CutCircularOrientationVisualizer.md),  [AIAC::CutCircularSawDepthVisualizer](classAIAC_1_1CutCircularSawDepthVisualizer.md),  [AIAC::CutCircularSawPositionStartVisualizer](classAIAC_1_1CutCircularSawPositionStartVisualizer.md),  [AIAC::CutOrientationVisualizer](classAIAC_1_1CutOrientationVisualizer.md),  [AIAC::CutPlaneVisualizer](classAIAC_1_1CutPlaneVisualizer.md),  [AIAC::HoleFeedbackPosition](classAIAC_1_1HoleFeedbackPosition.md),  [AIAC::HoleFeedbackRotation](classAIAC_1_1HoleFeedbackRotation.md),  [AIAC::HoleFeedbackText](classAIAC_1_1HoleFeedbackText.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](#function-activate) () <br> |
| virtual void | [**Deactivate**](#function-deactivate) () <br> |
|   | [**FeedbackVisualizer**](#function-feedbackvisualizer) () = default<br> |
|   | [**~FeedbackVisualizer**](#function-feedbackvisualizer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**toString**](#function-tostring) (double val) <br>_Convert a double value to the real world scale in mm and return a string with 2 digits. If the value in mm is &gt; 99, return "99"._  |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](#variable-m_allprimitives)  <br> |




















## Public Functions Documentation




### function Activate 

```C++
inline virtual void AIAC::FeedbackVisualizer::Activate () 
```




<hr>



### function Deactivate 

```C++
inline virtual void AIAC::FeedbackVisualizer::Deactivate () 
```




<hr>



### function FeedbackVisualizer 

```C++
AIAC::FeedbackVisualizer::FeedbackVisualizer () = default
```




<hr>



### function ~FeedbackVisualizer 

```C++
AIAC::FeedbackVisualizer::~FeedbackVisualizer () = default
```




<hr>
## Public Static Functions Documentation




### function toString 

_Convert a double value to the real world scale in mm and return a string with 2 digits. If the value in mm is &gt; 99, return "99"._ 
```C++
static inline std::string AIAC::FeedbackVisualizer::toString (
    double val
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_AllPrimitives 

```C++
std::vector<std::shared_ptr<GOPrimitive> > AIAC::FeedbackVisualizer::m_AllPrimitives;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/FeedbackVisualizer.h`

