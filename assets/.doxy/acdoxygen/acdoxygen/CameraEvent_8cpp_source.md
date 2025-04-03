

# File CameraEvent.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**EventSys**](dir_bda428afb66b315b23b4e646d7591fb3.md) **>** [**CameraEvent.cpp**](CameraEvent_8cpp.md)

[Go to the documentation of this file](CameraEvent_8cpp.md)


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
#include "aiacpch.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"
#include "AIAC/Config.h"

namespace AIAC
{
    void CameraCalibrationLoadedEvent::OnCameraCalibrationFileLoaded()
    {
        // update the config first
        AIAC::Config::UpdateEntry(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, m_FilePath);

        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromFile(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));
        AIAC_APP.GetLayer<LayerToolhead>()->ReloadCameraFromFile();

        // Since the camera calibration file has changed, making it uncompilable with the previous SLAM map
        // we need to stop the SLAM process, or it will crash
        AIAC_APP.GetLayer<LayerSlam>()->ToProcess = false;

        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();
    }
}
```


