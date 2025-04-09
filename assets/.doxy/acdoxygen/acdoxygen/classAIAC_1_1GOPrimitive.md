

# Class AIAC::GOPrimitive



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOPrimitive**](classAIAC_1_1GOPrimitive.md)










Inherited by the following classes: [AIAC::GOCircle](classAIAC_1_1GOCircle.md),  [AIAC::GOCylinder](classAIAC_1_1GOCylinder.md),  [AIAC::GOLine](classAIAC_1_1GOLine.md),  [AIAC::GOMesh](classAIAC_1_1GOMesh.md),  [AIAC::GOPoint](classAIAC_1_1GOPoint.md),  [AIAC::GOPolyline](classAIAC_1_1GOPolyline.md),  [AIAC::GOText](classAIAC_1_1GOText.md),  [AIAC::GOTriangle](classAIAC_1_1GOTriangle.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearGLObject**](#function-clearglobject) () <br> |
|  void | [**Draw**](#function-draw) () <br> |
|   | [**GOPrimitive**](#function-goprimitive) (bool isVisible=true, glm::vec4 color=glm::vec4(0, 0, 0, 1.0)) <br> |
|  uint32\_t | [**GenerateId**](#function-generateid) () <br> |
|  glm::vec4 | [**GetColor**](#function-getcolor) () const<br> |
|  uint32\_t | [**GetId**](#function-getid) () <br> |
|  std::string | [**GetName**](#function-getname) () const<br> |
|  bool | [**GetState**](#function-getstate) () <br> |
|  GOTypeFlags | [**GetType**](#function-gettype) () <br> |
|  bool | [**GetVisibility**](#function-getvisibility) () <br> |
|  float | [**GetWeight**](#function-getweight) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  bool | [**IsVisible**](#function-isvisible) () const<br> |
|  void | [**SetColor**](#function-setcolor) (glm::vec4 color) <br> |
|  void | [**SetName**](#function-setname) (std::string name) <br> |
|  void | [**SetState**](#function-setstate) (bool state) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
|  void | [**SetVisibility**](#function-setvisibility) (bool isVisible) <br> |
|  int | [**SetWeight**](#function-setweight) (float weight) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
| virtual void | [**Translate**](#function-translate) (const glm::vec3 & translation) <br> |
| virtual  | [**~GOPrimitive**](#function-goprimitive) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Remove**](#function-remove-12) (const uint32\_t & id) <br> |
|  void | [**Remove**](#function-remove-22) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec4 | [**m\_Color**](#variable-m_color)  <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GLObject**](classAIAC_1_1GLObject.md) &gt; &gt; | [**m\_GLObjects**](#variable-m_globjects)  <br> |
|  uint32\_t | [**m\_Id**](#variable-m_id)  <br> |
|  bool | [**m\_IsVisible**](#variable-m_isvisible)  <br> |
|  std::string | [**m\_Name**](#variable-m_name)  <br> |
|  bool | [**m\_State**](#variable-m_state)  <br> |
|  GOTypeFlags | [**m\_Type**](#variable-m_type)  <br> |
|  float | [**m\_Weight**](#variable-m_weight)   = `GOWeight::Default`<br> |




















## Public Functions Documentation




### function ClearGLObject 

```C++
void AIAC::GOPrimitive::ClearGLObject () 
```




<hr>



### function Draw 

```C++
inline void AIAC::GOPrimitive::Draw () 
```




<hr>



### function GOPrimitive 

```C++
explicit AIAC::GOPrimitive::GOPrimitive (
    bool isVisible=true,
    glm::vec4 color=glm::vec4(0, 0, 0, 1.0)
) 
```




<hr>



### function GenerateId 

```C++
uint32_t AIAC::GOPrimitive::GenerateId () 
```




<hr>



### function GetColor 

```C++
inline glm::vec4 AIAC::GOPrimitive::GetColor () const
```




<hr>



### function GetId 

```C++
inline uint32_t AIAC::GOPrimitive::GetId () 
```




<hr>



### function GetName 

```C++
inline std::string AIAC::GOPrimitive::GetName () const
```




<hr>



### function GetState 

```C++
inline bool AIAC::GOPrimitive::GetState () 
```




<hr>



### function GetType 

```C++
inline GOTypeFlags AIAC::GOPrimitive::GetType () 
```




<hr>



### function GetVisibility 

```C++
inline bool AIAC::GOPrimitive::GetVisibility () 
```




<hr>



### function GetWeight 

```C++
inline float AIAC::GOPrimitive::GetWeight () const
```




<hr>



### function InitGLObject 

```C++
inline virtual void AIAC::GOPrimitive::InitGLObject () 
```




<hr>



### function IsVisible 

```C++
inline bool AIAC::GOPrimitive::IsVisible () const
```




<hr>



### function SetColor 

```C++
inline void AIAC::GOPrimitive::SetColor (
    glm::vec4 color
) 
```




<hr>



### function SetName 

```C++
inline void AIAC::GOPrimitive::SetName (
    std::string name
) 
```




<hr>



### function SetState 

```C++
inline void AIAC::GOPrimitive::SetState (
    bool state
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOPrimitive::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```




<hr>



### function SetVisibility 

```C++
inline void AIAC::GOPrimitive::SetVisibility (
    bool isVisible
) 
```




<hr>



### function SetWeight 

```C++
inline int AIAC::GOPrimitive::SetWeight (
    float weight
) 
```




<hr>



### function Transform 

```C++
inline virtual void AIAC::GOPrimitive::Transform (
    const glm::mat4x4 & transformMat
) 
```




<hr>



### function Translate 

```C++
inline virtual void AIAC::GOPrimitive::Translate (
    const glm::vec3 & translation
) 
```




<hr>



### function ~GOPrimitive 

```C++
virtual AIAC::GOPrimitive::~GOPrimitive () = default
```




<hr>
## Public Static Functions Documentation




### function Remove [1/2]

```C++
static void AIAC::GOPrimitive::Remove (
    const uint32_t & id
) 
```




<hr>



### function Remove [2/2]

```C++
static void AIAC::GOPrimitive::Remove (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_Color 

```C++
glm::vec4 AIAC::GOPrimitive::m_Color;
```




<hr>



### variable m\_GLObjects 

```C++
std::vector<std::shared_ptr<GLObject> > AIAC::GOPrimitive::m_GLObjects;
```




<hr>



### variable m\_Id 

```C++
uint32_t AIAC::GOPrimitive::m_Id;
```




<hr>



### variable m\_IsVisible 

```C++
bool AIAC::GOPrimitive::m_IsVisible;
```




<hr>



### variable m\_Name 

```C++
std::string AIAC::GOPrimitive::m_Name;
```




<hr>



### variable m\_State 

```C++
bool AIAC::GOPrimitive::m_State;
```




<hr>



### variable m\_Type 

```C++
GOTypeFlags AIAC::GOPrimitive::m_Type;
```




<hr>



### variable m\_Weight 

```C++
float AIAC::GOPrimitive::m_Weight;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

