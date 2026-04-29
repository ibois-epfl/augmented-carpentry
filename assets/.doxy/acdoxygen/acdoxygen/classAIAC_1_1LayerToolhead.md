

# Class AIAC::LayerToolhead



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerToolhead**](classAIAC_1_1LayerToolhead.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::shared\_ptr&lt; [**AIAC::ACInfoToolheadManager**](classAIAC_1_1ACInfoToolheadManager.md) &gt; | [**ACInfoToolheadManager**](#variable-acinfotoolheadmanager)  <br>_The manager holding the toolheads and setting the active one._  |
|  bool | [**IsSavePoseLog**](#variable-issaveposelog)   = `false`<br>_Save pose log._  |
|  bool | [**IsShowShaded**](#variable-isshowshaded)   = `false`<br>_Show the silouhette of the ttool._  |
|  bool | [**IsShowSilouhette**](#variable-isshowsilouhette)  <br>_Show the silouhette of the ttool._  |
|  bool | [**IsShowToolheadGOInfo**](#variable-isshowtoolheadgoinfo)  <br>_Show the GOInfo toolhead's elements._  |
|  std::shared\_ptr&lt; ttool::TTool &gt; | [**TTool**](#variable-ttool)  <br>_The ttool object._  |
|  int | [**ToolheadStateUI**](#variable-toolheadstateui)  <br>_The UI state of the toolhead (None, PoseInput, Tracking)_  |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DetectToolhead**](#function-detecttoolhead) () <br> |
|  std::string | [**GetClassifierLog**](#function-getclassifierlog) () const<br>_Get the current classifier log of the ttool._  |
|  std::vector&lt; std::string &gt; | [**GetClassifierToolheadList**](#function-getclassifiertoolheadlist) () const<br> |
|  cv::Matx44f | [**GetPose**](#function-getpose) () const<br>_Get the current pose of the ttool._  |
|  std::string | [**GetTrackingStatus**](#function-gettrackingstatus) () const<br>_Get the current tracking status of the ttool._  |
|  ttool::EventType | [**GetTtoolState**](#function-getttoolstate) () const<br>_Get the Ttool State object of the ttool event type._  |
|  glm::mat4x4 | [**GetWorldPose**](#function-getworldpose) () <br>_Get the current pose of the ttool._  |
|   | [**LayerToolhead**](#function-layertoolhead) () <br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**ReloadCameraFromFile**](#function-reloadcamerafromfile) () <br>_Destroy the ttool view and recreate a new ttool object._  |
|  void | [**ReloadCameraFromMatrix**](#function-reloadcamerafrommatrix) (cv::Mat cameraMatrix, cv::Size cameraSize) <br>_Destroy the ttool view and recreate a new ttool object with given camera params._  |
|  void | [**ResetPoseFromConfig**](#function-resetposefromconfig) () <br>_Set the pose from the value in the config initially read._  |
|  void | [**ResetToLastSavedPose**](#function-resettolastsavedpose) () <br>_Reset the pose of the ttool to the last saved pose._  |
|  void | [**SavePose**](#function-savepose) () <br>_Save the current pose of the ttool to the config file and to the ttool model manager (as a fallback pose for the ttool) It will reset_ [_**LayerToolhead**_](classAIAC_1_1LayerToolhead.md) _state to None (i.e. stop tracking and pose input)_ |
|  void | [**SetCurrentObject**](#function-setcurrentobject) (std::string name) <br>_Set the current active object for both the ttool and acit menager._  |
|  void | [**UpdateToolheadStateUI**](#function-updatetoolheadstateui) () <br>_Update the ttool state from the UI._  |


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




### variable ACInfoToolheadManager 

_The manager holding the toolheads and setting the active one._ 
```C++
std::shared_ptr<AIAC::ACInfoToolheadManager> AIAC::LayerToolhead::ACInfoToolheadManager;
```




<hr>



### variable IsSavePoseLog 

_Save pose log._ 
```C++
bool AIAC::LayerToolhead::IsSavePoseLog;
```




<hr>



### variable IsShowShaded 

_Show the silouhette of the ttool._ 
```C++
bool AIAC::LayerToolhead::IsShowShaded;
```




<hr>



### variable IsShowSilouhette 

_Show the silouhette of the ttool._ 
```C++
bool AIAC::LayerToolhead::IsShowSilouhette;
```




<hr>



### variable IsShowToolheadGOInfo 

_Show the GOInfo toolhead's elements._ 
```C++
bool AIAC::LayerToolhead::IsShowToolheadGOInfo;
```




<hr>



### variable TTool 

_The ttool object._ 
```C++
std::shared_ptr<ttool::TTool> AIAC::LayerToolhead::TTool;
```




<hr>



### variable ToolheadStateUI 

_The UI state of the toolhead (None, PoseInput, Tracking)_ 
```C++
int AIAC::LayerToolhead::ToolheadStateUI;
```




<hr>
## Public Functions Documentation




### function DetectToolhead 

```C++
void AIAC::LayerToolhead::DetectToolhead () 
```




<hr>



### function GetClassifierLog 

_Get the current classifier log of the ttool._ 
```C++
inline std::string AIAC::LayerToolhead::GetClassifierLog () const
```




<hr>



### function GetClassifierToolheadList 

```C++
inline std::vector< std::string > AIAC::LayerToolhead::GetClassifierToolheadList () const
```




<hr>



### function GetPose 

_Get the current pose of the ttool._ 
```C++
inline cv::Matx44f AIAC::LayerToolhead::GetPose () const
```




<hr>



### function GetTrackingStatus 

_Get the current tracking status of the ttool._ 
```C++
inline std::string AIAC::LayerToolhead::GetTrackingStatus () const
```




<hr>



### function GetTtoolState 

_Get the Ttool State object of the ttool event type._ 
```C++
inline ttool::EventType AIAC::LayerToolhead::GetTtoolState () const
```



&lt; Getters and setters 


        

<hr>



### function GetWorldPose 

_Get the current pose of the ttool._ 
```C++
glm::mat4x4 AIAC::LayerToolhead::GetWorldPose () 
```



Get the world pose of the toolhead.




**Returns:**

The transformation matrix that transforms from the toolhead frame to the world frame 





        

<hr>



### function LayerToolhead 

```C++
inline AIAC::LayerToolhead::LayerToolhead () 
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerToolhead::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerToolhead::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function ReloadCameraFromFile 

_Destroy the ttool view and recreate a new ttool object._ 
```C++
void AIAC::LayerToolhead::ReloadCameraFromFile () 
```




<hr>



### function ReloadCameraFromMatrix 

_Destroy the ttool view and recreate a new ttool object with given camera params._ 
```C++
void AIAC::LayerToolhead::ReloadCameraFromMatrix (
    cv::Mat cameraMatrix,
    cv::Size cameraSize
) 
```




<hr>



### function ResetPoseFromConfig 

_Set the pose from the value in the config initially read._ 
```C++
void AIAC::LayerToolhead::ResetPoseFromConfig () 
```




<hr>



### function ResetToLastSavedPose 

_Reset the pose of the ttool to the last saved pose._ 
```C++
void AIAC::LayerToolhead::ResetToLastSavedPose () 
```




<hr>



### function SavePose 

_Save the current pose of the ttool to the config file and to the ttool model manager (as a fallback pose for the ttool) It will reset_ [_**LayerToolhead**_](classAIAC_1_1LayerToolhead.md) _state to None (i.e. stop tracking and pose input)_
```C++
void AIAC::LayerToolhead::SavePose () 
```




<hr>



### function SetCurrentObject 

_Set the current active object for both the ttool and acit menager._ 
```C++
void AIAC::LayerToolhead::SetCurrentObject (
    std::string name
) 
```




<hr>



### function UpdateToolheadStateUI 

_Update the ttool state from the UI._ 
```C++
void AIAC::LayerToolhead::UpdateToolheadStateUI () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerToolhead.h`

