

# Class AIAC::LayerUI



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerUI**](classAIAC_1_1LayerUI.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**PaneUI**](classAIAC_1_1PaneUI.md) \* | [**GetOpenedPaneUI**](#function-getopenedpaneui) () <br> |
|   | [**LayerUI**](#function-layerui) () = default<br> |
|  void | [**LoadReconstructParams**](#function-loadreconstructparams) () <br> |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
|  void | [**OnCollapsingPaneUIToolhead**](#function-oncollapsingpaneuitoolhead) () <br> |
| virtual void | [**OnDetach**](#function-ondetach) () override<br>_Is called when the layer is detached from the application (~app)._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**OnUIRender**](#function-onuirender) () <br> |
|  void | [**OpenFileSelectDialog**](#function-openfileselectdialog) (const char \* title, const char \* fileExt, char \* path, std::function&lt; void()&gt; callback=[]{}) <br> |
|  void | [**SetOpenedPaneUI**](#function-setopenedpaneui) ([**PaneUI**](classAIAC_1_1PaneUI.md) \* paneUI) <br> |
|  void | [**SetPaneUIACIM**](#function-setpaneuiacim) () <br> |
|  void | [**SetPaneUICamera**](#function-setpaneuicamera) () <br> |
|  void | [**SetPaneUISlam**](#function-setpaneuislam) () <br> |
|  void | [**SetPaneUIToolhead**](#function-setpaneuitoolhead) () <br> |
|  void | [**SetPaneUIUtils**](#function-setpaneuiutils) () <br> |
|  void | [**ShowCamCalibPopup**](#function-showcamcalibpopup) () <br> |
|  void | [**ShowCombineMapPopup**](#function-showcombinemappopup) () <br> |
|  void | [**ShowFileSelectDialog**](#function-showfileselectdialog) () <br> |
|  void | [**ShowLogRecorderUI**](#function-showlogrecorderui) () <br> |
|  void | [**ShowMainUI**](#function-showmainui) () <br> |
|  void | [**ShowMapFileDialog**](#function-showmapfiledialog) (char \* path) <br> |
|  void | [**ShowMappingPopup**](#function-showmappingpopup) () <br> |
|  void | [**ShowMenuBar**](#function-showmenubar) () <br> |
|  void | [**ShowReconExportFilePathDialog**](#function-showreconexportfilepathdialog) () <br> |
|  void | [**ShowReconstruct3DPopup**](#function-showreconstruct3dpopup) () <br> |
|  void | [**ShowSaveCamCalibFileDialog**](#function-showsavecamcalibfiledialog) () <br> |
|  void | [**ShowSaveMapFileDialog**](#function-showsavemapfiledialog) () <br> |
|  void | [**ShowSaveVideoRecorderFileDialog**](#function-showsavevideorecorderfiledialog) () <br> |
|  void | [**ShowSceneViewport**](#function-showsceneviewport) () <br> |
|  void | [**StackPane**](#function-stackpane) ([**PaneUI**](classAIAC_1_1PaneUI.md) pane) <br> |
| virtual  | [**~LayerUI**](#function-layerui) () = default<br> |


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




### function GetOpenedPaneUI 

```C++
inline PaneUI * AIAC::LayerUI::GetOpenedPaneUI () 
```




<hr>



### function LayerUI 

```C++
AIAC::LayerUI::LayerUI () = default
```




<hr>



### function LoadReconstructParams 

```C++
void AIAC::LayerUI::LoadReconstructParams () 
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerUI::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnCollapsingPaneUIToolhead 

```C++
void AIAC::LayerUI::OnCollapsingPaneUIToolhead () 
```




<hr>



### function OnDetach 

_Is called when the layer is detached from the application (~app)._ 
```C++
virtual void AIAC::LayerUI::OnDetach () override
```



Implements [*AIAC::Layer::OnDetach*](classAIAC_1_1Layer.md#function-ondetach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerUI::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function OnUIRender 

```C++
void AIAC::LayerUI::OnUIRender () 
```




<hr>



### function OpenFileSelectDialog 

```C++
void AIAC::LayerUI::OpenFileSelectDialog (
    const char * title,
    const char * fileExt,
    char * path,
    std::function< void()> callback=[]{}
) 
```




<hr>



### function SetOpenedPaneUI 

```C++
inline void AIAC::LayerUI::SetOpenedPaneUI (
    PaneUI * paneUI
) 
```




<hr>



### function SetPaneUIACIM 

```C++
void AIAC::LayerUI::SetPaneUIACIM () 
```




<hr>



### function SetPaneUICamera 

```C++
void AIAC::LayerUI::SetPaneUICamera () 
```




<hr>



### function SetPaneUISlam 

```C++
void AIAC::LayerUI::SetPaneUISlam () 
```




<hr>



### function SetPaneUIToolhead 

```C++
void AIAC::LayerUI::SetPaneUIToolhead () 
```




<hr>



### function SetPaneUIUtils 

```C++
void AIAC::LayerUI::SetPaneUIUtils () 
```




<hr>



### function ShowCamCalibPopup 

```C++
void AIAC::LayerUI::ShowCamCalibPopup () 
```




<hr>



### function ShowCombineMapPopup 

```C++
void AIAC::LayerUI::ShowCombineMapPopup () 
```




<hr>



### function ShowFileSelectDialog 

```C++
void AIAC::LayerUI::ShowFileSelectDialog () 
```




<hr>



### function ShowLogRecorderUI 

```C++
void AIAC::LayerUI::ShowLogRecorderUI () 
```




<hr>



### function ShowMainUI 

```C++
void AIAC::LayerUI::ShowMainUI () 
```




<hr>



### function ShowMapFileDialog 

```C++
void AIAC::LayerUI::ShowMapFileDialog (
    char * path
) 
```




<hr>



### function ShowMappingPopup 

```C++
void AIAC::LayerUI::ShowMappingPopup () 
```




<hr>



### function ShowMenuBar 

```C++
void AIAC::LayerUI::ShowMenuBar () 
```




<hr>



### function ShowReconExportFilePathDialog 

```C++
void AIAC::LayerUI::ShowReconExportFilePathDialog () 
```




<hr>



### function ShowReconstruct3DPopup 

```C++
void AIAC::LayerUI::ShowReconstruct3DPopup () 
```




<hr>



### function ShowSaveCamCalibFileDialog 

```C++
void AIAC::LayerUI::ShowSaveCamCalibFileDialog () 
```




<hr>



### function ShowSaveMapFileDialog 

```C++
void AIAC::LayerUI::ShowSaveMapFileDialog () 
```




<hr>



### function ShowSaveVideoRecorderFileDialog 

```C++
void AIAC::LayerUI::ShowSaveVideoRecorderFileDialog () 
```




<hr>



### function ShowSceneViewport 

```C++
void AIAC::LayerUI::ShowSceneViewport () 
```




<hr>



### function StackPane 

```C++
inline void AIAC::LayerUI::StackPane (
    PaneUI pane
) 
```




<hr>



### function ~LayerUI 

```C++
virtual AIAC::LayerUI::~LayerUI () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerUI.h`

