

# Class AIAC::GOText



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOText**](classAIAC_1_1GOText.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  const [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetAnchor**](#function-getanchor) () const<br> |
|  const std::string | [**GetText**](#function-gettext) () const<br> |
|  const double | [**GetTextSize**](#function-gettextsize) () const<br> |
|  void | [**SetAnchor**](#function-setanchor-12) (const [**GOPoint**](classAIAC_1_1GOPoint.md) anchor) <br> |
|  void | [**SetAnchor**](#function-setanchor-22) (const glm::vec3 anchor) <br> |
|  void | [**SetText**](#function-settext) (const std::string text) <br> |
|  void | [**SetTextSize**](#function-settextsize) (const double size) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
|  [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) | [**operator\***](#function-operator) (const glm::mat4x4 & transformMat) <br> |
| virtual  | [**~GOText**](#function-gotext) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOText**](classAIAC_1_1GOText.md) &gt; | [**Add**](#function-add-12) () <br>_Add_ [_**GOText**_](classAIAC_1_1GOText.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOText**](classAIAC_1_1GOText.md) &gt; | [**Add**](#function-add-22) (std::string text, [**GOPoint**](classAIAC_1_1GOPoint.md) anchor, double size=GOTextSize::Default) <br> |
|  std::shared\_ptr&lt; [**GOText**](classAIAC_1_1GOText.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOText**](classAIAC_1_1GOText.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


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




### function GetAnchor 

```C++
inline const GOPoint AIAC::GOText::GetAnchor () const
```




<hr>



### function GetText 

```C++
inline const std::string AIAC::GOText::GetText () const
```




<hr>



### function GetTextSize 

```C++
inline const double AIAC::GOText::GetTextSize () const
```




<hr>



### function SetAnchor [1/2]

```C++
inline void AIAC::GOText::SetAnchor (
    const GOPoint anchor
) 
```




<hr>



### function SetAnchor [2/2]

```C++
inline void AIAC::GOText::SetAnchor (
    const glm::vec3 anchor
) 
```




<hr>



### function SetText 

```C++
inline void AIAC::GOText::SetText (
    const std::string text
) 
```




<hr>



### function SetTextSize 

```C++
inline void AIAC::GOText::SetTextSize (
    const double size
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOText::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```



Implements [*AIAC::GOPrimitive::SetValueFrom*](classAIAC_1_1GOPrimitive.md#function-setvaluefrom)


<hr>



### function Transform 

```C++
inline virtual void AIAC::GOText::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function operator\* 

```C++
inline GOPrimitive AIAC::GOText::operator* (
    const glm::mat4x4 & transformMat
) 
```




<hr>



### function ~GOText 

```C++
virtual AIAC::GOText::~GOText () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/2]

_Add_ [_**GOText**_](classAIAC_1_1GOText.md) _to the scene._
```C++
static std::shared_ptr< GOText > AIAC::GOText::Add () 
```





**Parameters:**


* `text` Text of the text. 
* `anchor` Anchor of the text. 
* `size` Size of the text. 



**Returns:**

uint32\_t Id of the text. 





        

<hr>



### function Add [2/2]

```C++
static std::shared_ptr< GOText > AIAC::GOText::Add (
    std::string text,
    GOPoint anchor,
    double size=GOTextSize::Default
) 
```




<hr>



### function Get 

```C++
static std::shared_ptr< GOText > AIAC::GOText::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOText > > AIAC::GOText::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

