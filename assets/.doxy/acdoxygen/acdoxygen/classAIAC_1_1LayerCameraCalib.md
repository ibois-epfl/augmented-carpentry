

# Class AIAC::LayerCameraCalib



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerCameraCalib**](classAIAC_1_1LayerCameraCalib.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**AutoCapture**](#variable-autocapture)   = `true`<br> |
|  int | [**Delay**](#variable-delay)   = `1500`<br> |
|  bool | [**JustCaptured**](#variable-justcaptured)   = `false`<br> |
|  int | [**NumOfFrame**](#variable-numofframe)   = `100`<br> |
|  std::string | [**SaveFilename**](#variable-savefilename)   = `"assets/tslam/calibration.yml"`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|  [**CameraCalibrator**](classAIAC_1_1CameraCalibrator.md) & | [**GetCameraCalibrator**](#function-getcameracalibrator) () <br> |
|  bool | [**IsCalibrating**](#function-iscalibrating) () const<br> |
|  bool | [**IsCapturing**](#function-iscapturing) () const<br> |
|   | [**LayerCameraCalib**](#function-layercameracalib) () = default<br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**SetSaveFilename**](#function-setsavefilename) (const std::string & filename) <br> |
|  void | [**StartCalibration**](#function-startcalibration) () <br> |
|  void | [**StartCapturing**](#function-startcapturing) () <br> |
|  void | [**StopCalibration**](#function-stopcalibration) () <br> |
|   | [**~LayerCameraCalib**](#function-layercameracalib) () override<br> |


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






















































## Public Attributes Documentation




### variable AutoCapture 

```C++
bool AIAC::LayerCameraCalib::AutoCapture;
```




<hr>



### variable Delay 

```C++
int AIAC::LayerCameraCalib::Delay;
```




<hr>



### variable JustCaptured 

```C++
bool AIAC::LayerCameraCalib::JustCaptured;
```




<hr>



### variable NumOfFrame 

```C++
int AIAC::LayerCameraCalib::NumOfFrame;
```




<hr>



### variable SaveFilename 

```C++
std::string AIAC::LayerCameraCalib::SaveFilename;
```




<hr>
## Public Functions Documentation




### function Clear 

```C++
void AIAC::LayerCameraCalib::Clear () 
```




<hr>



### function GetCameraCalibrator 

```C++
inline CameraCalibrator & AIAC::LayerCameraCalib::GetCameraCalibrator () 
```




<hr>



### function IsCalibrating 

```C++
inline bool AIAC::LayerCameraCalib::IsCalibrating () const
```




<hr>



### function IsCapturing 

```C++
inline bool AIAC::LayerCameraCalib::IsCapturing () const
```




<hr>



### function LayerCameraCalib 

```C++
AIAC::LayerCameraCalib::LayerCameraCalib () = default
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerCameraCalib::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerCameraCalib::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function SetSaveFilename 

```C++
inline void AIAC::LayerCameraCalib::SetSaveFilename (
    const std::string & filename
) 
```




<hr>



### function StartCalibration 

```C++
void AIAC::LayerCameraCalib::StartCalibration () 
```




<hr>



### function StartCapturing 

```C++
inline void AIAC::LayerCameraCalib::StartCapturing () 
```




<hr>



### function StopCalibration 

```C++
inline void AIAC::LayerCameraCalib::StopCalibration () 
```




<hr>



### function ~LayerCameraCalib 

```C++
AIAC::LayerCameraCalib::~LayerCameraCalib () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerCameraCalib.h`

