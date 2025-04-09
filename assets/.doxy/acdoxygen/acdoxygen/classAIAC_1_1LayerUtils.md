

# Class AIAC::LayerUtils



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerUtils**](classAIAC_1_1LayerUtils.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ExportHoleToolheadAxis**](#function-exportholetoolheadaxis) () <br>_Export and write the hole and toolhead coordinates._  |
|  std::string | [**GetSaveFolderPath**](#function-getsavefolderpath) () <br>_Get the current save folder path for the utils._  |
|  bool | [**IsProcessing**](#function-isprocessing) () <br>_Check if the video is being processed._  |
|   | [**LayerUtils**](#function-layerutils) () <br> |
| virtual void | [**OnFrameEnd**](#function-onframeend) () override<br>_Is called when frame ends._  |
|  void | [**SetSaveFolderPath**](#function-setsavefolderpath) (const std::string & path) <br>_Set the save folder path for the utils from UI._  |
|  void | [**SetWindowScreenshot**](#function-setwindowscreenshot) (bool value) <br>_Set the flag to check if the screenshot is of the window._  |
|  void | [**StartRecording**](#function-startrecording) () <br>_Start recording the video of a window._  |
|  void | [**StopRecording**](#function-stoprecording) () <br>_Stop recording the video of a window._  |
|  void | [**TakeBufferScreenshot**](#function-takebufferscreenshot) () <br>_Take a screenshot of the colored buffer._  |
|  void | [**TakeWindowScreenshot**](#function-takewindowscreenshot) () <br>_Take a screenshot of the current window._  |


## Public Functions inherited from AIAC::Layer

See [AIAC::Layer](classAIAC_1_1Layer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnAttach**](classAIAC_1_1Layer.md#function-onattach) () <br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnDetach**](classAIAC_1_1Layer.md#function-ondetach) () <br>_Is called when the layer is detached from the application (~app)._  |
| virtual void | [**OnFrameAwake**](classAIAC_1_1Layer.md#function-onframeawake) () <br>_Is calle before GLFW poll events, GL frame and Imgui Frame._  |
| virtual void | [**OnFrameEnd**](classAIAC_1_1Layer.md#function-onframeend) () <br>_Is called when frame ends._  |
| virtual void | [**OnFrameFall**](classAIAC_1_1Layer.md#function-onframefall) () <br>_Is called when the GLFW, GL and Imgui frame is updated and rendered._  |
| virtual void | [**OnFrameStart**](classAIAC_1_1Layer.md#function-onframestart) () <br>_Is called when frame starts._  |
| virtual  | [**~Layer**](classAIAC_1_1Layer.md#function-layer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CreateFolder**](#function-createfolder) (const std::string & path) <br>_Create a folder if it does not exist._  |




















































## Public Functions Documentation




### function ExportHoleToolheadAxis 

_Export and write the hole and toolhead coordinates._ 
```C++
void AIAC::LayerUtils::ExportHoleToolheadAxis () 
```



&lt; hole and toolhead exporter 


        

<hr>



### function GetSaveFolderPath 

_Get the current save folder path for the utils._ 
```C++
inline std::string AIAC::LayerUtils::GetSaveFolderPath () 
```





**Returns:**

std::string Path to the current utils folder 





        

<hr>



### function IsProcessing 

_Check if the video is being processed._ 
```C++
inline bool AIAC::LayerUtils::IsProcessing () 
```




<hr>



### function LayerUtils 

```C++
AIAC::LayerUtils::LayerUtils () 
```




<hr>



### function OnFrameEnd 

_Is called when frame ends._ 
```C++
virtual void AIAC::LayerUtils::OnFrameEnd () override
```



Implements [*AIAC::Layer::OnFrameEnd*](classAIAC_1_1Layer.md#function-onframeend)


<hr>



### function SetSaveFolderPath 

_Set the save folder path for the utils from UI._ 
```C++
void AIAC::LayerUtils::SetSaveFolderPath (
    const std::string & path
) 
```





**Parameters:**


* `path` Path to the folder that comes from UI 




        

<hr>



### function SetWindowScreenshot 

_Set the flag to check if the screenshot is of the window._ 
```C++
inline void AIAC::LayerUtils::SetWindowScreenshot (
    bool value
) 
```





**Parameters:**


* `value` True if the screenshot is of the window 




        

<hr>



### function StartRecording 

_Start recording the video of a window._ 
```C++
void AIAC::LayerUtils::StartRecording () 
```



&lt; video recorder 


        

<hr>



### function StopRecording 

_Stop recording the video of a window._ 
```C++
void AIAC::LayerUtils::StopRecording () 
```




<hr>



### function TakeBufferScreenshot 

_Take a screenshot of the colored buffer._ 
```C++
void AIAC::LayerUtils::TakeBufferScreenshot () 
```




<hr>



### function TakeWindowScreenshot 

_Take a screenshot of the current window._ 
```C++
void AIAC::LayerUtils::TakeWindowScreenshot () 
```



&lt; screenshot 


        

<hr>
## Public Static Functions Documentation




### function CreateFolder 

_Create a folder if it does not exist._ 
```C++
static bool AIAC::LayerUtils::CreateFolder (
    const std::string & path
) 
```





**Parameters:**


* `path` Path to the folder 



**Returns:**

true if the folder is created 




**Returns:**

false if the folder already exists 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerUtils.h`

