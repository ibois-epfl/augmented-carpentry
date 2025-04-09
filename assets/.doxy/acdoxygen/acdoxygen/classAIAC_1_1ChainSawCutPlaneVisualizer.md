

# Class AIAC::ChainSawCutPlaneVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ChainSawCutPlaneVisualizer**](classAIAC_1_1ChainSawCutPlaneVisualizer.md)








Inherits the following classes: [AIAC::CutPlaneVisualizer](classAIAC_1_1CutPlaneVisualizer.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ChainSawCutPlaneVisualizer**](#function-chainsawcutplanevisualizer) () = default<br> |


## Public Functions inherited from AIAC::CutPlaneVisualizer

See [AIAC::CutPlaneVisualizer](classAIAC_1_1CutPlaneVisualizer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](classAIAC_1_1CutPlaneVisualizer.md#function-activate) () override<br> |
|   | [**CutPlaneVisualizer**](classAIAC_1_1CutPlaneVisualizer.md#function-cutplanevisualizer) () <br> |
| virtual void | [**Deactivate**](classAIAC_1_1CutPlaneVisualizer.md#function-deactivate) () override<br> |
|  std::vector&lt; glm::vec3 &gt; | [**Update**](classAIAC_1_1CutPlaneVisualizer.md#function-update) (glm::vec3 faceNorm, glm::vec3 facePt) <br>_Update the intersection polyline and face, and return the intersection point._  |


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
















## Protected Attributes inherited from AIAC::CutPlaneVisualizer

See [AIAC::CutPlaneVisualizer](classAIAC_1_1CutPlaneVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentA1**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmenta1)  <br>_the intersection line of the blade indicating the thickness away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentA2**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmenta2)  <br>_the intersection line of the blade indicating the thickness towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAppCenterA**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmentappcentera)  <br>_&lt;_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAppCenterB**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmentappcenterb)  <br>_the intersection line of the blade indicating the thickness towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentB1**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmentb1)  <br>_the intersection line of the blade indicating the thickness away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentB2**](classAIAC_1_1CutPlaneVisualizer.md#variable-m_longestintersectsegmentb2)  <br> |


## Protected Attributes inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](classAIAC_1_1FeedbackVisualizer.md#variable-m_allprimitives)  <br> |
























































## Public Functions Documentation




### function ChainSawCutPlaneVisualizer 

```C++
AIAC::ChainSawCutPlaneVisualizer::ChainSawCutPlaneVisualizer () = default
```




<hr>## Friends Documentation





### friend CutChainSawFeedback 

```C++
class AIAC::ChainSawCutPlaneVisualizer::CutChainSawFeedback (
    CutChainSawFeedback
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutChainSawFeedback.h`

