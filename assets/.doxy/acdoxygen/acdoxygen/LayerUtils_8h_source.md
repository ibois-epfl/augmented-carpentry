

# File LayerUtils.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerUtils.h**](LayerUtils_8h.md)

[Go to the documentation of this file](LayerUtils_8h.md)


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

#include "AIAC/Layer.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"
#include "Config.h"
#include "AIAC/GOSys/GOPrimitive.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:
        LayerUtils();
        void OnFrameEnd() override;
        static bool CreateFolder(const std::string& path);
        void SetSaveFolderPath(const std::string& path);
        std::string GetSaveFolderPath(){return m_UtilsPath;};

    public: 
        void StartRecording();
        void StopRecording();
        bool IsProcessing(){return m_Processing;};

    public: 
        void ExportHoleToolheadAxis();

    public: 
        void TakeWindowScreenshot();
        void TakeBufferScreenshot();
        void SetWindowScreenshot(bool value){m_WindowScreenshot = value;};

    private:
        std::string m_UtilsPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS,
                                                                 AIAC::Config::UTILS_PATH,
                                                                 "./temp");
    private: 
        bool m_Recording = false;
        bool m_Processing = false;
        std::unique_ptr<AIAC::Utils::VideoRecorder> m_VideoRecorder;

    private: 
        std::unique_ptr<AIAC::Utils::HoleToolheadAxisExporter> m_HoleToolheadAxisExporter;

    private: 
        bool m_WindowScreenshot = false;
    };
}

```


