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
        {
            this->ACInfoToolheadManager = std::make_shared<AIAC::ACInfoToolheadManager>();
        };

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void ReloadCameraFromFile();
        void ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize);

        glm::mat4x4 GetWorldPose();

    private:
        void UpdateToolheadState();
        void OnPoseManipulation();

    public:
        std::shared_ptr<ttool::TTool> TTool;
        int ToolheadStateUI = -1;

    private:
        ttool::EventType m_TtoolState = ttool::EventType::None;
        cv::Matx44f m_Pose;
        std::vector<std::shared_ptr<GOPrimitive>> m_GOObjects;
        std::vector<glm::vec3> m_Points = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
        cv::Mat m_SilouhetteMat;

    public:
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}