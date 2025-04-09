

# Class AIAC::CutBladeThicknessVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CutBladeThicknessVisualizer**](classAIAC_1_1CutBladeThicknessVisualizer.md)



_The idea behind the_ [_**CutBladeThicknessVisualizer**_](classAIAC_1_1CutBladeThicknessVisualizer.md) _is to give a visual feedback on the thickness of the blade. We do this by intersecting the two neighbours faces of the current highlighted face._

* `#include <CutBladeThicknessVisualizer.h>`



Inherits the following classes: [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)


Inherited by the following classes: [AIAC::CircularSawCutBladeThicknessVisualizer](classAIAC_1_1CircularSawCutBladeThicknessVisualizer.md)




















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**IsSegmenDetectToolPlaneVisible**](#variable-issegmendetecttoolplanevisible)   = `false`<br>_&lt;_  |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CutBladeThicknessVisualizer**](#function-cutbladethicknessvisualizer) () <br> |


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










## Protected Attributes

| Type | Name |
| ---: | :--- |
|  float | [**m\_BladeOverhangScaled**](#variable-m_bladeoverhangscaled)  <br>_the reference to the current toolhead's normal start_  |
|  float | [**m\_BladeTotalThicknessScaled**](#variable-m_bladetotalthicknessscaled)  <br>_the overhang distance of the blade's teeth from one side only_  |
|  glm::vec3 | [**m\_DisplacedCenterAwayFromCamera**](#variable-m_displacedcenterawayfromcamera)  <br> |
|  glm::vec3 | [**m\_DisplacedCenterTowardsCamera**](#variable-m_displacedcentertowardscamera)  <br>_the displaced center of the face away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmenDetectToolPlane**](#variable-m_longestintersectsegmendetecttoolplane)  <br>_&lt;_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAwayFromCameraA**](#variable-m_longestintersectsegmentawayfromcameraa)  <br>_the thickness A of the blade away from the camera on second neighbour side_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAwayFromCameraB**](#variable-m_longestintersectsegmentawayfromcamerab)  <br>_the scaled thickness of the blade towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentTowardsCameraA**](#variable-m_longestintersectsegmenttowardscameraa)  <br>_the thickness of the blade towards the camera on second neighbour side_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentTowardsCameraB**](#variable-m_longestintersectsegmenttowardscamerab)  <br>_the thickness A of the blade away from the camera on first neighbour side_  |
|  glm::vec3 | [**m\_NormalOppositeUnitized**](#variable-m_normaloppositeunitized)  <br>_the displaced center of the face towards the camera_  |
|  glm::vec3 | [**m\_NormalUnitized**](#variable-m_normalunitized)  <br>_the opposite unitize value of the normal_  |
|  glm::vec3 | [**m\_ToolheadRefCenter**](#variable-m_toolheadrefcenter)  <br>_the unitize value of the normal_  |
|  glm::vec3 | [**m\_ToolheadRefNormEnd**](#variable-m_toolheadrefnormend)  <br>_the reference to the current toolhead's center_  |
|  glm::vec3 | [**m\_ToolheadRefNormStart**](#variable-m_toolheadrefnormstart)  <br>_the reference to the current toolhead's normal end_  |


## Protected Attributes inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](classAIAC_1_1FeedbackVisualizer.md#variable-m_allprimitives)  <br> |






























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**IntersectBladeWithNeighbours**](#function-intersectbladewithneighbours) ([**AIAC::TimberInfo::Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) \* cut, [**AIAC::TimberInfo::Cut::Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) & face, bool isTowardsCamera, bool isDetectToolPlane, std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; & lineIntersection) = 0<br>_This function intersect the plane of the blade with the two(or one) neighbour faces._  |
| virtual void | [**UpdateToolheadsData**](#function-updatetoolheadsdata) () = 0<br>_Update the current toolhead's data: normalStart, normEnd and center, as well the thickness. Since there could be multiple cutting toolheads (sawblade or chainsaw), we need to get the correct toolhead's type._  |








## Public Attributes Documentation




### variable IsSegmenDetectToolPlaneVisible 

_&lt;_ 
```C++
bool AIAC::CutBladeThicknessVisualizer::IsSegmenDetectToolPlaneVisible;
```



if the segment of the detected blade is visible 


        

<hr>
## Public Functions Documentation




### function CutBladeThicknessVisualizer 

```C++
AIAC::CutBladeThicknessVisualizer::CutBladeThicknessVisualizer () 
```




<hr>
## Protected Attributes Documentation




### variable m\_BladeOverhangScaled 

_the reference to the current toolhead's normal start_ 
```C++
float AIAC::CutBladeThicknessVisualizer::m_BladeOverhangScaled;
```




<hr>



### variable m\_BladeTotalThicknessScaled 

_the overhang distance of the blade's teeth from one side only_ 
```C++
float AIAC::CutBladeThicknessVisualizer::m_BladeTotalThicknessScaled;
```




<hr>



### variable m\_DisplacedCenterAwayFromCamera 

```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_DisplacedCenterAwayFromCamera;
```




<hr>



### variable m\_DisplacedCenterTowardsCamera 

_the displaced center of the face away from the camera_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_DisplacedCenterTowardsCamera;
```




<hr>



### variable m\_LongestIntersectSegmenDetectToolPlane 

_&lt;_ 
```C++
std::shared_ptr<GOLine> AIAC::CutBladeThicknessVisualizer::m_LongestIntersectSegmenDetectToolPlane;
```



the segment where the blade is detected by the toolhead


the thickness of the blade towards the camera on first neighbour side 


        

<hr>



### variable m\_LongestIntersectSegmentAwayFromCameraA 

_the thickness A of the blade away from the camera on second neighbour side_ 
```C++
std::shared_ptr<GOLine> AIAC::CutBladeThicknessVisualizer::m_LongestIntersectSegmentAwayFromCameraA;
```




<hr>



### variable m\_LongestIntersectSegmentAwayFromCameraB 

_the scaled thickness of the blade towards the camera_ 
```C++
std::shared_ptr<GOLine> AIAC::CutBladeThicknessVisualizer::m_LongestIntersectSegmentAwayFromCameraB;
```




<hr>



### variable m\_LongestIntersectSegmentTowardsCameraA 

_the thickness of the blade towards the camera on second neighbour side_ 
```C++
std::shared_ptr<GOLine> AIAC::CutBladeThicknessVisualizer::m_LongestIntersectSegmentTowardsCameraA;
```




<hr>



### variable m\_LongestIntersectSegmentTowardsCameraB 

_the thickness A of the blade away from the camera on first neighbour side_ 
```C++
std::shared_ptr<GOLine> AIAC::CutBladeThicknessVisualizer::m_LongestIntersectSegmentTowardsCameraB;
```




<hr>



### variable m\_NormalOppositeUnitized 

_the displaced center of the face towards the camera_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_NormalOppositeUnitized;
```




<hr>



### variable m\_NormalUnitized 

_the opposite unitize value of the normal_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_NormalUnitized;
```




<hr>



### variable m\_ToolheadRefCenter 

_the unitize value of the normal_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_ToolheadRefCenter;
```




<hr>



### variable m\_ToolheadRefNormEnd 

_the reference to the current toolhead's center_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_ToolheadRefNormEnd;
```




<hr>



### variable m\_ToolheadRefNormStart 

_the reference to the current toolhead's normal end_ 
```C++
glm::vec3 AIAC::CutBladeThicknessVisualizer::m_ToolheadRefNormStart;
```




<hr>
## Protected Functions Documentation




### function IntersectBladeWithNeighbours 

_This function intersect the plane of the blade with the two(or one) neighbour faces._ 
```C++
virtual bool AIAC::CutBladeThicknessVisualizer::IntersectBladeWithNeighbours (
    AIAC::TimberInfo::Cut * cut,
    AIAC::TimberInfo::Cut::Face & face,
    bool isTowardsCamera,
    bool isDetectToolPlane,
    std::shared_ptr< GOLine > & lineIntersection
) = 0
```





**Parameters:**


* `cut` the [**TimberInfo::Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) object 
* `face` the face belonging to the cut to intersect with 
* `isTowardsCamera` the boolean to indicate if we intersect the blade's edge close to the camera 
* `isDetectToolPlane` the intersection is for the reference toolhead's plane 
* `lineIntersection` the reference to the line intersection



**Returns:**

bool true if the intersection is successful, false otherwise 





        

<hr>



### function UpdateToolheadsData 

_Update the current toolhead's data: normalStart, normEnd and center, as well the thickness. Since there could be multiple cutting toolheads (sawblade or chainsaw), we need to get the correct toolhead's type._ 
```C++
virtual void AIAC::CutBladeThicknessVisualizer::UpdateToolheadsData () = 0
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutBladeThicknessVisualizer.h`

