

# Class AIAC::GOCircle



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOCircle**](classAIAC_1_1GOCircle.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**ClosestPointToPoint**](#function-closestpointtopoint) (glm::vec3 point) <br>_Get the closest point to the circle from a given point._  |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetCenter**](#function-getcenter) () const<br> |
|  glm::vec4 | [**GetEdgeColor**](#function-getedgecolor) () const<br> |
|  glm::vec3 | [**GetNormal**](#function-getnormal) () const<br> |
|  float | [**GetRadius**](#function-getradius) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  void | [**SetCenter**](#function-setcenter) ([**GOPoint**](classAIAC_1_1GOPoint.md) center) <br> |
|  void | [**SetEdgeColor**](#function-setedgecolor) (glm::vec4 edgeColor) <br> |
|  void | [**SetNormal**](#function-setnormal) (glm::vec3 normal) <br> |
|  void | [**SetRadius**](#function-setradius) (float radius) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
| virtual  | [**~GOCircle**](#function-gocircle) () = default<br> |


## Public Functions inherited from AIAC::GOPrimitive

See [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)

| Type | Name |
| ---: | :--- |
|  void | [**ClearGLObject**](classAIAC_1_1GOPrimitive.md#function-clearglobject) () <br> |
|  void | [**Draw**](classAIAC_1_1GOPrimitive.md#function-draw) () <br> |
|   | [**GOPrimitive**](classAIAC_1_1GOPrimitive.md#function-goprimitive) (bool isVisible=true, glm::vec4 color=glm::vec4(0, 0, 0, 1.0)) <br> |
|  uint32\_t | [**GenerateId**](classAIAC_1_1GOPrimitive.md#function-generateid) () <br> |
|  glm::vec4 | [**GetColor**](classAIAC_1_1GOPrimitive.md#function-getcolor) () const<br> |
|  uint32\_t | [**GetId**](classAIAC_1_1GOPrimitive.md#function-getid) () <br> |
|  std::string | [**GetName**](classAIAC_1_1GOPrimitive.md#function-getname) () const<br> |
|  bool | [**GetState**](classAIAC_1_1GOPrimitive.md#function-getstate) () <br> |
|  GOTypeFlags | [**GetType**](classAIAC_1_1GOPrimitive.md#function-gettype) () <br> |
|  bool | [**GetVisibility**](classAIAC_1_1GOPrimitive.md#function-getvisibility) () <br> |
|  float | [**GetWeight**](classAIAC_1_1GOPrimitive.md#function-getweight) () const<br> |
| virtual void | [**InitGLObject**](classAIAC_1_1GOPrimitive.md#function-initglobject) () <br> |
|  bool | [**IsVisible**](classAIAC_1_1GOPrimitive.md#function-isvisible) () const<br> |
|  void | [**SetColor**](classAIAC_1_1GOPrimitive.md#function-setcolor) (glm::vec4 color) <br> |
|  void | [**SetName**](classAIAC_1_1GOPrimitive.md#function-setname) (std::string name) <br> |
|  void | [**SetState**](classAIAC_1_1GOPrimitive.md#function-setstate) (bool state) <br> |
| virtual void | [**SetValueFrom**](classAIAC_1_1GOPrimitive.md#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
|  void | [**SetVisibility**](classAIAC_1_1GOPrimitive.md#function-setvisibility) (bool isVisible) <br> |
|  int | [**SetWeight**](classAIAC_1_1GOPrimitive.md#function-setweight) (float weight) <br> |
| virtual void | [**Transform**](classAIAC_1_1GOPrimitive.md#function-transform) (const glm::mat4x4 & transformMat) <br> |
| virtual void | [**Translate**](classAIAC_1_1GOPrimitive.md#function-translate) (const glm::vec3 & translation) <br> |
| virtual  | [**~GOPrimitive**](classAIAC_1_1GOPrimitive.md#function-goprimitive) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::shared\_ptr&lt; [**GOCircle**](classAIAC_1_1GOCircle.md) &gt; | [**Add**](#function-add-12) ([**GOPoint**](classAIAC_1_1GOPoint.md) center, float radius) <br>_Add_ [_**GOCircle**_](classAIAC_1_1GOCircle.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOCircle**](classAIAC_1_1GOCircle.md) &gt; | [**Add**](#function-add-22) ([**GOPoint**](classAIAC_1_1GOPoint.md) center, glm::vec3 normal, float radius) <br> |
|  float | [**ClosestDistanceFromLineToCircle**](#function-closestdistancefromlinetocircle) (std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; ptrLine, const glm::vec3 & circleCenter, float circleRadius) <br>_This function calculates the closest distance from a line, defined by a point and a direction, to a circle in 3D space. If the line intersects the circle, the function returns 0, indicating the minimum distance is inside the circle._  |
|  std::pair&lt; float, std::pair&lt; glm::vec3, glm::vec3 &gt; &gt; | [**ClosestDistanceFromSegmentToCircle**](#function-closestdistancefromsegmenttocircle) (std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; ptrLine, const glm::vec3 & circleCenter, float circleRadius) <br>_This function calculates the closest distance from a segment. defined by two points, to a circle in 3D space._  |
|  glm::vec3 | [**ClosestPointToCircle**](#function-closestpointtocircle) (const glm::vec3 & point, const glm::vec3 & circleCenter, const glm::vec3 & circleNormal, float circleRadius) <br>_&lt; Static geometry functions_  |
|  std::shared\_ptr&lt; [**GOCircle**](classAIAC_1_1GOCircle.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOCircle**](classAIAC_1_1GOCircle.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


## Public Static Functions inherited from AIAC::GOPrimitive

See [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)

| Type | Name |
| ---: | :--- |
|  void | [**Remove**](classAIAC_1_1GOPrimitive.md#function-remove-12) (const uint32\_t & id) <br> |
|  void | [**Remove**](classAIAC_1_1GOPrimitive.md#function-remove-22) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |












## Protected Attributes inherited from AIAC::GOPrimitive

See [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)

| Type | Name |
| ---: | :--- |
|  glm::vec4 | [**m\_Color**](classAIAC_1_1GOPrimitive.md#variable-m_color)  <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GLObject**](classAIAC_1_1GLObject.md) &gt; &gt; | [**m\_GLObjects**](classAIAC_1_1GOPrimitive.md#variable-m_globjects)  <br> |
|  uint32\_t | [**m\_Id**](classAIAC_1_1GOPrimitive.md#variable-m_id)  <br> |
|  bool | [**m\_IsVisible**](classAIAC_1_1GOPrimitive.md#variable-m_isvisible)  <br> |
|  std::string | [**m\_Name**](classAIAC_1_1GOPrimitive.md#variable-m_name)  <br> |
|  bool | [**m\_State**](classAIAC_1_1GOPrimitive.md#variable-m_state)  <br> |
|  GOTypeFlags | [**m\_Type**](classAIAC_1_1GOPrimitive.md#variable-m_type)  <br> |
|  float | [**m\_Weight**](classAIAC_1_1GOPrimitive.md#variable-m_weight)   = `GOWeight::Default`<br> |






































## Public Functions Documentation




### function ClosestPointToPoint 

_Get the closest point to the circle from a given point._ 
```C++
glm::vec3 AIAC::GOCircle::ClosestPointToPoint (
    glm::vec3 point
) 
```





**Parameters:**


* `point` the point 



**Returns:**

glm::vec3 





        

<hr>



### function GetCenter 

```C++
inline GOPoint AIAC::GOCircle::GetCenter () const
```




<hr>



### function GetEdgeColor 

```C++
inline glm::vec4 AIAC::GOCircle::GetEdgeColor () const
```




<hr>



### function GetNormal 

```C++
inline glm::vec3 AIAC::GOCircle::GetNormal () const
```




<hr>



### function GetRadius 

```C++
inline float AIAC::GOCircle::GetRadius () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOCircle::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function SetCenter 

```C++
inline void AIAC::GOCircle::SetCenter (
    GOPoint center
) 
```




<hr>



### function SetEdgeColor 

```C++
inline void AIAC::GOCircle::SetEdgeColor (
    glm::vec4 edgeColor
) 
```




<hr>



### function SetNormal 

```C++
inline void AIAC::GOCircle::SetNormal (
    glm::vec3 normal
) 
```




<hr>



### function SetRadius 

```C++
inline void AIAC::GOCircle::SetRadius (
    float radius
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOCircle::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```



Implements [*AIAC::GOPrimitive::SetValueFrom*](classAIAC_1_1GOPrimitive.md#function-setvaluefrom)


<hr>



### function Transform 

```C++
inline virtual void AIAC::GOCircle::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function ~GOCircle 

```C++
virtual AIAC::GOCircle::~GOCircle () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/2]

_Add_ [_**GOCircle**_](classAIAC_1_1GOCircle.md) _to the scene._
```C++
static std::shared_ptr< GOCircle > AIAC::GOCircle::Add (
    GOPoint center,
    float radius
) 
```





**Parameters:**


* `center` Center of the circle. 
* `radius` Radius of the circle. 



**Returns:**

uint32\_t Id of the circle. 





        

<hr>



### function Add [2/2]

```C++
static std::shared_ptr< GOCircle > AIAC::GOCircle::Add (
    GOPoint center,
    glm::vec3 normal,
    float radius
) 
```




<hr>



### function ClosestDistanceFromLineToCircle 

_This function calculates the closest distance from a line, defined by a point and a direction, to a circle in 3D space. If the line intersects the circle, the function returns 0, indicating the minimum distance is inside the circle._ 
```C++
static inline float AIAC::GOCircle::ClosestDistanceFromLineToCircle (
    std::shared_ptr< GOLine > ptrLine,
    const glm::vec3 & circleCenter,
    float circleRadius
) 
```





**Parameters:**


* `ptrLine` the pointer to the line. 
* `circleCenter` The center of the circle. 
* `circleRadius` The radius of the circle. 



**Returns:**

The closest distance from the line to the circle 





        

<hr>



### function ClosestDistanceFromSegmentToCircle 

_This function calculates the closest distance from a segment. defined by two points, to a circle in 3D space._ 
```C++
static inline std::pair< float, std::pair< glm::vec3, glm::vec3 > > AIAC::GOCircle::ClosestDistanceFromSegmentToCircle (
    std::shared_ptr< GOLine > ptrLine,
    const glm::vec3 & circleCenter,
    float circleRadius
) 
```





**Parameters:**


* `ptrLine` the pointer to the line. 
* `circleCenter` The center of the circle. 
* `circleRadius` The radius of the circle. 



**Returns:**

The closest distance from the line to the circle and the closest point on the line and the circle 





        

<hr>



### function ClosestPointToCircle 

_&lt; Static geometry functions_ 
```C++
static inline glm::vec3 AIAC::GOCircle::ClosestPointToCircle (
    const glm::vec3 & point,
    const glm::vec3 & circleCenter,
    const glm::vec3 & circleNormal,
    float circleRadius
) 
```



Calculates the closest point on a circle to a given point in 3D.




**Parameters:**


* `point` The point from which to find the closest point on the circle. 
* `circleCenter` The center of the circle. 
* `circleNormal` The normal vector of the circle's plane. 
* `circleRadius` The radius of the circle. 



**Returns:**

The closest point on the circle to the given point. 





        

<hr>



### function Get 

```C++
static std::shared_ptr< GOCircle > AIAC::GOCircle::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOCircle > > AIAC::GOCircle::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

