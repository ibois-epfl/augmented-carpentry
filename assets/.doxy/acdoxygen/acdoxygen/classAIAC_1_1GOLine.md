

# Class AIAC::GOLine



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOLine**](classAIAC_1_1GOLine.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  float | [**ComputeAngle**](#function-computeangle) (std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; ptrGO2) <br>_Compute the angle between the current line object and another one._  |
|  float | [**ComputeSignedAngle**](#function-computesignedangle) (std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; ptrGO2) <br>_Compute the angle between the current line object and another one with a sign._  |
|  void | [**ExtendBothEnds**](#function-extendbothends) (float length) <br> |
|  void | [**ExtendFromEnd**](#function-extendfromend) (float length) <br> |
|  void | [**ExtendFromStart**](#function-extendfromstart) (float length) <br> |
|  float | [**GetLength**](#function-getlength) () const<br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetMidPoint**](#function-getmidpoint) () const<br> |
|  glm::vec3 | [**GetMidPointValues**](#function-getmidpointvalues) () const<br> |
|  glm::vec3 | [**GetNormalValues**](#function-getnormalvalues) () const<br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetPEnd**](#function-getpend) () const<br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetPStart**](#function-getpstart) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  void | [**SetPEnd**](#function-setpend) ([**GOPoint**](classAIAC_1_1GOPoint.md) pEnd) <br> |
|  void | [**SetPStart**](#function-setpstart) ([**GOPoint**](classAIAC_1_1GOPoint.md) pStart) <br> |
|  void | [**SetPts**](#function-setpts) ([**GOPoint**](classAIAC_1_1GOPoint.md) pStart, [**GOPoint**](classAIAC_1_1GOPoint.md) pEnd) <br> |
| virtual void | [**SetValueFrom**](#function-setvaluefrom) (const std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; & ptrGO) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
| virtual void | [**Translate**](#function-translate) (const glm::vec3 & translation) <br> |
| virtual  | [**~GOLine**](#function-goline) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**Add**](#function-add-12) () <br> |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**Add**](#function-add-22) ([**GOPoint**](classAIAC_1_1GOPoint.md) p1, [**GOPoint**](classAIAC_1_1GOPoint.md) p2, float weight=GOWeight::Default) <br>_Add_ [_**GOLine**_](classAIAC_1_1GOLine.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |


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




### function ComputeAngle 

_Compute the angle between the current line object and another one._ 
```C++
float AIAC::GOLine::ComputeAngle (
    std::shared_ptr< GOLine > ptrGO2
) 
```





**Parameters:**


* `ptrGO2` the second line 



**Returns:**

float the angle in degrees 





        

<hr>



### function ComputeSignedAngle 

_Compute the angle between the current line object and another one with a sign._ 
```C++
float AIAC::GOLine::ComputeSignedAngle (
    std::shared_ptr< GOLine > ptrGO2
) 
```





**Parameters:**


* `ptrGO2` the second line 



**Returns:**

float the angle in degrees 





        

<hr>



### function ExtendBothEnds 

```C++
inline void AIAC::GOLine::ExtendBothEnds (
    float length
) 
```




<hr>



### function ExtendFromEnd 

```C++
inline void AIAC::GOLine::ExtendFromEnd (
    float length
) 
```




<hr>



### function ExtendFromStart 

```C++
inline void AIAC::GOLine::ExtendFromStart (
    float length
) 
```




<hr>



### function GetLength 

```C++
inline float AIAC::GOLine::GetLength () const
```




<hr>



### function GetMidPoint 

```C++
inline GOPoint AIAC::GOLine::GetMidPoint () const
```




<hr>



### function GetMidPointValues 

```C++
inline glm::vec3 AIAC::GOLine::GetMidPointValues () const
```




<hr>



### function GetNormalValues 

```C++
inline glm::vec3 AIAC::GOLine::GetNormalValues () const
```




<hr>



### function GetPEnd 

```C++
inline GOPoint AIAC::GOLine::GetPEnd () const
```




<hr>



### function GetPStart 

```C++
inline GOPoint AIAC::GOLine::GetPStart () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOLine::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function SetPEnd 

```C++
inline void AIAC::GOLine::SetPEnd (
    GOPoint pEnd
) 
```




<hr>



### function SetPStart 

```C++
inline void AIAC::GOLine::SetPStart (
    GOPoint pStart
) 
```




<hr>



### function SetPts 

```C++
inline void AIAC::GOLine::SetPts (
    GOPoint pStart,
    GOPoint pEnd
) 
```




<hr>



### function SetValueFrom 

```C++
inline virtual void AIAC::GOLine::SetValueFrom (
    const std::shared_ptr< GOPrimitive > & ptrGO
) 
```



Implements [*AIAC::GOPrimitive::SetValueFrom*](classAIAC_1_1GOPrimitive.md#function-setvaluefrom)


<hr>



### function Transform 

```C++
inline virtual void AIAC::GOLine::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function Translate 

```C++
inline virtual void AIAC::GOLine::Translate (
    const glm::vec3 & translation
) 
```



Implements [*AIAC::GOPrimitive::Translate*](classAIAC_1_1GOPrimitive.md#function-translate)


<hr>



### function ~GOLine 

```C++
virtual AIAC::GOLine::~GOLine () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/2]

```C++
static std::shared_ptr< GOLine > AIAC::GOLine::Add () 
```




<hr>



### function Add [2/2]

_Add_ [_**GOLine**_](classAIAC_1_1GOLine.md) _to the scene._
```C++
static std::shared_ptr< GOLine > AIAC::GOLine::Add (
    GOPoint p1,
    GOPoint p2,
    float weight=GOWeight::Default
) 
```





**Parameters:**


* `p1` First point of the line. 
* `p2` Second point of the line. 
* `weight` Weight of the line. 



**Returns:**

uint32\_t Id of the line. 





        

<hr>



### function Get 

```C++
static std::shared_ptr< GOLine > AIAC::GOLine::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOLine > > AIAC::GOLine::GetAll () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

