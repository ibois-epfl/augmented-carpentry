

# Class AIAC::CameraCalibrator



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CameraCalibrator**](classAIAC_1_1CameraCalibrator.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Pattern**](#enum-pattern)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  float | [**aspectRatio**](#variable-aspectratio)   = `0.0f`<br> |
|  cv::Size | [**boardSize**](#variable-boardsize)   = `cv::Size(19, 13)`<br> |
|  bool | [**calibFixPrincipalPoint**](#variable-calibfixprincipalpoint)   = `false`<br> |
|  bool | [**calibZeroTangentDist**](#variable-calibzerotangentdist)   = `false`<br> |
|  Pattern | [**calibrationPattern**](#variable-calibrationpattern)   = `Pattern::CHESSBOARD`<br> |
|  cv::Mat | [**cameraMatrix**](#variable-cameramatrix)  <br> |
|  cv::Mat | [**distCoeffs**](#variable-distcoeffs)  <br> |
|  bool | [**fixDistortion**](#variable-fixdistortion)   = `false`<br> |
|  bool | [**flipVertical**](#variable-flipvertical)   = `false`<br> |
|  float | [**gridWidth**](#variable-gridwidth)   = `squareSize \* (boardSize.width - 1)`<br> |
|  cv::Size | [**imageSize**](#variable-imagesize)  <br> |
|  std::vector&lt; float &gt; | [**reprojErrs**](#variable-reprojerrs)  <br> |
|  cv::Mat | [**rvecs**](#variable-rvecs)  <br> |
|  float | [**squareSize**](#variable-squaresize)   = `20.0f`<br> |
|  double | [**totalAvgErr**](#variable-totalavgerr)  <br> |
|  cv::Mat | [**tvecs**](#variable-tvecs)  <br> |
|  bool | [**useFisheye**](#variable-usefisheye)   = `false`<br> |
|  bool | [**useFixedPoint**](#variable-usefixedpoint)   = `false`<br> |
|  int | [**winSize**](#variable-winsize)   = `11`<br> |
|  bool | [**writeExtrinsics**](#variable-writeextrinsics)   = `true`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddImage**](#function-addimage) (const cv::Mat & image) <br> |
|   | [**CameraCalibrator**](#function-cameracalibrator) () <br> |
|  void | [**ClearImages**](#function-clearimages) () <br> |
|  int | [**GetImageAmount**](#function-getimageamount) () const<br> |
|  bool | [**RunCalibration**](#function-runcalibration) (cv::Mat \* imgForDisplay=nullptr) <br>_[board\_corners_  |
|  void | [**Save**](#function-save) (const std::string & filename) <br> |
|   | [**~CameraCalibrator**](#function-cameracalibrator) () <br> |




























## Public Types Documentation




### enum Pattern 

```C++
enum AIAC::CameraCalibrator::Pattern {
    NOT_EXISTING,
    CHESSBOARD,
    CIRCLES_GRID,
    ASYMMETRIC_CIRCLES_GRID
};
```




<hr>
## Public Attributes Documentation




### variable aspectRatio 

```C++
float AIAC::CameraCalibrator::aspectRatio;
```




<hr>



### variable boardSize 

```C++
cv::Size AIAC::CameraCalibrator::boardSize;
```




<hr>



### variable calibFixPrincipalPoint 

```C++
bool AIAC::CameraCalibrator::calibFixPrincipalPoint;
```




<hr>



### variable calibZeroTangentDist 

```C++
bool AIAC::CameraCalibrator::calibZeroTangentDist;
```




<hr>



### variable calibrationPattern 

```C++
Pattern AIAC::CameraCalibrator::calibrationPattern;
```




<hr>



### variable cameraMatrix 

```C++
cv::Mat AIAC::CameraCalibrator::cameraMatrix;
```




<hr>



### variable distCoeffs 

```C++
cv::Mat AIAC::CameraCalibrator::distCoeffs;
```




<hr>



### variable fixDistortion 

```C++
bool AIAC::CameraCalibrator::fixDistortion;
```




<hr>



### variable flipVertical 

```C++
bool AIAC::CameraCalibrator::flipVertical;
```




<hr>



### variable gridWidth 

```C++
float AIAC::CameraCalibrator::gridWidth;
```




<hr>



### variable imageSize 

```C++
cv::Size AIAC::CameraCalibrator::imageSize;
```




<hr>



### variable reprojErrs 

```C++
std::vector<float> AIAC::CameraCalibrator::reprojErrs;
```




<hr>



### variable rvecs 

```C++
cv::Mat AIAC::CameraCalibrator::rvecs;
```




<hr>



### variable squareSize 

```C++
float AIAC::CameraCalibrator::squareSize;
```




<hr>



### variable totalAvgErr 

```C++
double AIAC::CameraCalibrator::totalAvgErr;
```




<hr>



### variable tvecs 

```C++
cv::Mat AIAC::CameraCalibrator::tvecs;
```




<hr>



### variable useFisheye 

```C++
bool AIAC::CameraCalibrator::useFisheye;
```




<hr>



### variable useFixedPoint 

```C++
bool AIAC::CameraCalibrator::useFixedPoint;
```




<hr>



### variable winSize 

```C++
int AIAC::CameraCalibrator::winSize;
```




<hr>



### variable writeExtrinsics 

```C++
bool AIAC::CameraCalibrator::writeExtrinsics;
```




<hr>
## Public Functions Documentation




### function AddImage 

```C++
void AIAC::CameraCalibrator::AddImage (
    const cv::Mat & image
) 
```




<hr>



### function CameraCalibrator 

```C++
inline AIAC::CameraCalibrator::CameraCalibrator () 
```




<hr>



### function ClearImages 

```C++
inline void AIAC::CameraCalibrator::ClearImages () 
```




<hr>



### function GetImageAmount 

```C++
inline int AIAC::CameraCalibrator::GetImageAmount () const
```




<hr>



### function RunCalibration 

_[board\_corners_ 
```C++
bool AIAC::CameraCalibrator::RunCalibration (
    cv::Mat * imgForDisplay=nullptr
) 
```




<hr>



### function Save 

```C++
void AIAC::CameraCalibrator::Save (
    const std::string & filename
) 
```




<hr>



### function ~CameraCalibrator 

```C++
inline AIAC::CameraCalibrator::~CameraCalibrator () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/CameraCalibrator.h`

