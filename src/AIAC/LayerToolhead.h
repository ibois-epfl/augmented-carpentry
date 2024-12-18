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

        /// @brief Destroy the  ttool view and recreate a new ttool object
        void ReloadCameraFromFile();
        /// @brief Destroy the  ttool view and recreate a new ttool object with given camera params
        void ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize);

        void DetectToolhead();

        /// @brief Update the ttool state from the UI
        void UpdateToolheadStateUI();

        /// @brief Save the current pose of the ttool to the config file and to the ttool model manager (as a fallback pose for the ttool)
        /// It will reset LayerToolhead state to None (i.e. stop tracking and pose input)
        void SavePose();
        /// @brief Reset the pose of the ttool to the last saved pose
        void ResetToLastSavedPose();
        /// @brief Set the pose from the value in the config initially read
        void ResetPoseFromConfig();

        /// @brief Get the current pose of the ttool
        glm::mat4x4 GetWorldPose();

    public: ///< Getters and setters
        /// @brief Get the Ttool State object of the ttool event type
        inline ttool::EventType GetTtoolState() const { return this->m_TtoolState; }
        /// @brief Set the current active object for both the ttool and acit menager
        void SetCurrentObject(std::string name);
        /// @brief Get the current pose of the ttool
        cv::Matx44f GetPose() const { return m_Pose; }
        /// @brief Get the current tracking status of the ttool
        std::string GetTrackingStatus() const { return TTool ? TTool->GetTrackingStatus() : "TTool not initialized"; }
        /// @brief Get the current classifier log of the ttool
        std::string GetClassifierLog() const { return TTool ? TTool->GetClassifierLog() : "TTool not initialized"; }
        std::vector<std::string> GetClassifierToolheadList() const {return m_ClassifierToolList; }

    private:
        /// @brief Sync the ttool tool manager and the acitoolhead to point to the same object
        void syncTToolAndACInfoToolhead();
    
    public:
        /// The ttool object
        std::shared_ptr<ttool::TTool> TTool;
        /// The UI state of the toolhead (None, PoseInput, Tracking)
        int ToolheadStateUI;
        /// Show the silouhette of the ttool
        bool IsShowSilouhette;
        /// Show the silouhette of the ttool
        bool IsShowShaded = false;
        /// Show the GOInfo toolhead's elements
        bool IsShowToolheadGOInfo;
        /// Save pose log
        bool IsSavePoseLog = false;

    private:
        /// The current state of the ttool (None, PoseInput, Tracking)
        ttool::EventType m_TtoolState;
        /// The current pose of the ttool
        cv::Matx44f m_Pose;
        /// The scaling factor for ttoolhead data to AC space
        float m_ACScaleFactor;
        std::vector<std::string> m_ClassifierToolList = {};

    public:
        /// The manager holding the toolheads and setting the active one
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}
