

# Class AIAC::CutPlaneVisualizer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CutPlaneVisualizer**](classAIAC_1_1CutPlaneVisualizer.md)








Inherits the following classes: [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)


Inherited by the following classes: [AIAC::ChainSawCutPlaneVisualizer](classAIAC_1_1ChainSawCutPlaneVisualizer.md),  [AIAC::CircularSawCutPlaneVisualizer](classAIAC_1_1CircularSawCutPlaneVisualizer.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](#function-activate) () override<br> |
|   | [**CutPlaneVisualizer**](#function-cutplanevisualizer) () <br> |
| virtual void | [**Deactivate**](#function-deactivate) () override<br> |
|  std::vector&lt; glm::vec3 &gt; | [**Update**](#function-update) (glm::vec3 faceNorm, glm::vec3 facePt) <br>_Update the intersection polyline and face, and return the intersection point._  |


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
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentA1**](#variable-m_longestintersectsegmenta1)  <br>_the intersection line of the blade indicating the thickness away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentA2**](#variable-m_longestintersectsegmenta2)  <br>_the intersection line of the blade indicating the thickness towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAppCenterA**](#variable-m_longestintersectsegmentappcentera)  <br>_&lt;_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentAppCenterB**](#variable-m_longestintersectsegmentappcenterb)  <br>_the intersection line of the blade indicating the thickness towards the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentB1**](#variable-m_longestintersectsegmentb1)  <br>_the intersection line of the blade indicating the thickness away from the camera_  |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**m\_LongestIntersectSegmentB2**](#variable-m_longestintersectsegmentb2)  <br> |


## Protected Attributes inherited from AIAC::FeedbackVisualizer

See [AIAC::FeedbackVisualizer](classAIAC_1_1FeedbackVisualizer.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_AllPrimitives**](classAIAC_1_1FeedbackVisualizer.md#variable-m_allprimitives)  <br> |






































## Public Functions Documentation




### function Activate 

```C++
virtual void AIAC::CutPlaneVisualizer::Activate () override
```



Implements [*AIAC::FeedbackVisualizer::Activate*](classAIAC_1_1FeedbackVisualizer.md#function-activate)


<hr>



### function CutPlaneVisualizer 

```C++
AIAC::CutPlaneVisualizer::CutPlaneVisualizer () 
```




<hr>



### function Deactivate 

```C++
virtual void AIAC::CutPlaneVisualizer::Deactivate () override
```



Implements [*AIAC::FeedbackVisualizer::Deactivate*](classAIAC_1_1FeedbackVisualizer.md#function-deactivate)


<hr>



### function Update 

_Update the intersection polyline and face, and return the intersection point._ 
```C++
std::vector< glm::vec3 > AIAC::CutPlaneVisualizer::Update (
    glm::vec3 faceNorm,
    glm::vec3 facePt
) 
```





**Parameters:**


* `faceNorm` the normal of the face 
* `facePt` the point on the face 



**Returns:**

std::vector&lt;glm::vec3&gt; the intersection point of the bbox and the face 





        

<hr>
## Protected Attributes Documentation




### variable m\_LongestIntersectSegmentA1 

_the intersection line of the blade indicating the thickness away from the camera_ 
```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentA1;
```




<hr>



### variable m\_LongestIntersectSegmentA2 

_the intersection line of the blade indicating the thickness towards the camera_ 
```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentA2;
```




<hr>



### variable m\_LongestIntersectSegmentAppCenterA 

_&lt;_ 
```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentAppCenterA;
```



the intersection of the top plane of the blade from the closest side to the center of the blade


the intersection of the top plane of the blade from the second closest side to the center of the blade 


        

<hr>



### variable m\_LongestIntersectSegmentAppCenterB 

_the intersection line of the blade indicating the thickness towards the camera_ 
```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentAppCenterB;
```




<hr>



### variable m\_LongestIntersectSegmentB1 

_the intersection line of the blade indicating the thickness away from the camera_ 
```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentB1;
```




<hr>



### variable m\_LongestIntersectSegmentB2 

```C++
std::shared_ptr<GOLine> AIAC::CutPlaneVisualizer::m_LongestIntersectSegmentB2;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutPlaneVisualizer.h`

