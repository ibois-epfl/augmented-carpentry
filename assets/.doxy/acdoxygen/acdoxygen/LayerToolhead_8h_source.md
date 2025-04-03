

# File LayerToolhead.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerToolhead.h**](LayerToolhead_8h.md)

[Go to the documentation of this file](LayerToolhead_8h.md)


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
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoToolheadManager.h"

#include <ttool.hh>



namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead()
            : IsShowSilouhette(false),
              ToolheadStateUI(-1),
              IsShowToolheadGOInfo(false),
            m_TtoolState(ttool::EventType::None)
        {
            this->m_ACScaleFactor = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
            this->ACInfoToolheadManager = std::make_shared<AIAC::ACInfoToolheadManager>();
        };

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void ReloadCameraFromFile();
        void ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize);

        void DetectToolhead();

        void UpdateToolheadStateUI();

        void SavePose();
        void ResetToLastSavedPose();
        void ResetPoseFromConfig();

        glm::mat4x4 GetWorldPose();

    public: 
        inline ttool::EventType GetTtoolState() const { return this->m_TtoolState; }
        void SetCurrentObject(std::string name);
        cv::Matx44f GetPose() const { return m_Pose; }
        std::string GetTrackingStatus() const { return TTool ? TTool->GetTrackingStatus() : "TTool not initialized"; }
        std::string GetClassifierLog() const { return TTool ? TTool->GetClassifierLog() : "TTool not initialized"; }
        std::vector<std::string> GetClassifierToolheadList() const {return m_ClassifierToolList; }

    private:
        void syncTToolAndACInfoToolhead();
    
    public:
        std::shared_ptr<ttool::TTool> TTool;
        int ToolheadStateUI;
        bool IsShowSilouhette;
        bool IsShowShaded = false;
        bool IsShowToolheadGOInfo;
        bool IsSavePoseLog = false;

    private:
        ttool::EventType m_TtoolState;
        cv::Matx44f m_Pose;
        float m_ACScaleFactor;
        std::vector<std::string> m_ClassifierToolList = {};

    public:
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}
```


