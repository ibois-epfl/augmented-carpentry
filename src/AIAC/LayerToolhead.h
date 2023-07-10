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
            :IsShowSilouhette(true),
            ToolheadStateUI(-1),
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

        /// @brief Get the current pose of the ttool
        glm::mat4x4 GetWorldPose();

        /// @brief Update the ttool state from the UI
        void UpdateToolheadStateUI();

    public: ///< Getters and setters
        /**
         * @brief Get the Ttool State object of the ttool event type
         * 
         * @return ttool::EventType None, poseinput or tracking
         */
        inline ttool::EventType GetTtoolState() const { return this->m_TtoolState; }
        /**
         * @brief Set the current active object for both the ttool and acit menager
         * 
         * @param name 
         */
        void SetCurrentObject(std::string name);
    
    private:
        void syncTToolAndACInfoToolhead();
    
    public: ///< Public members
        /// The ttool object
        std::shared_ptr<ttool::TTool> TTool;
        /// The UI state of the toolhead (None, PoseInput, Tracking)
        int ToolheadStateUI;
        /// Show the silouhette of the ttool
        bool IsShowSilouhette;

    private: ///< Private members
        /// The current state of the ttool (None, PoseInput, Tracking)
        ttool::EventType m_TtoolState;
        /// The current pose of the ttool
        cv::Matx44f m_Pose;

    public:
        /// The manager holding the toolheads and setting the active one
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}