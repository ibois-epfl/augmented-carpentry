

# Class AIAC::LayerLogRecorder



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerLogRecorder**](classAIAC_1_1LayerLogRecorder.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**IsPaused**](#function-ispaused) () const<br>_the recoder is paused_  |
|  bool | [**IsRecording**](#function-isrecording) () const<br>_the recorder is on_  |
|   | [**LayerLogRecorder**](#function-layerlogrecorder) () = default<br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**PauseRecording**](#function-pauserecording) () <br>_Pause recording._  |
|  void | [**ResumeRecording**](#function-resumerecording) () <br>_Pause recording._  |
|  void | [**StartRecording**](#function-startrecording) (std::string logRootFolderPath="") <br>_Start recording the log to a file._  |
|  void | [**StopRecording**](#function-stoprecording) () <br>_Stop recording the log to a file._  |
| virtual  | [**~LayerLogRecorder**](#function-layerlogrecorder) () = default<br> |


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






















































## Public Functions Documentation




### function IsPaused 

_the recoder is paused_ 
```C++
inline bool AIAC::LayerLogRecorder::IsPaused () const
```




<hr>



### function IsRecording 

_the recorder is on_ 
```C++
inline bool AIAC::LayerLogRecorder::IsRecording () const
```





**Returns:**

true if it's recording, false otherwise 





        

<hr>



### function LayerLogRecorder 

```C++
AIAC::LayerLogRecorder::LayerLogRecorder () = default
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerLogRecorder::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerLogRecorder::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function PauseRecording 

_Pause recording._ 
```C++
void AIAC::LayerLogRecorder::PauseRecording () 
```




<hr>



### function ResumeRecording 

_Pause recording._ 
```C++
void AIAC::LayerLogRecorder::ResumeRecording () 
```




<hr>



### function StartRecording 

_Start recording the log to a file._ 
```C++
void AIAC::LayerLogRecorder::StartRecording (
    std::string logRootFolderPath=""
) 
```





**Parameters:**


* `logRootFolderPath` The filename of the log file 




        

<hr>



### function StopRecording 

_Stop recording the log to a file._ 
```C++
void AIAC::LayerLogRecorder::StopRecording () 
```




<hr>



### function ~LayerLogRecorder 

```C++
virtual AIAC::LayerLogRecorder::~LayerLogRecorder () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerLogRecorder.h`

