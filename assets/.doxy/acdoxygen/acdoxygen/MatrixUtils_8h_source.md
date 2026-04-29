

# File MatrixUtils.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**MatrixUtils.h**](MatrixUtils_8h.md)

[Go to the documentation of this file](MatrixUtils_8h.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#pragma once

#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

inline void CvtGlmMat2CvMat(const glm::mat4 &glmMat, cv::Mat &cvMat)
{
    cvMat = cv::Mat(4, 4, CV_32FC1);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cvMat.at<float>(i, j) = glmMat[j][i];
        }
    }
}

inline void CvtCvMat2GlmMat(const cv::Mat &cvMat, glm::mat4 &glmMat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glmMat[j][i] = cvMat.at<float>(i, j);
        }
    }
}

inline void CvtCvMat2GlmMat(const cv::Mat &cvMat, glm::mat3 &glmMat)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            glmMat[j][i] = cvMat.at<float>(i, j);
        }
    }
}

inline cv::Vec4f ConvertRotationMatrixToQuaternion(cv::Mat R) {
    cv::Vec4f q;
    q[3] = sqrt(1.0 + R.at<float>(0,0) + R.at<float>(1,1) + R.at<float>(2,2)) / 2.0;
    q[0] = (R.at<float>(2,1) - R.at<float>(1,2)) / (4.0 * q[3]);
    q[1] = (R.at<float>(0,2) - R.at<float>(2,0)) / (4.0 * q[3]);
    q[2] = (R.at<float>(1,0) - R.at<float>(0,1)) / (4.0 * q[3]);
    return q;
}

inline void ConvertTransMatToTvecAndQvec(cv::Matx44f transMat, cv::Vec3f &tvec, cv::Vec4f &qvec) {
    auto tTransMat = cv::Mat(transMat);

    tvec[0] = tTransMat.at<float>(0, 3);
    tvec[1] = tTransMat.at<float>(1, 3);
    tvec[2] = tTransMat.at<float>(2, 3);

    cv::Mat R = tTransMat(cv::Rect(0, 0, 3, 3));
    qvec = ConvertRotationMatrixToQuaternion(R);
}
```


