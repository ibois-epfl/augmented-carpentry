

# Class AIAC::GLPointObject



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GLPointObject**](classAIAC_1_1GLPointObject.md)








Inherits the following classes: [AIAC::GLObject](classAIAC_1_1GLObject.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  GLfloat | [**pointSize**](#variable-pointsize)  <br> |


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
|   | [**GLPointObject**](#function-glpointobject-13) () <br> |
|   | [**GLPointObject**](#function-glpointobject-23) (const std::vector&lt; glm::vec3 &gt; & vertices, const std::vector&lt; glm::vec4 &gt; & colors, GLfloat pointSize=1.0f) <br> |
|   | [**GLPointObject**](#function-glpointobject-33) (const [**GLPointObject**](classAIAC_1_1GLPointObject.md) & other) <br> |
|  [**GLPointObject**](classAIAC_1_1GLPointObject.md) & | [**operator=**](#function-operator) (const [**GLPointObject**](classAIAC_1_1GLPointObject.md) & other) <br> |


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




### variable pointSize 

```C++
GLfloat AIAC::GLPointObject::pointSize;
```




<hr>
## Public Functions Documentation




### function Draw 

```C++
virtual void AIAC::GLPointObject::Draw () 
```



Implements [*AIAC::GLObject::Draw*](classAIAC_1_1GLObject.md#function-draw)


<hr>



### function GLPointObject [1/3]

```C++
inline AIAC::GLPointObject::GLPointObject () 
```




<hr>



### function GLPointObject [2/3]

```C++
AIAC::GLPointObject::GLPointObject (
    const std::vector< glm::vec3 > & vertices,
    const std::vector< glm::vec4 > & colors,
    GLfloat pointSize=1.0f
) 
```




<hr>



### function GLPointObject [3/3]

```C++
inline AIAC::GLPointObject::GLPointObject (
    const GLPointObject & other
) 
```




<hr>



### function operator= 

```C++
inline GLPointObject & AIAC::GLPointObject::operator= (
    const GLPointObject & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/GLObject.h`

