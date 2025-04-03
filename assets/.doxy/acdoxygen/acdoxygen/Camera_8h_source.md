

# File Camera.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Camera.h**](Camera_8h.md)

[Go to the documentation of this file](Camera_8h.md)


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

#include "AIAC/Image.h"

namespace AIAC
{
    class Camera
    {
    public:
        Camera();
        ~Camera() {};
        void Open(int id);

        bool LoadCameraParams(const std::string &filePath);

        inline void UpdateFov();

        const AIAC::Image GetNextFrame();

        inline AIAC::Image &GetColorCurrentFrame() { return m_CalibratedCurrentFrame; }
        inline AIAC::Image &GetCurrentFrame() { return m_GrayCalibratedCurrentFrame; }
        inline AIAC::Image &GetRawCurrentFrame() { return m_RawCurrentFrame; }
        AIAC::Image &GetCenterCroppedCurrentFrame(float ratioX = 0.6f, float ratioY = 0.75f);

        inline const std::string GetCalibrationFilePath() const { return m_CalibFilePath; }

        void UpdateCameraParamFromFile(const std::string &filePath);

        void UpdateCameraParamFromSlamMap(const int paramWidth, const int paramHeight, const cv::Mat &cameraMatrix);

        inline const cv::Mat GetCameraMatrix() { return m_CameraMatrix;};
        inline const cv::Mat GetDistortionCoef() { return m_DistortionCoef; }

        inline const uint32_t GetRawWidth() const {return m_PhysicalWidth; }

        inline const uint32_t GetRawHeight() const {return m_PhysicalHeight; }

        inline const uint32_t GetWidth() const { return m_ParamWidth; }

        inline const uint32_t GetHeight() const { return m_ParamHeight; }

        inline const std::pair<float, float> GetFov() const { return std::make_pair(m_FovX, m_FovY); }

        bool IsOpened() const { return m_IsOpened; }

        bool IsPhysicalAndParamWidthHeightMatched() const { return m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight; }

    public:
        bool FlipHorizontal = false;
        bool FlipVertical = false;

    private:
        bool m_IsCamMatrixInit = false;
        bool m_IsFisheye = false;
        std::string m_CalibFilePath;
        cv::Mat m_CameraMatrix;
        cv::Mat m_DistortionCoef;
        cv::Mat m_UndistortMap[2];

        int m_PhysicalWidth, m_PhysicalHeight;
        int m_ParamWidth, m_ParamHeight;
        float m_FovX = -1.0f, m_FovY = -1.0f;

        Image m_RawCurrentFrame;
        Image m_CenterCroppedCurrentFrame;
        Image m_CalibratedCurrentFrame;
        Image m_GrayCalibratedCurrentFrame;

        cv::VideoCapture m_VideoCapture;
        bool m_IsOpened = false;
    };
}
```


