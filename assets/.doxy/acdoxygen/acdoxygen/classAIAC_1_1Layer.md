

# Class AIAC::Layer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Layer**](classAIAC_1_1Layer.md)










Inherited by the following classes: [AIAC::LayerCamera](classAIAC_1_1LayerCamera.md),  [AIAC::LayerCameraCalib](classAIAC_1_1LayerCameraCalib.md),  [AIAC::LayerFeedback](classAIAC_1_1LayerFeedback.md),  [AIAC::LayerLogRecorder](classAIAC_1_1LayerLogRecorder.md),  [AIAC::LayerModel](classAIAC_1_1LayerModel.md),  [AIAC::LayerSlam](classAIAC_1_1LayerSlam.md),  [AIAC::LayerToolhead](classAIAC_1_1LayerToolhead.md),  [AIAC::LayerUI](classAIAC_1_1LayerUI.md),  [AIAC::LayerUtils](classAIAC_1_1LayerUtils.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnAttach**](#function-onattach) () <br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnDetach**](#function-ondetach) () <br>_Is called when the layer is detached from the application (~app)._  |
| virtual void | [**OnFrameAwake**](#function-onframeawake) () <br>_Is calle before GLFW poll events, GL frame and Imgui Frame._  |
| virtual void | [**OnFrameEnd**](#function-onframeend) () <br>_Is called when frame ends._  |
| virtual void | [**OnFrameFall**](#function-onframefall) () <br>_Is called when the GLFW, GL and Imgui frame is updated and rendered._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () <br>_Is called when frame starts._  |
| virtual  | [**~Layer**](#function-layer) () = default<br> |




























## Public Functions Documentation




### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
inline virtual void AIAC::Layer::OnAttach () 
```




<hr>



### function OnDetach 

_Is called when the layer is detached from the application (~app)._ 
```C++
inline virtual void AIAC::Layer::OnDetach () 
```




<hr>



### function OnFrameAwake 

_Is calle before GLFW poll events, GL frame and Imgui Frame._ 
```C++
inline virtual void AIAC::Layer::OnFrameAwake () 
```




<hr>



### function OnFrameEnd 

_Is called when frame ends._ 
```C++
inline virtual void AIAC::Layer::OnFrameEnd () 
```




<hr>



### function OnFrameFall 

_Is called when the GLFW, GL and Imgui frame is updated and rendered._ 
```C++
inline virtual void AIAC::Layer::OnFrameFall () 
```




<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
inline virtual void AIAC::Layer::OnFrameStart () 
```




<hr>



### function ~Layer 

```C++
virtual AIAC::Layer::~Layer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Layer.h`

