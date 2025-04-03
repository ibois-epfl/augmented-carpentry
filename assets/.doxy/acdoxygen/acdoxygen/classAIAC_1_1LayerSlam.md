

# Class AIAC::LayerSlam



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerSlam**](classAIAC_1_1LayerSlam.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  tslam::TSlam | [**Slam**](#variable-slam)  <br> |
|  bool | [**ToEnhance**](#variable-toenhance)   = `false`<br> |
|  bool | [**ToProcess**](#variable-toprocess)   = `true`<br> |
|  bool | [**ToShowTag**](#variable-toshowtag)   = `false`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  const cv::Mat | [**GetCamPoseCv**](#function-getcamposecv) () <br> |
|  glm::mat4 | [**GetCamPoseGlm**](#function-getcamposeglm) () <br> |
|  void | [**GetCamPoseInObjCoord**](#function-getcamposeinobjcoord) (cv::Mat & rotationMatrix, cv::Mat & tvec) <br> |
|  void | [**GetCamPoseQuaternionAndTvec**](#function-getcamposequaternionandtvec) (cv::Vec4f & quaternion, cv::Vec3f & tvec) <br> |
|  glm::mat4 | [**GetInvCamPoseGlm**](#function-getinvcamposeglm) () <br> |
|  const int | [**GetNumLostFrame**](#function-getnumlostframe) () <br> |
|  [**AIAC::Image**](classAIAC_1_1Image.md) & | [**GetProcessedFrame**](#function-getprocessedframe) () <br> |
|  void | [**InitSlamMapGOs**](#function-initslammapgos) () <br> |
|  const bool | [**IsMapping**](#function-ismapping) () const<br> |
|  const bool | [**IsTracked**](#function-istracked) () <br> |
|   | [**LayerSlam**](#function-layerslam) () = default<br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**StartMapping**](#function-startmapping) () <br> |
|  void | [**StopMapping**](#function-stopmapping) () <br> |
|  void | [**UpdateMap**](#function-updatemap) (std::string path) <br> |
|   | [**~LayerSlam**](#function-layerslam) () = default<br> |


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




### variable Slam 

```C++
tslam::TSlam AIAC::LayerSlam::Slam;
```




<hr>



### variable ToEnhance 

```C++
bool AIAC::LayerSlam::ToEnhance;
```




<hr>



### variable ToProcess 

```C++
bool AIAC::LayerSlam::ToProcess;
```




<hr>



### variable ToShowTag 

```C++
bool AIAC::LayerSlam::ToShowTag;
```




<hr>
## Public Functions Documentation




### function GetCamPoseCv 

```C++
inline const cv::Mat AIAC::LayerSlam::GetCamPoseCv () 
```




<hr>



### function GetCamPoseGlm 

```C++
glm::mat4 AIAC::LayerSlam::GetCamPoseGlm () 
```




<hr>



### function GetCamPoseInObjCoord 

```C++
void AIAC::LayerSlam::GetCamPoseInObjCoord (
    cv::Mat & rotationMatrix,
    cv::Mat & tvec
) 
```




<hr>



### function GetCamPoseQuaternionAndTvec 

```C++
void AIAC::LayerSlam::GetCamPoseQuaternionAndTvec (
    cv::Vec4f & quaternion,
    cv::Vec3f & tvec
) 
```




<hr>



### function GetInvCamPoseGlm 

```C++
glm::mat4 AIAC::LayerSlam::GetInvCamPoseGlm () 
```




<hr>



### function GetNumLostFrame 

```C++
inline const int AIAC::LayerSlam::GetNumLostFrame () 
```




<hr>



### function GetProcessedFrame 

```C++
inline AIAC::Image & AIAC::LayerSlam::GetProcessedFrame () 
```




<hr>



### function InitSlamMapGOs 

```C++
void AIAC::LayerSlam::InitSlamMapGOs () 
```




<hr>



### function IsMapping 

```C++
inline const bool AIAC::LayerSlam::IsMapping () const
```




<hr>



### function IsTracked 

```C++
inline const bool AIAC::LayerSlam::IsTracked () 
```




<hr>



### function LayerSlam 

```C++
AIAC::LayerSlam::LayerSlam () = default
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerSlam::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerSlam::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function StartMapping 

```C++
void AIAC::LayerSlam::StartMapping () 
```




<hr>



### function StopMapping 

```C++
void AIAC::LayerSlam::StopMapping () 
```




<hr>



### function UpdateMap 

```C++
void AIAC::LayerSlam::UpdateMap (
    std::string path
) 
```




<hr>



### function ~LayerSlam 

```C++
AIAC::LayerSlam::~LayerSlam () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerSlam.h`

