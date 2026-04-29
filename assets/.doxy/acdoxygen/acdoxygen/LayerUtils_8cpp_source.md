

# File LayerUtils.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerUtils.cpp**](LayerUtils_8cpp.md)

[Go to the documentation of this file](LayerUtils_8cpp.md)


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
#include <thread>
#include "LayerUtils.h"
#include "Config.h"
#include "Application.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"
#include "utils/Screenshot.h"

namespace AIAC {
    LayerUtils::LayerUtils() {
        LayerUtils::CreateFolder(m_UtilsPath);
    }

    void LayerUtils::OnFrameEnd() {
        if(this->m_Recording){
            this->m_VideoRecorder->CaptureFrames();
        }
        if(this->m_WindowScreenshot){
            this->TakeWindowScreenshot();
            this->m_WindowScreenshot = false;
        }
    }

    void LayerUtils::StartRecording(){
        AIAC_INFO("Started Recording");
        this->m_Recording = true;
        std::string savePath = this->GetSaveFolderPath();
        this->m_VideoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>(savePath);
    }

    void LayerUtils::StopRecording(){
        AIAC_INFO("Stopped Recording");
        this->m_Recording = false;
        this->m_Processing = true;
        std::thread([this]{
            this->m_VideoRecorder->MakeVideoFromFrames();
            this->m_VideoRecorder.reset();
            this->m_Processing = false;
        }).detach();
    }

    void LayerUtils::SetSaveFolderPath(const std::string& path){
        if(path.empty()) {
            AIAC_INFO("Using default path: {}", m_UtilsPath);
        } else {
            m_UtilsPath = path;
            AIAC_INFO("Using specified path: {}", m_UtilsPath);
        }
    }

    void LayerUtils::ExportHoleToolheadAxis(){
        AIAC_INFO("Hole and toolhead axis export");
        std::string savePath = this->GetSaveFolderPath();
        this->m_HoleToolheadAxisExporter = std::make_unique<AIAC::Utils::HoleToolheadAxisExporter>(savePath);
        this->m_HoleToolheadAxisExporter->ExportCoordinates();
    }

    bool LayerUtils::CreateFolder(const std::string& path) {
        if(std::filesystem::exists(path)) {
            AIAC_INFO("{0} folder already exists!", path);
            return true;
        }
        if(std::filesystem::create_directories(path)) {
            AIAC_INFO("Created {0} folder", path);
            return true;
        } else {
            AIAC_ERROR("Failed to create {0} folder", path);
            return false;
        }
    }

    void LayerUtils::TakeWindowScreenshot(){
        std::string savePath = this->GetSaveFolderPath();
        AIAC::Utils::Screenshot recorder(savePath);
        recorder.CaptureWindow();
        AIAC_INFO("Captured screenshot of the current window");
    }

    void LayerUtils::TakeBufferScreenshot(){
        std::string savePath = this->GetSaveFolderPath();
        AIAC::Utils::Screenshot recorder(savePath);
        recorder.CaptureBuffer();
        AIAC_INFO("Captured colored buffer of the current window");
    }
}

```


