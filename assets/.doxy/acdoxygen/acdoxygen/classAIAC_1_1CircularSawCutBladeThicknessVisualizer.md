

# Class AIAC::CircularSawCutBladeThicknessVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CircularSawCutBladeThicknessVisualizer**](classAIAC_1_1CircularSawCutBladeThicknessVisualizer.md)



_This is an inherited class to show the thickness of the blade on circular saws._ 

* `#include <CutCircularSawFeedback.h>`



Inherits the following classes: [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md)




























## Public Attributes inherited from AIAC::CutBladeThicknessVisualizer

See [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md)

| Type | Name |
| ---: | :--- |
|  bool | [**IsSegmenDetectToolPlaneVisible**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-issegmendetecttoolplanevisible)   = `false`<br>_&lt;_  |














































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CircularSawCutBladeThicknessVisualizer**](#function-circularsawcutbladethicknessvisualizer) () = default<br> |
| virtual bool | [**IntersectBladeWithNeighbours**](#function-intersectbladewithneighbours) ([**TimberInfo::Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) \* cut, [**TimberInfo::Cut::Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) & face, bool isTowardsCamera, bool isDetectToolPlane, std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; & lineIntersection) override<br>_This function intersect the plane of the blade with the two(or one) neighbour faces._  |
| virtual void | [**UpdateToolheadsData**](#function-updatetoolheadsdata) () override<br>_Update the current toolhead's data: normalStart, normEnd and center, as well the thickness. Since there could be multiple cutting toolheads (sawblade or chainsaw), we need to get the correct toolhead's type._  |


## Public Functions inherited from AIAC::CutBladeThicknessVisualizer

See [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md)

| Type | Name |
| ---: | :--- |
|   | [**CutBladeThicknessVisualizer**](classAIAC_1_1CutBladeThicknessVisualizer.md#function-cutbladethicknessvisualizer) () <br> |


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
















## Protected Attributes inherited from AIAC::CutBladeThicknessVisualizer

See [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md)

| Type | Name |
| ---: | :--- |
|  float | [**m\_BladeOverhangScaled**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_bladeoverhangscaled)  <br>_the reference to the current toolhead's normal start_  |
|  float | [**m\_BladeTotalThicknessScaled**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_bladetotalthicknessscaled)  <br>_the overhang distance of the blade's teeth from one side only_  |
|  glm::vec3 | [**m\_DisplacedCenterAwayFromCamera**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_displacedcenterawayfromcamera)  <br> |
|  glm::vec3 | [**m\_DisplacedCenterTowardsCamera**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_displacedcentertowardscamera)  <br>_the displaced center of the face away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmenDetectToolPlane**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_longestintersectsegmendetecttoolplane)  <br>_&lt;_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAwayFromCameraA**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_longestintersectsegmentawayfromcameraa)  <br>_the thickness A of the blade away from the camera on second neighbour side_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAwayFromCameraB**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_longestintersectsegmentawayfromcamerab)  <br>_the scaled thickness of the blade towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentTowardsCameraA**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_longestintersectsegmenttowardscameraa)  <br>_the thickness of the blade towards the camera on second neighbour side_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentTowardsCameraB**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_longestintersectsegmenttowardscamerab)  <br>_the thickness A of the blade away from the camera on first neighbour side_  |
|  glm::vec3 | [**m\_NormalOppositeUnitized**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_normaloppositeunitized)  <br>_the displaced center of the face towards the camera_  |
|  glm::vec3 | [**m\_NormalUnitized**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_normalunitized)  <br>_the opposite unitize value of the normal_  |
|  glm::vec3 | [**m\_ToolheadRefCenter**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_toolheadrefcenter)  <br>_the unitize value of the normal_  |
|  glm::vec3 | [**m\_ToolheadRefNormEnd**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_toolheadrefnormend)  <br>_the reference to the current toolhead's center_  |
|  glm::vec3 | [**m\_ToolheadRefNormStart**](classAIAC_1_1CutBladeThicknessVisualizer.md#variable-m_toolheadrefnormstart)  <br>_the reference to the current toolhead's normal end_  |


## Protected Attributes inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](classAIAC_1_1FeedbackVisualizer.md#variable-m_allprimitives)  <br> |














































## Protected Functions inherited from AIAC::CutBladeThicknessVisualizer

See [AIAC::CutBladeThicknessVisualizer](classAIAC_1_1CutBladeThicknessVisualizer.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**IntersectBladeWithNeighbours**](classAIAC_1_1CutBladeThicknessVisualizer.md#function-intersectbladewithneighbours) ([**AIAC::TimberInfo::Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) \* cut, [**AIAC::TimberInfo::Cut::Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) & face, bool isTowardsCamera, bool isDetectToolPlane, std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; & lineIntersection) = 0<br>_This function intersect the plane of the blade with the two(or one) neighbour faces._  |
| virtual void | [**UpdateToolheadsData**](classAIAC_1_1CutBladeThicknessVisualizer.md#function-updatetoolheadsdata) () = 0<br>_Update the current toolhead's data: normalStart, normEnd and center, as well the thickness. Since there could be multiple cutting toolheads (sawblade or chainsaw), we need to get the correct toolhead's type._  |










## Public Functions Documentation




### function CircularSawCutBladeThicknessVisualizer 

```C++
AIAC::CircularSawCutBladeThicknessVisualizer::CircularSawCutBladeThicknessVisualizer () = default
```




<hr>



### function IntersectBladeWithNeighbours 

_This function intersect the plane of the blade with the two(or one) neighbour faces._ 
```C++
virtual bool AIAC::CircularSawCutBladeThicknessVisualizer::IntersectBladeWithNeighbours (
    TimberInfo::Cut * cut,
    TimberInfo::Cut::Face & face,
    bool isTowardsCamera,
    bool isDetectToolPlane,
    std::shared_ptr< GOLine > & lineIntersection
) override
```





**Parameters:**


* `cut` the [**TimberInfo::Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) object 
* `face` the face belonging to the cut to intersect with 
* `isTowardsCamera` the boolean to indicate if we intersect the blade's edge close to the camera 
* `isDetectToolPlane` the intersection is for the reference toolhead's plane 
* `lineIntersection` the reference to the line intersection



**Returns:**

bool true if the intersection is successful, false otherwise 





        
Implements [*AIAC::CutBladeThicknessVisualizer::IntersectBladeWithNeighbours*](classAIAC_1_1CutBladeThicknessVisualizer.md#function-intersectbladewithneighbours)


<hr>



### function UpdateToolheadsData 

_Update the current toolhead's data: normalStart, normEnd and center, as well the thickness. Since there could be multiple cutting toolheads (sawblade or chainsaw), we need to get the correct toolhead's type._ 
```C++
virtual void AIAC::CircularSawCutBladeThicknessVisualizer::UpdateToolheadsData () override
```



Implements [*AIAC::CutBladeThicknessVisualizer::UpdateToolheadsData*](classAIAC_1_1CutBladeThicknessVisualizer.md#function-updatetoolheadsdata)


<hr>## Friends Documentation





### friend CutCircularSawFeedback 

```C++
class AIAC::CircularSawCutBladeThicknessVisualizer::CutCircularSawFeedback (
    CutCircularSawFeedback
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutCircularSawFeedback.h`

