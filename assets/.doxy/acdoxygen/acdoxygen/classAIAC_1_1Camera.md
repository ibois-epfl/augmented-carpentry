

# Class AIAC::Camera



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Camera**](classAIAC_1_1Camera.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**FlipHorizontal**](#variable-fliphorizontal)   = `false`<br>_Flag indicating if the captured image should be flipped._  |
|  bool | [**FlipVertical**](#variable-flipvertical)   = `false`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Camera**](#function-camera) () <br> |
|  const std::string | [**GetCalibrationFilePath**](#function-getcalibrationfilepath) () const<br>_Get the path to the camera calibration parameters._  |
|  const cv::Mat | [**GetCameraMatrix**](#function-getcameramatrix) () <br>_Get the camera matrix._  |
|  [**AIAC::Image**](classAIAC_1_1Image.md) & | [**GetCenterCroppedCurrentFrame**](#function-getcentercroppedcurrentframe) (float ratioX=0.6f, float ratioY=0.75f) <br>_Get the raw current frame, but borders are set to black according to the specified ratio._  |
|  [**AIAC::Image**](classAIAC_1_1Image.md) & | [**GetColorCurrentFrame**](#function-getcolorcurrentframe) () <br>_Get the current color (calibrated) frame from the camera._  |
|  [**AIAC::Image**](classAIAC_1_1Image.md) & | [**GetCurrentFrame**](#function-getcurrentframe) () <br>_Get the current grayscale (calibrated) frame from the camera._  |
|  const cv::Mat | [**GetDistortionCoef**](#function-getdistortioncoef) () <br>_Get the distortion coefficients matrix._  |
|  const std::pair&lt; float, float &gt; | [**GetFov**](#function-getfov) () const<br>_Get the field of view (FOV) of the camera._  |
|  const uint32\_t | [**GetHeight**](#function-getheight) () const<br>_Get the calibrated height of the camera frame._  |
|  const [**AIAC::Image**](classAIAC_1_1Image.md) | [**GetNextFrame**](#function-getnextframe) () <br>_Capture and preprocess the next frame from the camera._  |
|  [**AIAC::Image**](classAIAC_1_1Image.md) & | [**GetRawCurrentFrame**](#function-getrawcurrentframe) () <br>_Get the current raw (uncalibrated) frame from the camera._  |
|  const uint32\_t | [**GetRawHeight**](#function-getrawheight) () const<br>_Get the raw (uncalibrated) height of the camera frame._  |
|  const uint32\_t | [**GetRawWidth**](#function-getrawwidth) () const<br>_Get the raw (uncalibrated) width of the camera frame._  |
|  const uint32\_t | [**GetWidth**](#function-getwidth) () const<br>_Get the calibrated width of the camera frame._  |
|  bool | [**IsOpened**](#function-isopened) () const<br>_Check if the camera is opened._  |
|  bool | [**IsPhysicalAndParamWidthHeightMatched**](#function-isphysicalandparamwidthheightmatched) () const<br>_Check if the physical and parameterized width and height match._  |
|  bool | [**LoadCameraParams**](#function-loadcameraparams) (const std::string & filePath) <br>_Loads camera parameters from a configuration file._  |
|  void | [**Open**](#function-open) (int id) <br>_Open the camera with the specified id._  |
|  void | [**UpdateCameraParamFromFile**](#function-updatecameraparamfromfile) (const std::string & filePath) <br>_Force to update the default camera param._  |
|  void | [**UpdateCameraParamFromSlamMap**](#function-updatecameraparamfromslammap) (const int paramWidth, const int paramHeight, const cv::Mat & cameraMatrix) <br>_Update the camera parameters from the SLAM-generated map._  |
|  void | [**UpdateFov**](#function-updatefov) () <br>_Update the field of view (FOV) values based on camera parameters._  |
|   | [**~Camera**](#function-camera) () <br> |




























## Public Attributes Documentation




### variable FlipHorizontal 

_Flag indicating if the captured image should be flipped._ 
```C++
bool AIAC::Camera::FlipHorizontal;
```




<hr>



### variable FlipVertical 

```C++
bool AIAC::Camera::FlipVertical;
```




<hr>
## Public Functions Documentation




### function Camera 

```C++
AIAC::Camera::Camera () 
```




<hr>



### function GetCalibrationFilePath 

_Get the path to the camera calibration parameters._ 
```C++
inline const std::string AIAC::Camera::GetCalibrationFilePath () const
```





**Returns:**

A constant reference to the camera calibration file path. 





        

<hr>



### function GetCameraMatrix 

_Get the camera matrix._ 
```C++
inline const cv::Mat AIAC::Camera::GetCameraMatrix () 
```





**Returns:**

A constant reference to the camera matrix. 





        

<hr>



### function GetCenterCroppedCurrentFrame 

_Get the raw current frame, but borders are set to black according to the specified ratio._ 
```C++
AIAC::Image & AIAC::Camera::GetCenterCroppedCurrentFrame (
    float ratioX=0.6f,
    float ratioY=0.75f
) 
```





**Parameters:**


* `ratioX` How much of % the width of the image is kept. (default: 0.75, i.e. 75%). 
* `ratioY` How much of % the height of the image is kept. (default: 0.9, i.e. 90%). 



**Returns:**

A reference to the center-cropped current frame image. 





        

<hr>



### function GetColorCurrentFrame 

_Get the current color (calibrated) frame from the camera._ 
```C++
inline AIAC::Image & AIAC::Camera::GetColorCurrentFrame () 
```





**Returns:**

A reference to the current color frame image. 





        

<hr>



### function GetCurrentFrame 

_Get the current grayscale (calibrated) frame from the camera._ 
```C++
inline AIAC::Image & AIAC::Camera::GetCurrentFrame () 
```





**Returns:**

A reference to the current grayscale frame image. 





        

<hr>



### function GetDistortionCoef 

_Get the distortion coefficients matrix._ 
```C++
inline const cv::Mat AIAC::Camera::GetDistortionCoef () 
```





**Returns:**

A constant reference to the distortion coefficient matrix. 





        

<hr>



### function GetFov 

_Get the field of view (FOV) of the camera._ 
```C++
inline const std::pair< float, float > AIAC::Camera::GetFov () const
```





**Returns:**

A pair of floats representing the horizontal and vertical FOV of the camera. 





        

<hr>



### function GetHeight 

_Get the calibrated height of the camera frame._ 
```C++
inline const uint32_t AIAC::Camera::GetHeight () const
```





**Returns:**

The calibrated height of the camera frame as an unsigned 32-bit integer. 





        

<hr>



### function GetNextFrame 

_Capture and preprocess the next frame from the camera._ 
```C++
const AIAC::Image AIAC::Camera::GetNextFrame () 
```





**Returns:**

A grayscale image representing the captured and processed frame. 





        

<hr>



### function GetRawCurrentFrame 

_Get the current raw (uncalibrated) frame from the camera._ 
```C++
inline AIAC::Image & AIAC::Camera::GetRawCurrentFrame () 
```





**Returns:**

A reference to the current raw frame image. 





        

<hr>



### function GetRawHeight 

_Get the raw (uncalibrated) height of the camera frame._ 
```C++
inline const uint32_t AIAC::Camera::GetRawHeight () const
```





**Returns:**

The raw height of the camera frame as an unsigned 32-bit integer. 





        

<hr>



### function GetRawWidth 

_Get the raw (uncalibrated) width of the camera frame._ 
```C++
inline const uint32_t AIAC::Camera::GetRawWidth () const
```





**Returns:**

The raw width of the camera frame as an unsigned 32-bit integer. 





        

<hr>



### function GetWidth 

_Get the calibrated width of the camera frame._ 
```C++
inline const uint32_t AIAC::Camera::GetWidth () const
```





**Returns:**

The calibrated width of the camera frame as an unsigned 32-bit integer. 





        

<hr>



### function IsOpened 

_Check if the camera is opened._ 
```C++
inline bool AIAC::Camera::IsOpened () const
```





**Returns:**

True if the camera is opened, false otherwise. 





        

<hr>



### function IsPhysicalAndParamWidthHeightMatched 

_Check if the physical and parameterized width and height match._ 
```C++
inline bool AIAC::Camera::IsPhysicalAndParamWidthHeightMatched () const
```





**Returns:**

True if the physical and parameterized width and height match, false otherwise. 





        

<hr>



### function LoadCameraParams 

_Loads camera parameters from a configuration file._ 
```C++
bool AIAC::Camera::LoadCameraParams (
    const std::string & filePath
) 
```





**Parameters:**


* `filePath` The path to the camera parameter configuration file. 



**Returns:**

True if the camera parameters are loaded successfully, false otherwise. 





        

<hr>



### function Open 

_Open the camera with the specified id._ 
```C++
void AIAC::Camera::Open (
    int id
) 
```





**Parameters:**


* `id` The id of the camera to open. 




        

<hr>



### function UpdateCameraParamFromFile 

_Force to update the default camera param._ 
```C++
void AIAC::Camera::UpdateCameraParamFromFile (
    const std::string & filePath
) 
```





**Parameters:**


* `filePath` The path to the camera param file. 




        

<hr>



### function UpdateCameraParamFromSlamMap 

_Update the camera parameters from the SLAM-generated map._ 
```C++
void AIAC::Camera::UpdateCameraParamFromSlamMap (
    const int paramWidth,
    const int paramHeight,
    const cv::Mat & cameraMatrix
) 
```





**Parameters:**


* `paramWidth` [**Image**](classAIAC_1_1Image.md) width for camera calibration. 
* `paramHeight` [**Image**](classAIAC_1_1Image.md) height for camera calibration. 
* `cameraMatrix` The camera matrix 




        

<hr>



### function UpdateFov 

_Update the field of view (FOV) values based on camera parameters._ 
```C++
inline void AIAC::Camera::UpdateFov () 
```




<hr>



### function ~Camera 

```C++
inline AIAC::Camera::~Camera () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Camera.h`

