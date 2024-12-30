

# Class AIAC::Renderer



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Renderer**](classAIAC_1_1Renderer.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**CameraFrameType**](#enum-cameraframetype)  <br> |
| enum  | [**StandardView**](#enum-standardview)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  GLuint | [**GetCamCalibView**](#function-getcamcalibview) () const<br> |
|  GLuint | [**GetGlobalView**](#function-getglobalview) () const<br> |
|  GLuint | [**GetMappingView**](#function-getmappingview) () const<br> |
|  void | [**Init**](#function-init) () <br> |
|  void | [**InitProjMatrix**](#function-initprojmatrix) () <br> |
|  void | [**OnRender**](#function-onrender) () <br> |
|   | [**Renderer**](#function-renderer) () = default<br> |
|  void | [**SetCamCalibViewSize**](#function-setcamcalibviewsize) (float w, float h) <br> |
|  void | [**SetGlobalViewSize**](#function-setglobalviewsize) (float w, float h) <br> |
|  void | [**SetGlobalViewToActivatedComponent**](#function-setglobalviewtoactivatedcomponent) (StandardView standardView) <br> |
|  void | [**SetMappingViewSize**](#function-setmappingviewsize) (float w, float h) <br> |
|  void | [**UpdateGlobalViewCameraRotation**](#function-updateglobalviewcamerarotation) (double diffX, double diffY) <br> |
|  void | [**UpdateGlobalViewCameraScale**](#function-updateglobalviewcamerascale) (double diff) <br> |
|  void | [**UpdateGlobalViewCameraTranslation**](#function-updateglobalviewcameratranslation) (double diffX, double diffY) <br> |
| virtual  | [**~Renderer**](#function-renderer) () = default<br> |




























## Public Types Documentation




### enum CameraFrameType 

```C++
enum AIAC::Renderer::CameraFrameType {
    RAW,
    UNDISTORTED,
    SLAM_PROCESSED
};
```




<hr>



### enum StandardView 

```C++
enum AIAC::Renderer::StandardView {
    TOP,
    BOTTOM,
    NW,
    NE,
    SW,
    SE
};
```




<hr>
## Public Functions Documentation




### function GetCamCalibView 

```C++
inline GLuint AIAC::Renderer::GetCamCalibView () const
```




<hr>



### function GetGlobalView 

```C++
inline GLuint AIAC::Renderer::GetGlobalView () const
```




<hr>



### function GetMappingView 

```C++
inline GLuint AIAC::Renderer::GetMappingView () const
```




<hr>



### function Init 

```C++
void AIAC::Renderer::Init () 
```




<hr>



### function InitProjMatrix 

```C++
void AIAC::Renderer::InitProjMatrix () 
```




<hr>



### function OnRender 

```C++
void AIAC::Renderer::OnRender () 
```




<hr>



### function Renderer 

```C++
AIAC::Renderer::Renderer () = default
```




<hr>



### function SetCamCalibViewSize 

```C++
void AIAC::Renderer::SetCamCalibViewSize (
    float w,
    float h
) 
```




<hr>



### function SetGlobalViewSize 

```C++
void AIAC::Renderer::SetGlobalViewSize (
    float w,
    float h
) 
```




<hr>



### function SetGlobalViewToActivatedComponent 

```C++
void AIAC::Renderer::SetGlobalViewToActivatedComponent (
    StandardView standardView
) 
```




<hr>



### function SetMappingViewSize 

```C++
void AIAC::Renderer::SetMappingViewSize (
    float w,
    float h
) 
```




<hr>



### function UpdateGlobalViewCameraRotation 

```C++
void AIAC::Renderer::UpdateGlobalViewCameraRotation (
    double diffX,
    double diffY
) 
```




<hr>



### function UpdateGlobalViewCameraScale 

```C++
void AIAC::Renderer::UpdateGlobalViewCameraScale (
    double diff
) 
```




<hr>



### function UpdateGlobalViewCameraTranslation 

```C++
void AIAC::Renderer::UpdateGlobalViewCameraTranslation (
    double diffX,
    double diffY
) 
```




<hr>



### function ~Renderer 

```C++
virtual AIAC::Renderer::~Renderer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Render/Renderer.h`

