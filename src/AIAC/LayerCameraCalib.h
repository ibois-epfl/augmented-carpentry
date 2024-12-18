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

#include "AIAC/Layer.h"
#include "AIAC/Image.h"
#include "AIAC/Camera.h"
#include "CameraCalibrator.h"

namespace AIAC
{
    class LayerCameraCalib : public AIAC::Layer
    {
    public:
        LayerCameraCalib() = default;
        ~LayerCameraCalib() override = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void Clear();
        void StartCalibration();
        void StopCalibration() { m_IsCalibrating = false;};
        bool IsCalibrating() const { return m_IsCalibrating; }
        void StartCapturing() { Clear(); m_IsCapturing = true; }
        bool IsCapturing() const { return m_IsCapturing; }
        void SetSaveFilename(const std::string& filename) { SaveFilename = filename; }
        CameraCalibrator &GetCameraCalibrator() { return m_CameraCalibrator; }

    public:
        bool AutoCapture = true;
        bool JustCaptured = false;
        int Delay = 1500;
        int NumOfFrame = 100;
        std::string SaveFilename = "assets/tslam/calibration.yml";

    private:
        CameraCalibrator m_CameraCalibrator;
        bool m_IsCalibrating = false;
        bool m_IsCapturing = false;
        std::chrono::steady_clock::time_point prevCaptureTimestamp = std::chrono::steady_clock::now();
    };
}