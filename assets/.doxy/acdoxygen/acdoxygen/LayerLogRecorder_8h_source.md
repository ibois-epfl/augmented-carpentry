

# File LayerLogRecorder.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerLogRecorder.h**](LayerLogRecorder_8h.md)

[Go to the documentation of this file](LayerLogRecorder_8h.md)


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

#include <fstream>
#include "Layer.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace AIAC
{
    class LayerLogRecorder : public AIAC::Layer
    {
    public:
        LayerLogRecorder() = default;
        virtual ~LayerLogRecorder() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    public:
        void StartRecording(std::string logRootFolderPath = "");

        void StopRecording();

        void PauseRecording();

        void ResumeRecording();

        bool IsRecording() const { return m_IsRecording; }

         bool IsPaused() const { return m_IsPaused; }
    private:
        void LogHeader();

        void LogSlamStatus();

        void LogTToolHead();

        void LogTToolPose();

        void InitTToolStatus();

        void LogTToolTransformation(const std::string& status);

        void LogACIM();

        void InitACIMStatus();

        void LogACIMTransformation();


    private:
        bool m_IsRecording = false;
        bool m_IsPaused = false;
        std::string m_LogFolderPath;
        std::string m_LogFilePath;
        std::ofstream m_LogFile;
        int m_FrameCount = 0;

        // variables for TTool
        std::set<std::string> m_TToolStatusToLog = {
            "PoseInput",
            "Tracking",
        };
        std::string m_TToolPreviousToolheadName;

        // variables for ACInfoModel
        std::string m_ACIMPreviousActivatedComponentID;
        bool m_IsActivatedComponentDone = false;
        double m_ACIMOffset = INFINITY;
        int m_ACIMRotation = INT_MAX;
        bool m_ACIMFlip = false;
        std::unordered_map<std::string, bool> m_ACIMComponentStatus;
    };
}
```


