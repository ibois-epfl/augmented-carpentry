

# Class AIAC::LayerFeedback



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerFeedback**](classAIAC_1_1LayerFeedback.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**ToShowCutPlane**](#variable-toshowcutplane)   = `false`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ActivateCurrentFeedbackVisibility**](#function-activatecurrentfeedbackvisibility) () <br> |
|  void | [**DeactivateCurrentFeedbackVisibility**](#function-deactivatecurrentfeedbackvisibility) () <br> |
|  void | [**EnableCutPlane**](#function-enablecutplane) (bool enable) <br> |
|  [**FabFeedback**](classAIAC_1_1FabFeedback.md) \* | [**GetCurrentFabFeedback**](#function-getcurrentfabfeedback) () <br> |
|   | [**LayerFeedback**](#function-layerfeedback) () <br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
| virtual  | [**~LayerFeedback**](#function-layerfeedback) () = default<br> |


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




### variable ToShowCutPlane 

```C++
bool AIAC::LayerFeedback::ToShowCutPlane;
```




<hr>
## Public Functions Documentation




### function ActivateCurrentFeedbackVisibility 

```C++
inline void AIAC::LayerFeedback::ActivateCurrentFeedbackVisibility () 
```




<hr>



### function DeactivateCurrentFeedbackVisibility 

```C++
inline void AIAC::LayerFeedback::DeactivateCurrentFeedbackVisibility () 
```




<hr>



### function EnableCutPlane 

```C++
inline void AIAC::LayerFeedback::EnableCutPlane (
    bool enable
) 
```




<hr>



### function GetCurrentFabFeedback 

```C++
inline FabFeedback * AIAC::LayerFeedback::GetCurrentFabFeedback () 
```




<hr>



### function LayerFeedback 

```C++
AIAC::LayerFeedback::LayerFeedback () 
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerFeedback::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerFeedback::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function ~LayerFeedback 

```C++
virtual AIAC::LayerFeedback::~LayerFeedback () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerFeedback.h`

