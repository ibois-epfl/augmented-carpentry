#pragma once

#include "AIAC/Layer.h"
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

        glm::mat4 GetWorldPose();

    public:
        std::shared_ptr<ttool::TTool> TTool;
        int ToolheadStateUI = -1;

    protected:
        void UpdateToolheadState();
        void OnPoseManipulation();

    protected:
        ttool::EventType ttoolState = ttool::EventType::None;
        cv::Matx44f m_Pose;
    };
}