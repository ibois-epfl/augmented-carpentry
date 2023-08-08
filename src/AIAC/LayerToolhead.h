#pragma once

#include "AIAC/Layer.h"

#include "AIAC/GOSys/GOPrimitive.h"

#include "ttool.hh"

#include "AIAC/ACInfoToolheadManager.h"

namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead()
            : IsShowSilouhette(true),
              ToolheadStateUI(-1),
              IsShowToolheadGOInfo(false),
              m_ACScaleFactor(50.0f),
            m_TtoolState(ttool::EventType::None)
        {
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
    
    private:
        /// @brief Sync the ttool tool manager and the acitoolhead to point to the same object
        void syncTToolAndACInfoToolhead();
    
    public: ///< Public members
        /// The ttool object
        std::shared_ptr<ttool::TTool> TTool;
        /// The UI state of the toolhead (None, PoseInput, Tracking)
        int ToolheadStateUI;
        /// Show the silouhette of the ttool
        bool IsShowSilouhette;
        /// Show the silouhette of the ttool
        bool IsShowShaded;
        /// Show the GOInfo toolhead's elements
        bool IsShowToolheadGOInfo;
        /// Save pose log
        bool IsSavePoseLog = false;

    private: ///< Private members
        /// The current state of the ttool (None, PoseInput, Tracking)
        ttool::EventType m_TtoolState;
        /// The current pose of the ttool
        cv::Matx44f m_Pose;
        /// The scaling factor for ttoolhead data to AC space
        float m_ACScaleFactor;

    public:
        /// The manager holding the toolheads and setting the active one
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}