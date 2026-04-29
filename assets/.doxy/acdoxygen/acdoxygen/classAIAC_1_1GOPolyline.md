

# Class AIAC::GOPolyline



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOPolyline**](classAIAC_1_1GOPolyline.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  const std::vector&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; & | [**GetPoints**](#function-getpoints) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  bool | [**IsClosed**](#function-isclosed) () const<br> |
|  void | [**SetClosed**](#function-setclosed) (bool isClosed) <br> |
|  void | [**SetPoints**](#function-setpoints-12) (std::vector&lt; glm::vec3 &gt; points) <br> |
|  void | [**SetPoints**](#function-setpoints-22) (std::vector&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; points) <br> |
|  void | [**SetWeight**](#function-setweight) (float weight) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
|  [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) | [**operator\***](#function-operator) (const glm::mat4x4 & transformMat) <br> |
| virtual  | [**~GOPolyline**](#function-gopolyline) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; | [**Add**](#function-add-13) () <br>_Add_ [_**GOPolyline**_](classAIAC_1_1GOPolyline.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; | [**Add**](#function-add-23) (std::vector&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; points, bool isClosed=false, float weight=GOWeight::Default) <br> |
|  std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; | [**Add**](#function-add-33) (std::vector&lt; glm::vec3 &gt; points, bool isClosed=false, float weight=GOWeight::Default) <br> |
|  std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


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




### function GetPoints 

```C++
inline const std::vector< GOPoint > & AIAC::GOPolyline::GetPoints () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOPolyline::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function IsClosed 

```C++
inline bool AIAC::GOPolyline::IsClosed () const
```




<hr>



### function SetClosed 

```C++
inline void AIAC::GOPolyline::SetClosed (
    bool isClosed
) 
```




<hr>



### function SetPoints [1/2]

```C++
inline void AIAC::GOPolyline::SetPoints (
    std::vector< glm::vec3 > points
) 
```




<hr>



### function SetPoints [2/2]

```C++
inline void AIAC::GOPolyline::SetPoints (
    std::vector< GOPoint > points
) 
```




<hr>



### function SetWeight 

```C++
inline void AIAC::GOPolyline::SetWeight (
    float weight
) 
```




<hr>



### function Transform 

```C++
inline virtual void AIAC::GOPolyline::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function operator\* 

```C++
inline GOPrimitive AIAC::GOPolyline::operator* (
    const glm::mat4x4 & transformMat
) 
```




<hr>



### function ~GOPolyline 

```C++
virtual AIAC::GOPolyline::~GOPolyline () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/3]

_Add_ [_**GOPolyline**_](classAIAC_1_1GOPolyline.md) _to the scene._
```C++
static std::shared_ptr< GOPolyline > AIAC::GOPolyline::Add () 
```





**Parameters:**


* `points` Points of the polyline. 



**Returns:**

uint32\_t Id of the polyline. 





        

<hr>



### function Add [2/3]

```C++
static std::shared_ptr< GOPolyline > AIAC::GOPolyline::Add (
    std::vector< GOPoint > points,
    bool isClosed=false,
    float weight=GOWeight::Default
) 
```




<hr>



### function Add [3/3]

```C++
static std::shared_ptr< GOPolyline > AIAC::GOPolyline::Add (
    std::vector< glm::vec3 > points,
    bool isClosed=false,
    float weight=GOWeight::Default
) 
```




<hr>



### function Get 

```C++
static std::shared_ptr< GOPolyline > AIAC::GOPolyline::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOPolyline > > AIAC::GOPolyline::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

