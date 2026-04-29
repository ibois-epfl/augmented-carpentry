

# Class AIAC::Utils::VideoRecorder



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Utils**](namespaceAIAC_1_1Utils.md) **>** [**VideoRecorder**](classAIAC_1_1Utils_1_1VideoRecorder.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CaptureFrames**](#function-captureframes) () <br>_Capture frames from the window._  |
|  void | [**DeleteFrameFolder**](#function-deleteframefolder) () <br>_Delete the /frames folder._  |
|  void | [**InitializeDirectories**](#function-initializedirectories) () <br>_Create folders for captured frames and videos._  |
|  void | [**MakeVideoFromFrames**](#function-makevideofromframes) () <br>_Create video from the frames using ffmpeg._  |
|  void | [**SaveFrames**](#function-saveframes) (int height, int width, std::vector&lt; unsigned char &gt; pixels) <br>_Save frames to the frame folder._  |
|  void | [**UpdatePaths**](#function-updatepaths) () <br>_Updates the paths used for video and frame storage._  |
|   | [**VideoRecorder**](#function-videorecorder) (const std::string & basePath) <br> |
|   | [**~VideoRecorder**](#function-videorecorder) () <br> |




























## Public Functions Documentation




### function CaptureFrames 

_Capture frames from the window._ 
```C++
void AIAC::Utils::VideoRecorder::CaptureFrames () 
```




<hr>



### function DeleteFrameFolder 

_Delete the /frames folder._ 
```C++
void AIAC::Utils::VideoRecorder::DeleteFrameFolder () 
```




<hr>



### function InitializeDirectories 

_Create folders for captured frames and videos._ 
```C++
void AIAC::Utils::VideoRecorder::InitializeDirectories () 
```




<hr>



### function MakeVideoFromFrames 

_Create video from the frames using ffmpeg._ 
```C++
void AIAC::Utils::VideoRecorder::MakeVideoFromFrames () 
```




<hr>



### function SaveFrames 

_Save frames to the frame folder._ 
```C++
void AIAC::Utils::VideoRecorder::SaveFrames (
    int height,
    int width,
    std::vector< unsigned char > pixels
) 
```





**Parameters:**


* `height` Height of the window 
* `width` Width of the window 
* `pixels` Vector to hold the data 




        

<hr>



### function UpdatePaths 

_Updates the paths used for video and frame storage._ 
```C++
void AIAC::Utils::VideoRecorder::UpdatePaths () 
```




<hr>



### function VideoRecorder 

```C++
explicit AIAC::Utils::VideoRecorder::VideoRecorder (
    const std::string & basePath
) 
```




<hr>



### function ~VideoRecorder 

```C++
AIAC::Utils::VideoRecorder::~VideoRecorder () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/VideoRecorder.h`

