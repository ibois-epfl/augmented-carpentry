

# File LayerCameraCalib.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerCameraCalib.cpp**](LayerCameraCalib_8cpp.md)

[Go to the documentation of this file](LayerCameraCalib_8cpp.md)


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
#include "LayerCameraCalib.h"
#include "Application.h"

void AIAC::LayerCameraCalib::OnAttach() {
    // nothing to do here
}

void AIAC::LayerCameraCalib::OnFrameStart() {
    if (!m_IsCalibrating) {
        return;
    }

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    JustCaptured = false;
    if (AutoCapture && m_IsCapturing && std::chrono::duration_cast<std::chrono::milliseconds>(now - prevCaptureTimestamp).count() > Delay) {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawCurrentFrame().GetCvMat().copyTo(currentFrame);
        m_CameraCalibrator.AddImage(currentFrame);

        prevCaptureTimestamp = now;
        JustCaptured = true;
        AIAC_INFO("Captured frame: {0} / {1}", m_CameraCalibrator.GetImageAmount(), NumOfFrame);
    }

    if(m_CameraCalibrator.GetImageAmount() >= NumOfFrame) {
        try {
            if(m_CameraCalibrator.RunCalibration()){
                m_CameraCalibrator.Save(SaveFilename);
                AIAC_INFO("Calibration finished, file is saved to {0}", SaveFilename);
            }
        } catch (std::exception const& err){
            AIAC_ERROR(err.what());
        }
        m_IsCapturing = false;
        m_CameraCalibrator.ClearImages();
    }
}

void AIAC::LayerCameraCalib::StartCalibration() {
    AIAC_INFO("Starting calibration");
    m_IsCalibrating = true;
    Clear();
}

void AIAC::LayerCameraCalib::Clear() {
    m_CameraCalibrator.ClearImages();
    prevCaptureTimestamp = std::chrono::steady_clock::now();
}
```


