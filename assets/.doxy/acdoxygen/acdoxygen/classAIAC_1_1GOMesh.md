

# Class AIAC::GOMesh



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GOMesh**](classAIAC_1_1GOMesh.md)








Inherits the following classes: [AIAC::GOPrimitive](classAIAC_1_1GOPrimitive.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  const std::vector&lt; glm::vec4 &gt; | [**GetColors**](#function-getcolors) () const<br> |
|  const std::vector&lt; uint32\_t &gt; | [**GetIndices**](#function-getindices) () const<br> |
|  const std::vector&lt; glm::vec3 &gt; | [**GetNormals**](#function-getnormals) () const<br> |
|  const std::vector&lt; glm::vec3 &gt; | [**GetVertices**](#function-getvertices) () const<br> |
| virtual void | [**InitGLObject**](#function-initglobject) () <br> |
|  void | [**SetColor**](#function-setcolor) (glm::vec4 color) <br> |
|  void | [**SetColors**](#function-setcolors) (std::vector&lt; glm::vec4 &gt; colors) <br> |
|  void | [**SetIndices**](#function-setindices) (std::vector&lt; uint32\_t &gt; indices) <br> |
|  void | [**SetNormals**](#function-setnormals) (std::vector&lt; glm::vec3 &gt; normals) <br> |
|  void | [**SetVertices**](#function-setvertices) (std::vector&lt; glm::vec3 &gt; vertices) <br> |
| virtual void | [**Transform**](#function-transform) (const glm::mat4x4 & transformMat) <br> |
|  [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) | [**operator\***](#function-operator) (const glm::mat4x4 & transformMat) <br> |
| virtual  | [**~GOMesh**](#function-gomesh) () = default<br> |


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
|  std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; | [**Add**](#function-add-12) () <br>_Add empty_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; | [**Add**](#function-add-22) (std::vector&lt; glm::vec3 &gt; vertices, std::vector&lt; uint32\_t &gt; indices) <br>_Add_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._ |
|  std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; | [**Get**](#function-get) (const uint32\_t & id) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; &gt; | [**GetAll**](#function-getall) () <br> |
|  std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; | [**LoadPly**](#function-loadply) (std::string path) <br>_Load .ply and add the corresponding_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._ |


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




### function GetColors 

```C++
inline const std::vector< glm::vec4 > AIAC::GOMesh::GetColors () const
```




<hr>



### function GetIndices 

```C++
inline const std::vector< uint32_t > AIAC::GOMesh::GetIndices () const
```




<hr>



### function GetNormals 

```C++
inline const std::vector< glm::vec3 > AIAC::GOMesh::GetNormals () const
```




<hr>



### function GetVertices 

```C++
inline const std::vector< glm::vec3 > AIAC::GOMesh::GetVertices () const
```




<hr>



### function InitGLObject 

```C++
virtual void AIAC::GOMesh::InitGLObject () 
```



Implements [*AIAC::GOPrimitive::InitGLObject*](classAIAC_1_1GOPrimitive.md#function-initglobject)


<hr>



### function SetColor 

```C++
inline void AIAC::GOMesh::SetColor (
    glm::vec4 color
) 
```




<hr>



### function SetColors 

```C++
inline void AIAC::GOMesh::SetColors (
    std::vector< glm::vec4 > colors
) 
```




<hr>



### function SetIndices 

```C++
inline void AIAC::GOMesh::SetIndices (
    std::vector< uint32_t > indices
) 
```




<hr>



### function SetNormals 

```C++
inline void AIAC::GOMesh::SetNormals (
    std::vector< glm::vec3 > normals
) 
```




<hr>



### function SetVertices 

```C++
inline void AIAC::GOMesh::SetVertices (
    std::vector< glm::vec3 > vertices
) 
```




<hr>



### function Transform 

```C++
inline virtual void AIAC::GOMesh::Transform (
    const glm::mat4x4 & transformMat
) 
```



Implements [*AIAC::GOPrimitive::Transform*](classAIAC_1_1GOPrimitive.md#function-transform)


<hr>



### function operator\* 

```C++
inline GOPrimitive AIAC::GOMesh::operator* (
    const glm::mat4x4 & transformMat
) 
```




<hr>



### function ~GOMesh 

```C++
virtual AIAC::GOMesh::~GOMesh () = default
```




<hr>
## Public Static Functions Documentation




### function Add [1/2]

_Add empty_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._
```C++
static std::shared_ptr< GOMesh > AIAC::GOMesh::Add () 
```




<hr>



### function Add [2/2]

_Add_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._
```C++
static std::shared_ptr< GOMesh > AIAC::GOMesh::Add (
    std::vector< glm::vec3 > vertices,
    std::vector< uint32_t > indices
) 
```





**Parameters:**


* `vertices` Vertices of the mesh. 
* `indices` Indices of the mesh. 



**Returns:**

uint32\_t Id of the mesh. 





        

<hr>



### function Get 

```C++
static std::shared_ptr< GOMesh > AIAC::GOMesh::Get (
    const uint32_t & id
) 
```




<hr>



### function GetAll 

```C++
static std::vector< std::shared_ptr< GOMesh > > AIAC::GOMesh::GetAll () 
```




<hr>



### function LoadPly 

_Load .ply and add the corresponding_ [_**GOMesh**_](classAIAC_1_1GOMesh.md) _to the scene._
```C++
static std::shared_ptr< GOMesh > AIAC::GOMesh::LoadPly (
    std::string path
) 
```





**Returns:**

uint32\_t Id of the mesh. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GOPrimitive.h`

