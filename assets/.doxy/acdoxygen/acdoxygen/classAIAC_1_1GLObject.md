

# Class AIAC::GLObject



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GLObject**](classAIAC_1_1GLObject.md)










Inherited by the following classes: [AIAC::GLLineObject](classAIAC_1_1GLLineObject.md),  [AIAC::GLMeshObject](classAIAC_1_1GLMeshObject.md),  [AIAC::GLPointObject](classAIAC_1_1GLPointObject.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  GLuint | [**colorBuf**](#variable-colorbuf)  <br> |
|  GLsizei | [**size**](#variable-size)  <br> |
|  GLObjectType | [**type**](#variable-type)  <br> |
|  GLuint | [**vertexBuf**](#variable-vertexbuf)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DeleteVBOs**](#function-deletevbos) () <br> |
| virtual void | [**Draw**](#function-draw) () = 0<br> |
|   | [**GLObject**](#function-globject-12) () = default<br> |
|   | [**GLObject**](#function-globject-22) (const [**GLObject**](classAIAC_1_1GLObject.md) & other) <br> |
|  [**GLObject**](classAIAC_1_1GLObject.md) & | [**operator=**](#function-operator) (const [**GLObject**](classAIAC_1_1GLObject.md) & other) <br> |
|   | [**~GLObject**](#function-globject) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**BindVBOs**](#function-bindvbos) () <br> |
|  void | [**BufferData**](#function-bufferdata) (const std::vector&lt; glm::vec3 &gt; & vertices, const std::vector&lt; glm::vec4 &gt; & colors) <br> |




## Public Attributes Documentation




### variable colorBuf 

```C++
GLuint AIAC::GLObject::colorBuf;
```




<hr>



### variable size 

```C++
GLsizei AIAC::GLObject::size;
```




<hr>



### variable type 

```C++
GLObjectType AIAC::GLObject::type;
```




<hr>



### variable vertexBuf 

```C++
GLuint AIAC::GLObject::vertexBuf;
```




<hr>
## Public Functions Documentation




### function DeleteVBOs 

```C++
void AIAC::GLObject::DeleteVBOs () 
```




<hr>



### function Draw 

```C++
virtual void AIAC::GLObject::Draw () = 0
```




<hr>



### function GLObject [1/2]

```C++
AIAC::GLObject::GLObject () = default
```




<hr>



### function GLObject [2/2]

```C++
inline AIAC::GLObject::GLObject (
    const GLObject & other
) 
```




<hr>



### function operator= 

```C++
inline GLObject & AIAC::GLObject::operator= (
    const GLObject & other
) 
```




<hr>



### function ~GLObject 

```C++
inline AIAC::GLObject::~GLObject () 
```




<hr>
## Protected Functions Documentation




### function BindVBOs 

```C++
void AIAC::GLObject::BindVBOs () 
```




<hr>



### function BufferData 

```C++
void AIAC::GLObject::BufferData (
    const std::vector< glm::vec3 > & vertices,
    const std::vector< glm::vec4 > & colors
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/GLObject.h`

