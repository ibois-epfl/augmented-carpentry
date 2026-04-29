

# Class AIAC::LayerModel



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**LayerModel**](classAIAC_1_1LayerModel.md)








Inherits the following classes: [AIAC::Layer](classAIAC_1_1Layer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddAlignOffset**](#function-addalignoffset) (float diff) <br>_Change the align offset. The value is in TSLAM unit._  |
|  void | [**AlignModels**](#function-alignmodels) () <br>_transform the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _to the_[_**ScannedModel**_](classAIAC_1_1ScannedModel.md) __ |
|  void | [**ChangeAlignRotation**](#function-changealignrotation) (int diff) <br>_Change the align rotation. The value is in degree._  |
|  void | [**FlipAlign**](#function-flipalign) () <br>_Change the align flip._  |
|  void | [**ForceAlignToEnd**](#function-forcealigntoend) (bool leftOrRight) <br>_Set the offset make it align to one end._  |
|  [**ACInfoModel**](classAIAC_1_1ACInfoModel.md) & | [**GetACInfoModel**](#function-getacinfomodel) () <br>_Return the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._ |
|  const std::string | [**GetACInfoModelName**](#function-getacinfomodelname) () const<br>_Return the file name of the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._ |
|  const std::string & | [**GetACInfoModelPath**](#function-getacinfomodelpath) () const<br>_Return the filepath to the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._ |
|  bool | [**GetAlignFlip**](#function-getalignflip) () const<br>_Get the flip status of the model._  |
|  float | [**GetAlignOffset**](#function-getalignoffset) () <br>_Get the Align Offset of the model._  |
|  int | [**GetAlignRotation**](#function-getalignrotation) () const<br>_Get the rotation position of the model._  |
|  [**ScannedModel**](classAIAC_1_1ScannedModel.md) & | [**GetScannedModel**](#function-getscannedmodel) () <br>_Get the Scanned Model object._  |
|  const std::string & | [**GetScannedModelPath**](#function-getscannedmodelpath) () const<br>_Return the filepath to the loaded_ [_**ScannedModel**_](classAIAC_1_1ScannedModel.md) _._ |
|  glm::mat4x4 | [**GetTransformMat**](#function-gettransformmat) () const<br>_Get the transform matrix of the model._  |
|   | [**LayerModel**](#function-layermodel) () <br> |
|  void | [**LoadACInfoModel**](#function-loadacinfomodel) (const std::string & path) <br>_Load a .acim model from a file._  |
|  void | [**LoadScannedModel**](#function-loadscannedmodel) (const std::string & path) <br>_Load a .ply model from a file._  |
| virtual void | [**OnAttach**](#function-onattach) () override<br>_Is called when the layer is attached to the application._  |
| virtual void | [**OnFrameStart**](#function-onframestart) () override<br>_Is called when frame starts._  |
|  void | [**ReloadACInfoModel**](#function-reloadacinfomodel) () <br>_Reload the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _from the current path from config._ |
|  void | [**ResetAlignFlip**](#function-resetalignflip) () <br>_Reset the align flip to false (No flip)._  |
|  void | [**ResetAlignOffset**](#function-resetalignoffset) () <br>_Reset the align offset to 0 (Center)._  |
|  void | [**ResetAlignRotation**](#function-resetalignrotation) () <br>_Reset the align rotation to 0 (No rotation)._  |
| virtual  | [**~LayerModel**](#function-layermodel) () = default<br> |


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




### function AddAlignOffset 

_Change the align offset. The value is in TSLAM unit._ 
```C++
inline void AIAC::LayerModel::AddAlignOffset (
    float diff
) 
```




<hr>



### function AlignModels 

_transform the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _to the_[_**ScannedModel**_](classAIAC_1_1ScannedModel.md) __
```C++
void AIAC::LayerModel::AlignModels () 
```




<hr>



### function ChangeAlignRotation 

_Change the align rotation. The value is in degree._ 
```C++
inline void AIAC::LayerModel::ChangeAlignRotation (
    int diff
) 
```





**Parameters:**


* `diff` +1 or -1 to rotate 90 degree (counter-)clock wise. 




        

<hr>



### function FlipAlign 

_Change the align flip._ 
```C++
inline void AIAC::LayerModel::FlipAlign () 
```




<hr>



### function ForceAlignToEnd 

_Set the offset make it align to one end._ 
```C++
inline void AIAC::LayerModel::ForceAlignToEnd (
    bool leftOrRight
) 
```




<hr>



### function GetACInfoModel 

_Return the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._
```C++
inline ACInfoModel & AIAC::LayerModel::GetACInfoModel () 
```




<hr>



### function GetACInfoModelName 

_Return the file name of the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._
```C++
inline const std::string AIAC::LayerModel::GetACInfoModelName () const
```




<hr>



### function GetACInfoModelPath 

_Return the filepath to the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._
```C++
inline const std::string & AIAC::LayerModel::GetACInfoModelPath () const
```




<hr>



### function GetAlignFlip 

_Get the flip status of the model._ 
```C++
inline bool AIAC::LayerModel::GetAlignFlip () const
```




<hr>



### function GetAlignOffset 

_Get the Align Offset of the model._ 
```C++
inline float AIAC::LayerModel::GetAlignOffset () 
```




<hr>



### function GetAlignRotation 

_Get the rotation position of the model._ 
```C++
inline int AIAC::LayerModel::GetAlignRotation () const
```




<hr>



### function GetScannedModel 

_Get the Scanned Model object._ 
```C++
inline ScannedModel & AIAC::LayerModel::GetScannedModel () 
```




<hr>



### function GetScannedModelPath 

_Return the filepath to the loaded_ [_**ScannedModel**_](classAIAC_1_1ScannedModel.md) _._
```C++
inline const std::string & AIAC::LayerModel::GetScannedModelPath () const
```




<hr>



### function GetTransformMat 

_Get the transform matrix of the model._ 
```C++
inline glm::mat4x4 AIAC::LayerModel::GetTransformMat () const
```




<hr>



### function LayerModel 

```C++
AIAC::LayerModel::LayerModel () 
```




<hr>



### function LoadACInfoModel 

_Load a .acim model from a file._ 
```C++
void AIAC::LayerModel::LoadACInfoModel (
    const std::string & path
) 
```




<hr>



### function LoadScannedModel 

_Load a .ply model from a file._ 
```C++
void AIAC::LayerModel::LoadScannedModel (
    const std::string & path
) 
```




<hr>



### function OnAttach 

_Is called when the layer is attached to the application._ 
```C++
virtual void AIAC::LayerModel::OnAttach () override
```



Implements [*AIAC::Layer::OnAttach*](classAIAC_1_1Layer.md#function-onattach)


<hr>



### function OnFrameStart 

_Is called when frame starts._ 
```C++
virtual void AIAC::LayerModel::OnFrameStart () override
```



Implements [*AIAC::Layer::OnFrameStart*](classAIAC_1_1Layer.md#function-onframestart)


<hr>



### function ReloadACInfoModel 

_Reload the_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _from the current path from config._
```C++
void AIAC::LayerModel::ReloadACInfoModel () 
```




<hr>



### function ResetAlignFlip 

_Reset the align flip to false (No flip)._ 
```C++
inline void AIAC::LayerModel::ResetAlignFlip () 
```




<hr>



### function ResetAlignOffset 

_Reset the align offset to 0 (Center)._ 
```C++
inline void AIAC::LayerModel::ResetAlignOffset () 
```




<hr>



### function ResetAlignRotation 

_Reset the align rotation to 0 (No rotation)._ 
```C++
inline void AIAC::LayerModel::ResetAlignRotation () 
```




<hr>



### function ~LayerModel 

```C++
virtual AIAC::LayerModel::~LayerModel () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerModel.h`

