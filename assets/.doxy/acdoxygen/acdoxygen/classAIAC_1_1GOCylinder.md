

# Class AIAC::GOCylinder



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOCylinder**](classAIAC_1_1GOCylinder.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  glm::vec4 | [**GetEdgeColor**](#function-getedgecolor) () const<br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetPEnd**](#function-getpend) () const<br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetPStart**](#function-getpstart) () const<br> |
|  float | [**GetRadius**](#function-getradius) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  void | [**SetEdgeColor**](#function-setedgecolor) (glm::vec4 edgeColor) <br> |
|  void | [**SetPEnd**](#function-setpend) ([**GOPoint**](classAIAC_1_1GOPoint.md) pEnd) <br> |
|  void | [**SetPStart**](#function-setpstart) ([**GOPoint**](classAIAC_1_1GOPoint.md) pStart) <br> |
|  void | [**SetRadius**](#function-setradius) (float radius) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
| virtual  | [**~GOCylinder**](#function-gocylinder) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOCylinder**](classAIAC_1_1GOCylinder.md) &gt; | [**Add**](#function-add) ([**GOPoint**](classAIAC_1_1GOPoint.md) p1, [**GOPoint**](classAIAC_1_1GOPoint.md) p2, float radius) <br>_Add_ [_**GOCylinder**_](classAIAC_1_1GOCylinder.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOCylinder**](classAIAC_1_1GOCylinder.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOCylinder**](classAIAC_1_1GOCylinder.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


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




### function GetEdgeColor 

```C++
inline glm::vec4 AIAC::GOCylinder::GetEdgeColor () const
```




<hr>



### function GetPEnd 

```C++
inline GOPoint AIAC::GOCylinder::GetPEnd () const
```




<hr>



### function GetPStart 

```C++
inline GOPoint AIAC::GOCylinder::GetPStart () const
```




<hr>



### function GetRadius 

```C++
inline float AIAC::GOCylinder::GetRadius () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOCylinder::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function SetEdgeColor 

```C++
inline void AIAC::GOCylinder::SetEdgeColor (
    glm::vec4 edgeColor
) 
```




<hr>



### function SetPEnd 

```C++
inline void AIAC::GOCylinder::SetPEnd (
    GOPoint pEnd
) 
```




<hr>



### function SetPStart 

```C++
inline void AIAC::GOCylinder::SetPStart (
    GOPoint pStart
) 
```




<hr>



### function SetRadius 

```C++
inline void AIAC::GOCylinder::SetRadius (
    float radius
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOCylinder::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```



Implements [*AIAC::GOPrimitive::SetValueFrom*](classAIAC_1_1GOPrimitive.md#function-setvaluefrom)


<hr>



### function Transform 

```C++
inline virtual void AIAC::GOCylinder::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function ~GOCylinder 

```C++
virtual AIAC::GOCylinder::~GOCylinder () = default
```




<hr>
## Public Static Functions Documentation




### function Add 

_Add_ [_**GOCylinder**_](classAIAC_1_1GOCylinder.md) _to the scene._
```C++
static std::shared_ptr< GOCylinder > AIAC::GOCylinder::Add (
    GOPoint p1,
    GOPoint p2,
    float radius
) 
```





**Parameters:**


* `p1` First point of the cylinder. 
* `p2` Second point of the cylinder. 
* `radius` Radius of the cylinder. 



**Returns:**

uint32\_t Id of the cylinder. 





        

<hr>



### function Get 

```C++
static std::shared_ptr< GOCylinder > AIAC::GOCylinder::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOCylinder > > AIAC::GOCylinder::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

