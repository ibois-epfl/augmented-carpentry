

# Class AIAC::TextRenderer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TextRenderer**](classAIAC_1_1TextRenderer.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; char, [**Character**](structAIAC_1_1Character.md) &gt; | [**Characters**](#variable-characters)  <br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TextRenderer**](#function-textrenderer) () = default<br> |
|   | [**~TextRenderer**](#function-textrenderer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Init**](#function-init) () <br>_Initialize the static_ [_**TextRenderer**_](classAIAC_1_1TextRenderer.md) _instance._ |
|  void | [**RenderTextIn3DSpace**](#function-rendertextin3dspace) (std::string text, glm::vec3 position, glm::vec4 color, float scale=1.0f) <br>_Render text in the 3D space, but always facing the screen._  |
|  void | [**SetProjection**](#function-setprojection) (glm::mat4 projection) <br>_set the projection matrix for rendering text in 3D space_  |


























## Public Static Attributes Documentation




### variable Characters 

```C++
std::map< char, Character > AIAC::TextRenderer::Characters;
```




<hr>
## Public Functions Documentation




### function TextRenderer 

```C++
AIAC::TextRenderer::TextRenderer () = default
```




<hr>



### function ~TextRenderer 

```C++
AIAC::TextRenderer::~TextRenderer () = default
```




<hr>
## Public Static Functions Documentation




### function Init 

_Initialize the static_ [_**TextRenderer**_](classAIAC_1_1TextRenderer.md) _instance._
```C++
static void AIAC::TextRenderer::Init () 
```




<hr>



### function RenderTextIn3DSpace 

_Render text in the 3D space, but always facing the screen._ 
```C++
static void AIAC::TextRenderer::RenderTextIn3DSpace (
    std::string text,
    glm::vec3 position,
    glm::vec4 color,
    float scale=1.0f
) 
```





**Parameters:**


* `text` Text to show 
* `position` The anchor of the text 
* `color` Text color 
* `projection` The final MVP projection of the scene to show 
* `scale` Text scale, default = 1.0f 




        

<hr>



### function SetProjection 

_set the projection matrix for rendering text in 3D space_ 
```C++
static inline void AIAC::TextRenderer::SetProjection (
    glm::mat4 projection
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/TextRenderer.h`

