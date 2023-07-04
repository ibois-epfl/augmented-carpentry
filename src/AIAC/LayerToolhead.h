#pragma once

#include "AIAC/Layer.h"

#include "AIAC/GOSys/GOPrimitive.h"

#include "ttool.hh"

namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead() = default;
        virtual ~LayerToolhead() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void ReloadCameraFromFile();
        void ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize);

        glm::mat4x4 GetWorldPose();

    public:
        std::shared_ptr<ttool::TTool> TTool;
        int ToolheadStateUI = -1;

    protected:
        void UpdateToolheadState();
        void OnPoseManipulation();

    protected:
        ttool::EventType m_TtoolState = ttool::EventType::None;
        cv::Matx44f m_Pose;
        std::vector<std::shared_ptr<GOPrimitive>> m_GOObjects;
        std::vector<glm::vec3> m_Points = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
    };
}