

# Class AIAC::Image



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Image**](classAIAC_1_1Image.md)



_Class representing the main iamge object for AC._ 

* `#include <Image.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DeleteGlTexture**](#function-deletegltexture) () <br>_Delete the OpenGL texture object._  |
|  const cv::Mat | [**GetCvMat**](#function-getcvmat) () const<br>_Get the OpenCV matrix of the image._  |
|  GLuint | [**GetGlTextureObj**](#function-getgltextureobj) () <br>_Get the OpenGL texture object of the image._  |
|  int | [**GetHeight**](#function-getheight) () const<br>_Get the height of the image._  |
|  [**ImTexture**](structAIAC_1_1ImTexture.md) | [**GetImTexture**](#function-getimtexture) (ImVec2 size=ImVec2(0, 0)) <br>_Get the ImGui texture of the image._  |
|  std::string\_view | [**GetPath**](#function-getpath) () const<br>_Get the file path of the image._  |
|  const cv::Mat | [**GetPureCvMat**](#function-getpurecvmat) () const<br>_Get the pure OpenCV matrix of the image (BGR format)._  |
|  int | [**GetWidth**](#function-getwidth) () const<br>_Get the width of the image._  |
|  bool | [**HasGlTextureObj**](#function-hasgltextureobj) () <br>_Check if the image has a valid OpenGL texture object._  |
|  bool | [**HasImTexture**](#function-hasimtexture) () <br>_Check if the image has a valid ImGui texture._  |
|   | [**Image**](#function-image-14) () <br>_Default constructor._  |
|   | [**Image**](#function-image-24) (cv::Mat cvImg) <br>_Constructor with OpenCV matrix._  |
|   | [**Image**](#function-image-34) ([**AIAC::Image**](classAIAC_1_1Image.md) & img) <br>_Copy constructor._  |
|   | [**Image**](#function-image-44) (const char \* path, int cvImReadFlag=cv::IMREAD\_UNCHANGED) <br>_Constructor with file path._  |
|  void | [**ReplaceCvMat**](#function-replacecvmat) (cv::Mat cvMat) <br>_Replace the OpenCV matrix of the image._  |
|  void | [**Resize**](#function-resize) (int newWidth, int newHeight) <br>_Resize the image._  |
|  void | [**SetImTextureSize**](#function-setimtexturesize) (ImVec2 size) <br>_Set the size of the ImGui texture._  |
|  void | [**UpdateData**](#function-updatedata) (cv::Mat cvImg) <br>_Update image data with a new OpenCV matrix._  |
|  void | [**UpdateGlTextureObj**](#function-updategltextureobj) () <br>_Update the OpenGL texture object of the image._  |
|  void | [**UpdateImTexture**](#function-updateimtexture) () <br>_Update the ImGui texture of the image._  |
|  [**Image**](classAIAC_1_1Image.md) & | [**operator=**](#function-operator) (cv::Mat cvImg) <br>_Assignment operator for OpenCV matrix._  |
|   | [**~Image**](#function-image) () <br>_Destructor._  |




























## Public Functions Documentation




### function DeleteGlTexture 

_Delete the OpenGL texture object._ 
```C++
inline void AIAC::Image::DeleteGlTexture () 
```




<hr>



### function GetCvMat 

_Get the OpenCV matrix of the image._ 
```C++
inline const cv::Mat AIAC::Image::GetCvMat () const
```





**Returns:**

OpenCV matrix of the image. 





        

<hr>



### function GetGlTextureObj 

_Get the OpenGL texture object of the image._ 
```C++
GLuint AIAC::Image::GetGlTextureObj () 
```





**Returns:**

OpenGL texture object of the image. 





        

<hr>



### function GetHeight 

_Get the height of the image._ 
```C++
inline int AIAC::Image::GetHeight () const
```





**Returns:**

Height of the image. 





        

<hr>



### function GetImTexture 

_Get the ImGui texture of the image._ 
```C++
ImTexture AIAC::Image::GetImTexture (
    ImVec2 size=ImVec2(0, 0)
) 
```





**Parameters:**


* `size` Size of the texture. 



**Returns:**

ImGui texture of the image. 





        

<hr>



### function GetPath 

_Get the file path of the image._ 
```C++
inline std::string_view AIAC::Image::GetPath () const
```





**Returns:**

File path of the image. 





        

<hr>



### function GetPureCvMat 

_Get the pure OpenCV matrix of the image (BGR format)._ 
```C++
inline const cv::Mat AIAC::Image::GetPureCvMat () const
```





**Returns:**

Pure OpenCV matrix of the image. 





        

<hr>



### function GetWidth 

_Get the width of the image._ 
```C++
inline int AIAC::Image::GetWidth () const
```





**Returns:**

Width of the image. 





        

<hr>



### function HasGlTextureObj 

_Check if the image has a valid OpenGL texture object._ 
```C++
inline bool AIAC::Image::HasGlTextureObj () 
```





**Returns:**

True if the image has a valid OpenGL texture object, false otherwise. 





        

<hr>



### function HasImTexture 

_Check if the image has a valid ImGui texture._ 
```C++
inline bool AIAC::Image::HasImTexture () 
```





**Returns:**

True if the image has a valid ImGui texture, false otherwise. 





        

<hr>



### function Image [1/4]

_Default constructor._ 
```C++
AIAC::Image::Image () 
```




<hr>



### function Image [2/4]

_Constructor with OpenCV matrix._ 
```C++
AIAC::Image::Image (
    cv::Mat cvImg
) 
```





**Parameters:**


* `cvImg` OpenCV matrix representing the image. 




        

<hr>



### function Image [3/4]

_Copy constructor._ 
```C++
AIAC::Image::Image (
    AIAC::Image & img
) 
```





**Parameters:**


* `img` Reference to another [**AIAC::Image**](classAIAC_1_1Image.md) object. 




        

<hr>



### function Image [4/4]

_Constructor with file path._ 
```C++
AIAC::Image::Image (
    const char * path,
    int cvImReadFlag=cv::IMREAD_UNCHANGED
) 
```





**Parameters:**


* `path` Path to the image file. 
* `cvImReadFlag` Flag for OpenCV image reading. 




        

<hr>



### function ReplaceCvMat 

_Replace the OpenCV matrix of the image._ 
```C++
inline void AIAC::Image::ReplaceCvMat (
    cv::Mat cvMat
) 
```





**Parameters:**


* `cvMat` New OpenCV matrix. 




        

<hr>



### function Resize 

_Resize the image._ 
```C++
inline void AIAC::Image::Resize (
    int newWidth,
    int newHeight
) 
```





**Parameters:**


* `newWidth` New width of the image. 
* `newHeight` New height of the image. 




        

<hr>



### function SetImTextureSize 

_Set the size of the ImGui texture._ 
```C++
inline void AIAC::Image::SetImTextureSize (
    ImVec2 size
) 
```





**Parameters:**


* `size` Size of the texture. 




        

<hr>



### function UpdateData 

_Update image data with a new OpenCV matrix._ 
```C++
void AIAC::Image::UpdateData (
    cv::Mat cvImg
) 
```





**Parameters:**


* `cvImg` OpenCV matrix representing the new image data. 




        

<hr>



### function UpdateGlTextureObj 

_Update the OpenGL texture object of the image._ 
```C++
void AIAC::Image::UpdateGlTextureObj () 
```




<hr>



### function UpdateImTexture 

_Update the ImGui texture of the image._ 
```C++
void AIAC::Image::UpdateImTexture () 
```




<hr>



### function operator= 

_Assignment operator for OpenCV matrix._ 
```C++
inline Image & AIAC::Image::operator= (
    cv::Mat cvImg
) 
```





**Parameters:**


* `cvImg` OpenCV matrix representing the new image data. 



**Returns:**

Reference to the updated image object. 





        

<hr>



### function ~Image 

_Destructor._ 
```C++
AIAC::Image::~Image () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Image.h`

