

# File GeometryUtils.h



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**GeometryUtils.h**](utils_2GeometryUtils_8h.md)

[Go to the source code of this file](utils_2GeometryUtils_8h_source.md)



* `#include "glm/glm.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ExtendLineSeg**](#function-extendlineseg) (glm::vec3 & pt1, glm::vec3 & pt2, float extendLen) <br>_Make a line segment longer by a certain length._  |
|  bool | [**FormLongestLineSeg**](#function-formlongestlineseg) (const std::vector&lt; glm::vec3 &gt; & pts, glm::vec3 & pt1, glm::vec3 & pt2) <br>_From a list of points, find 2 point that forms the longest line segment._  |
|  float | [**GetAngleBetweenVectors**](#function-getanglebetweenvectors) (glm::vec3 v1, glm::vec3 v2, bool useDegree=false) <br>_Get the angle between 2 vectors._  |
|  bool | [**GetIntersectLineOf2Planes**](#function-getintersectlineof2planes) (glm::vec3 p1Norm, glm::vec3 pt1, glm::vec3 p2Norm, glm::vec3 pt2, glm::vec3 & lineVec, glm::vec3 & linePt) <br>_Get the Intersect Line Of 2 Planes._  |
|  bool | [**GetIntersectPointOf2Lines**](#function-getintersectpointof2lines) (glm::vec3 dir1, glm::vec3 pt1, glm::vec3 dir2, glm::vec3 pt2, glm::vec3 & pt) <br>_Get the Intersect Point Of 2 Lines._  |
|  bool | [**GetIntersectPointOfLineAndLineSeg**](#function-getintersectpointoflineandlineseg) (glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 lineSegPt1, glm::vec3 lineSegPt2, glm::vec3 & ptInLineSeg) <br>_Get the Intersect Point Of Line And Line Seg object._  |
|  bool | [**GetIntersectPointOfLineAndPlane**](#function-getintersectpointoflineandplane) (glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 & intersectPt) <br>_Get the Intersect Point Of Line And Plane object._  |
|  bool | [**GetIntersectPointOfLineSegAndPlane**](#function-getintersectpointoflinesegandplane) (glm::vec3 lineSegPt1, glm::vec3 lineSegPt2, glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 & intersectPt) <br>_Get the Intersect Point Of Line Seg And Plane object._  |
|  glm::vec3 | [**GetNearestPtOnLine**](#function-getnearestptonline) (glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 pt) <br>_Get the Nearest Pt On Line object._  |
|  glm::vec3 | [**GetProjectionPointOnPlane**](#function-getprojectionpointonplane) (glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 pt) <br>_Get the projection point of a point on a plane._  |
|  bool | [**IsPointBetweenLineSeg**](#function-ispointbetweenlineseg) (glm::vec3 pt, glm::vec3 lineSegPt1, glm::vec3 lineSegPt2) <br>_Check if a point is between a line segment, no matter if the point is on the line segment or not._  |
|  bool | [**IsSameDirection**](#function-issamedirection) (glm::vec3 v1, glm::vec3 v2) <br>_Check if 2 vectors are in the same direction (angle &lt; 180 degree)_  |




























## Public Functions Documentation




### function ExtendLineSeg 

_Make a line segment longer by a certain length._ 
```C++
inline void ExtendLineSeg (
    glm::vec3 & pt1,
    glm::vec3 & pt2,
    float extendLen
) 
```





**Parameters:**


* `pt1` Start of the line segment 
* `pt2` End of the line segment 
* `extendLen` Length to extend 




        

<hr>



### function FormLongestLineSeg 

_From a list of points, find 2 point that forms the longest line segment._ 
```C++
inline bool FormLongestLineSeg (
    const std::vector< glm::vec3 > & pts,
    glm::vec3 & pt1,
    glm::vec3 & pt2
) 
```





**Parameters:**


* `pts` Candidate points 
* `pt1` Start of the line segment 
* `pt2` End of the line segment 



**Returns:**

true if the line segment is formed successfully 





        

<hr>



### function GetAngleBetweenVectors 

_Get the angle between 2 vectors._ 
```C++
inline float GetAngleBetweenVectors (
    glm::vec3 v1,
    glm::vec3 v2,
    bool useDegree=false
) 
```





**Parameters:**


* `v1` 
* `v2` 



**Returns:**

float 





        

<hr>



### function GetIntersectLineOf2Planes 

_Get the Intersect Line Of 2 Planes._ 
```C++
inline bool GetIntersectLineOf2Planes (
    glm::vec3 p1Norm,
    glm::vec3 pt1,
    glm::vec3 p2Norm,
    glm::vec3 pt2,
    glm::vec3 & lineVec,
    glm::vec3 & linePt
) 
```





**Parameters:**


* `p1Norm` 
* `pt1` 
* `p2Norm` 
* `pt2` 
* `lineVec` 
* `linePt` 



**Returns:**

true if intersect, false if not 





        

<hr>



### function GetIntersectPointOf2Lines 

_Get the Intersect Point Of 2 Lines._ 
```C++
inline bool GetIntersectPointOf2Lines (
    glm::vec3 dir1,
    glm::vec3 pt1,
    glm::vec3 dir2,
    glm::vec3 pt2,
    glm::vec3 & pt
) 
```





**Parameters:**


* `dir1` 
* `pt1` 
* `dir2` 
* `pt2` 
* `pt` 



**Returns:**

true if intersect, false if not 





        

<hr>



### function GetIntersectPointOfLineAndLineSeg 

_Get the Intersect Point Of Line And Line Seg object._ 
```C++
inline bool GetIntersectPointOfLineAndLineSeg (
    glm::vec3 lineVec,
    glm::vec3 linePt,
    glm::vec3 lineSegPt1,
    glm::vec3 lineSegPt2,
    glm::vec3 & ptInLineSeg
) 
```





**Parameters:**


* `lineVec` 
* `linePt` 
* `lineSegPt1` 
* `lineSegPt2` 
* `ptInLineSeg` 



**Returns:**

true if intersect, false if not 





        

<hr>



### function GetIntersectPointOfLineAndPlane 

_Get the Intersect Point Of Line And Plane object._ 
```C++
inline bool GetIntersectPointOfLineAndPlane (
    glm::vec3 lineVec,
    glm::vec3 linePt,
    glm::vec3 planeNormal,
    glm::vec3 planePt,
    glm::vec3 & intersectPt
) 
```





**Parameters:**


* `lineVec` 
* `linePt` 
* `planeNormal` 
* `planePt` 
* `intersectPt` 



**Returns:**

true if intersect, false if not 





        

<hr>



### function GetIntersectPointOfLineSegAndPlane 

_Get the Intersect Point Of Line Seg And Plane object._ 
```C++
inline bool GetIntersectPointOfLineSegAndPlane (
    glm::vec3 lineSegPt1,
    glm::vec3 lineSegPt2,
    glm::vec3 planeNormal,
    glm::vec3 planePt,
    glm::vec3 & intersectPt
) 
```





**Parameters:**


* `lineSegPt1` 
* `lineSegPt2` 
* `planeNormal` 
* `planePt` 
* `intersectPt` 



**Returns:**

true 




**Returns:**

false 





        

<hr>



### function GetNearestPtOnLine 

_Get the Nearest Pt On Line object._ 
```C++
inline glm::vec3 GetNearestPtOnLine (
    glm::vec3 lineVec,
    glm::vec3 linePt,
    glm::vec3 pt
) 
```





**Parameters:**


* `lineVec` 
* `linePt` 
* `pt` 



**Returns:**

glm::vec3 





        

<hr>



### function GetProjectionPointOnPlane 

_Get the projection point of a point on a plane._ 
```C++
inline glm::vec3 GetProjectionPointOnPlane (
    glm::vec3 planeNormal,
    glm::vec3 planePt,
    glm::vec3 pt
) 
```





**Parameters:**


* `planeNormal` Normal of the plane 
* `planePt` A point on the plane 
* `point` The point to project 



**Returns:**

glm::vec3 The projection point 





        

<hr>



### function IsPointBetweenLineSeg 

_Check if a point is between a line segment, no matter if the point is on the line segment or not._ 
```C++
inline bool IsPointBetweenLineSeg (
    glm::vec3 pt,
    glm::vec3 lineSegPt1,
    glm::vec3 lineSegPt2
) 
```





**Parameters:**


* `pt` Point to check 
* `lineSegPt1` Start of the line segment 
* `lineSegPt2` End of the line segment 



**Returns:**

true if the point is between the line segment 





        

<hr>



### function IsSameDirection 

_Check if 2 vectors are in the same direction (angle &lt; 180 degree)_ 
```C++
inline bool IsSameDirection (
    glm::vec3 v1,
    glm::vec3 v2
) 
```





**Parameters:**


* `v1` 
* `v2` 



**Returns:**

true if in the same direction 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/GeometryUtils.h`

