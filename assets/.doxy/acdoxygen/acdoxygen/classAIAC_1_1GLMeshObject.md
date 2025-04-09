

# Class AIAC::GLMeshObject



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GLMeshObject**](classAIAC_1_1GLMeshObject.md)








Inherits the following classes: [AIAC::GLObject](classAIAC_1_1GLObject.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  GLuint | [**indexBuf**](#variable-indexbuf)  <br> |
|  std::vector&lt; glm::vec4 &gt; | [**m\_Colors**](#variable-m_colors)  <br> |
|  std::vector&lt; uint32\_t &gt; | [**m\_Indices**](#variable-m_indices)  <br> |
|  std::vector&lt; glm::vec3 &gt; | [**m\_Vertices**](#variable-m_vertices)  <br> |


## Public Attributes inherited from AIAC::GLObject

See [AIAC::GLObject](classAIAC_1_1GLObject.md)

| Type | Name |
| ---: | :--- |
|  GLuint | [**colorBuf**](classAIAC_1_1GLObject.md#variable-colorbuf)  <br> |
|  GLsizei | [**size**](classAIAC_1_1GLObject.md#variable-size)  <br> |
|  GLObjectType | [**type**](classAIAC_1_1GLObject.md#variable-type)  <br> |
|  GLuint | [**vertexBuf**](classAIAC_1_1GLObject.md#variable-vertexbuf)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Draw**](#function-draw) () <br> |
|   | [**GLMeshObject**](#function-glmeshobject-13) () <br> |
|   | [**GLMeshObject**](#function-glmeshobject-23) (const std::vector&lt; glm::vec3 &gt; & vertices, const std::vector&lt; glm::vec4 &gt; & colors, const std::vector&lt; uint32\_t &gt; & indices) <br> |
|   | [**GLMeshObject**](#function-glmeshobject-33) (const [**GLMeshObject**](classAIAC_1_1GLMeshObject.md) & other) <br> |
|  [**GLMeshObject**](classAIAC_1_1GLMeshObject.md) & | [**operator=**](#function-operator) (const [**GLMeshObject**](classAIAC_1_1GLMeshObject.md) & other) <br> |


## Public Functions inherited from AIAC::GLObject

See [AIAC::GLObject](classAIAC_1_1GLObject.md)

| Type | Name |
| ---: | :--- |
|  void | [**DeleteVBOs**](classAIAC_1_1GLObject.md#function-deletevbos) () <br> |
| virtual void | [**Draw**](classAIAC_1_1GLObject.md#function-draw) () = 0<br> |
|   | [**GLObject**](classAIAC_1_1GLObject.md#function-globject-12) () = default<br> |
|   | [**GLObject**](classAIAC_1_1GLObject.md#function-globject-22) (const [**GLObject**](classAIAC_1_1GLObject.md) & other) <br> |
|  [**GLObject**](classAIAC_1_1GLObject.md) & | [**operator=**](classAIAC_1_1GLObject.md#function-operator) (const [**GLObject**](classAIAC_1_1GLObject.md) & other) <br> |
|   | [**~GLObject**](classAIAC_1_1GLObject.md#function-globject) () <br> |
















































## Protected Functions inherited from AIAC::GLObject

See [AIAC::GLObject](classAIAC_1_1GLObject.md)

| Type | Name |
| ---: | :--- |
|  void | [**BindVBOs**](classAIAC_1_1GLObject.md#function-bindvbos) () <br> |
|  void | [**BufferData**](classAIAC_1_1GLObject.md#function-bufferdata) (const std::vector&lt; glm::vec3 &gt; & vertices, const std::vector&lt; glm::vec4 &gt; & colors) <br> |






## Public Attributes Documentation




### variable indexBuf 

```C++
GLuint AIAC::GLMeshObject::indexBuf;
```




<hr>



### variable m\_Colors 

```C++
std::vector<glm::vec4> AIAC::GLMeshObject::m_Colors;
```




<hr>



### variable m\_Indices 

```C++
std::vector<uint32_t> AIAC::GLMeshObject::m_Indices;
```




<hr>



### variable m\_Vertices 

```C++
std::vector<glm::vec3> AIAC::GLMeshObject::m_Vertices;
```




<hr>
## Public Functions Documentation




### function Draw 

```C++
virtual void AIAC::GLMeshObject::Draw () 
```



Implements [*AIAC::GLObject::Draw*](classAIAC_1_1GLObject.md#function-draw)


<hr>



### function GLMeshObject [1/3]

```C++
inline AIAC::GLMeshObject::GLMeshObject () 
```




<hr>



### function GLMeshObject [2/3]

```C++
AIAC::GLMeshObject::GLMeshObject (
    const std::vector< glm::vec3 > & vertices,
    const std::vector< glm::vec4 > & colors,
    const std::vector< uint32_t > & indices
) 
```




<hr>



### function GLMeshObject [3/3]

```C++
inline AIAC::GLMeshObject::GLMeshObject (
    const GLMeshObject & other
) 
```




<hr>



### function operator= 

```C++
inline GLMeshObject & AIAC::GLMeshObject::operator= (
    const GLMeshObject & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/GLObject.h`

