

# Class AIAC::Utils::Screenshot



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Utils**](namespaceAIAC_1_1Utils.md) **>** [**Screenshot**](classAIAC_1_1Utils_1_1Screenshot.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CaptureBuffer**](#function-capturebuffer) () <br>_Capture current buffer (color)_  |
|  void | [**CaptureWindow**](#function-capturewindow) () <br>_Capture pixels of the current window._  |
|  void | [**GenerateImageName**](#function-generateimagename) (bool isWindow) <br>_Generate the name of the image._  |
|  void | [**SaveScreenshot**](#function-savescreenshot) (cv::Mat image) <br>_Save the screenshot._  |
|   | [**Screenshot**](#function-screenshot) (const std::string & basePath) <br> |




























## Public Functions Documentation




### function CaptureBuffer 

_Capture current buffer (color)_ 
```C++
void AIAC::Utils::Screenshot::CaptureBuffer () 
```




<hr>



### function CaptureWindow 

_Capture pixels of the current window._ 
```C++
void AIAC::Utils::Screenshot::CaptureWindow () 
```




<hr>



### function GenerateImageName 

_Generate the name of the image._ 
```C++
void AIAC::Utils::Screenshot::GenerateImageName (
    bool isWindow
) 
```





**Parameters:**


* `isWindow` Flag to check if the image is a window screenshot if not it is a buffer screenshot 




        

<hr>



### function SaveScreenshot 

_Save the screenshot._ 
```C++
void AIAC::Utils::Screenshot::SaveScreenshot (
    cv::Mat image
) 
```





**Parameters:**


* `image` [**Image**](classAIAC_1_1Image.md) to save 




        

<hr>



### function Screenshot 

```C++
explicit AIAC::Utils::Screenshot::Screenshot (
    const std::string & basePath
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/Screenshot.h`

