

# Class AIAC::GLLineObject



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GLLineObject**](classAIAC_1_1GLLineObject.md)








Inherits the following classes: [AIAC::GLObject](classAIAC_1_1GLObject.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  GLfloat | [**lineWidth**](#variable-linewidth)  <br> |


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
|   | [**GLLineObject**](#function-gllineobject-13) () <br> |
|   | [**GLLineObject**](#function-gllineobject-23) (const std::vector&lt; glm::vec3 &gt; & vertices, const std::vector&lt; glm::vec4 &gt; & colors, GLfloat lineWidth=1.0f) <br> |
|   | [**GLLineObject**](#function-gllineobject-33) (const [**GLLineObject**](classAIAC_1_1GLLineObject.md) & other) <br> |
|  [**GLLineObject**](classAIAC_1_1GLLineObject.md) & | [**operator=**](#function-operator) (const [**GLLineObject**](classAIAC_1_1GLLineObject.md) & other) <br> |


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




### variable lineWidth 

```C++
GLfloat AIAC::GLLineObject::lineWidth;
```




<hr>
## Public Functions Documentation




### function Draw 

```C++
virtual void AIAC::GLLineObject::Draw () 
```



Implements [*AIAC::GLObject::Draw*](classAIAC_1_1GLObject.md#function-draw)


<hr>



### function GLLineObject [1/3]

```C++
inline AIAC::GLLineObject::GLLineObject () 
```




<hr>



### function GLLineObject [2/3]

```C++
AIAC::GLLineObject::GLLineObject (
    const std::vector< glm::vec3 > & vertices,
    const std::vector< glm::vec4 > & colors,
    GLfloat lineWidth=1.0f
) 
```




<hr>



### function GLLineObject [3/3]

```C++
inline AIAC::GLLineObject::GLLineObject (
    const GLLineObject & other
) 
```




<hr>



### function operator= 

```C++
inline GLLineObject & AIAC::GLLineObject::operator= (
    const GLLineObject & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/GLObject.h`

