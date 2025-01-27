

# Class AIAC::LayerCamera



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerCamera**](classAIAC_1_1LayerCamera.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::string &gt; | [**AvailableDevices**](#variable-availabledevices)  <br> |
|  [**AIAC::Camera**](classAIAC_1_1Camera.md) | [**MainCamera**](#variable-maincamera)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**GetCurrentDevice**](#function-getcurrentdevice) () const<br> |
|  int | [**GetCurrentDeviceIndex**](#function-getcurrentdeviceindex) () const<br> |
|   | [**LayerCamera**](#function-layercamera) () = default<br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**SetCurrentDevice**](#function-setcurrentdevice) (std::string path) <br> |
|  void | [**SetCurrentDeviceIndex**](#function-setcurrentdeviceindex) (int index) <br> |
|  bool | [**UpdateAvailableDevices**](#function-updateavailabledevices) () <br>_Update the list of available devices._  |
| virtual  | [**~LayerCamera**](#function-layercamera) () = default<br> |


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




### variable AvailableDevices 

```C++
std::vector<std::string> AIAC::LayerCamera::AvailableDevices;
```




<hr>



### variable MainCamera 

```C++
AIAC::Camera AIAC::LayerCamera::MainCamera;
```




<hr>
## Public Functions Documentation




### function GetCurrentDevice 

```C++
inline std::string AIAC::LayerCamera::GetCurrentDevice () const
```




<hr>



### function GetCurrentDeviceIndex 

```C++
inline int AIAC::LayerCamera::GetCurrentDeviceIndex () const
```




<hr>



### function LayerCamera 

```C++
AIAC::LayerCamera::LayerCamera () = default
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerCamera::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerCamera::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function SetCurrentDevice 

```C++
void AIAC::LayerCamera::SetCurrentDevice (
    std::string path
) 
```




<hr>



### function SetCurrentDeviceIndex 

```C++
void AIAC::LayerCamera::SetCurrentDeviceIndex (
    int index
) 
```




<hr>



### function UpdateAvailableDevices 

_Update the list of available devices._ 
```C++
bool AIAC::LayerCamera::UpdateAvailableDevices () 
```





**Returns:**

true if the list contains &gt;= 1 device 




**Returns:**

false if the list has no devices 





        

<hr>



### function ~LayerCamera 

```C++
virtual AIAC::LayerCamera::~LayerCamera () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerCamera.h`

