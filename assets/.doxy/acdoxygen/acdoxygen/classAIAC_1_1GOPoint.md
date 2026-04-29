

# Class AIAC::GOPoint



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOPoint**](classAIAC_1_1GOPoint.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  float | [**DistanceTo**](#function-distanceto) (const [**GOPoint**](classAIAC_1_1GOPoint.md) & point) const<br> |
|   | [**GOPoint**](#function-gopoint-13) () = default<br> |
|   | [**GOPoint**](#function-gopoint-23) (float x, float y, float z, float weight=GOWeight::Default) <br> |
|   | [**GOPoint**](#function-gopoint-33) (glm::vec3 position, float weight=GOWeight::Default) <br> |
|  glm::vec3 | [**GetPosition**](#function-getposition) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  void | [**SetPosition**](#function-setposition) (glm::vec3 position) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
|  void | [**SetWeight**](#function-setweight) (float weight) <br> |
|  void | [**SetX**](#function-setx) (float x) <br> |
|  void | [**SetY**](#function-sety) (float y) <br> |
|  void | [**SetZ**](#function-setz) (float z) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
|  float | [**X**](#function-x) () const<br> |
|  float | [**Y**](#function-y) () const<br> |
|  float | [**Z**](#function-z) () const<br> |
|   | [**vec3**](#function-vec3) () const<br> |
| virtual  | [**~GOPoint**](#function-gopoint) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**Add**](#function-add-12) (float x, float y, float z, float weight=GOWeight::Default) <br>_Add_ [_**GOPoint**_](classAIAC_1_1GOPoint.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**Add**](#function-add-22) (glm::vec3 position, float weight=GOWeight::Default) <br> |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


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




### function DistanceTo 

```C++
inline float AIAC::GOPoint::DistanceTo (
    const GOPoint & point
) const
```




<hr>



### function GOPoint [1/3]

```C++
AIAC::GOPoint::GOPoint () = default
```




<hr>



### function GOPoint [2/3]

```C++
AIAC::GOPoint::GOPoint (
    float x,
    float y,
    float z,
    float weight=GOWeight::Default
) 
```




<hr>



### function GOPoint [3/3]

```C++
AIAC::GOPoint::GOPoint (
    glm::vec3 position,
    float weight=GOWeight::Default
) 
```




<hr>



### function GetPosition 

```C++
inline glm::vec3 AIAC::GOPoint::GetPosition () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOPoint::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function SetPosition 

```C++
inline void AIAC::GOPoint::SetPosition (
    glm::vec3 position
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOPoint::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```



Implements [*AIAC::GOPrimitive::SetValueFrom*](classAIAC_1_1GOPrimitive.md#function-setvaluefrom)


<hr>



### function SetWeight 

```C++
inline void AIAC::GOPoint::SetWeight (
    float weight
) 
```




<hr>



### function SetX 

```C++
inline void AIAC::GOPoint::SetX (
    float x
) 
```




<hr>



### function SetY 

```C++
inline void AIAC::GOPoint::SetY (
    float y
) 
```




<hr>



### function SetZ 

```C++
inline void AIAC::GOPoint::SetZ (
    float z
) 
```




<hr>



### function Transform 

```C++
inline virtual void AIAC::GOPoint::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function X 

```C++
inline float AIAC::GOPoint::X () const
```




<hr>



### function Y 

```C++
inline float AIAC::GOPoint::Y () const
```




<hr>



### function Z 

```C++
inline float AIAC::GOPoint::Z () const
```




<hr>



### function vec3 

```C++
inline AIAC::GOPoint::vec3 () const
```




<hr>



### function ~GOPoint 

```C++
virtual AIAC::GOPoint::~GOPoint () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/2]

_Add_ [_**GOPoint**_](classAIAC_1_1GOPoint.md) _to the scene._
```C++
static std::shared_ptr< GOPoint > AIAC::GOPoint::Add (
    float x,
    float y,
    float z,
    float weight=GOWeight::Default
) 
```





**Parameters:**


* `x` X coordinate of the point. 
* `y` Y coordinate of the point. 
* `z` Z coordinate of the point. 
* `weight` Weight of the point. 



**Returns:**

uint32\_t Id of the point. 





        

<hr>



### function Add [2/2]

```C++
static std::shared_ptr< GOPoint > AIAC::GOPoint::Add (
    glm::vec3 position,
    float weight=GOWeight::Default
) 
```




<hr>



### function Get 

```C++
static std::shared_ptr< GOPoint > AIAC::GOPoint::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOPoint > > AIAC::GOPoint::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

