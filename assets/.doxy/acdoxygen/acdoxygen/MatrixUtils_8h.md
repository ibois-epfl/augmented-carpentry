

# File MatrixUtils.h



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**MatrixUtils.h**](MatrixUtils_8h.md)

[Go to the source code of this file](MatrixUtils_8h_source.md)



* `#include <opencv2/opencv.hpp>`
* `#include <glm/glm.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  cv::Vec4f | [**ConvertRotationMatrixToQuaternion**](#function-convertrotationmatrixtoquaternion) (cv::Mat R) <br>_Convert a rotation matrix to a quaternion._  |
|  void | [**ConvertTransMatToTvecAndQvec**](#function-converttransmattotvecandqvec) (cv::Matx44f transMat, cv::Vec3f & tvec, cv::Vec4f & qvec) <br>_Convert a Transformation matrix to a translation vector and a quaternion vector._  |
|  void | [**CvtCvMat2GlmMat**](#function-cvtcvmat2glmmat) (const cv::Mat & cvMat, glm::mat4 & glmMat) <br> |
|  void | [**CvtCvMat2GlmMat**](#function-cvtcvmat2glmmat) (const cv::Mat & cvMat, glm::mat3 & glmMat) <br> |
|  void | [**CvtGlmMat2CvMat**](#function-cvtglmmat2cvmat) (const glm::mat4 & glmMat, cv::Mat & cvMat) <br> |




























## Public Functions Documentation




### function ConvertRotationMatrixToQuaternion 

_Convert a rotation matrix to a quaternion._ 
```C++
inline cv::Vec4f ConvertRotationMatrixToQuaternion (
    cv::Mat R
) 
```





**Parameters:**


* `R` The rotation matrix 



**Returns:**

cv::Vec4f The quaternion 





        

<hr>



### function ConvertTransMatToTvecAndQvec 

_Convert a Transformation matrix to a translation vector and a quaternion vector._ 
```C++
inline void ConvertTransMatToTvecAndQvec (
    cv::Matx44f transMat,
    cv::Vec3f & tvec,
    cv::Vec4f & qvec
) 
```





**Parameters:**


* `transMat` cv::Mat4x4 The transformation matrix 
* `tvec` cv::Vec3f The output of the translation vector 
* `qvec` cv::Vec4f The output of the quaternion vector



**Returns:**

empty 





        

<hr>



### function CvtCvMat2GlmMat 

```C++
inline void CvtCvMat2GlmMat (
    const cv::Mat & cvMat,
    glm::mat4 & glmMat
) 
```




<hr>



### function CvtCvMat2GlmMat 

```C++
inline void CvtCvMat2GlmMat (
    const cv::Mat & cvMat,
    glm::mat3 & glmMat
) 
```




<hr>



### function CvtGlmMat2CvMat 

```C++
inline void CvtGlmMat2CvMat (
    const glm::mat4 & glmMat,
    cv::Mat & cvMat
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/MatrixUtils.h`

