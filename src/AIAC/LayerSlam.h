#pragma once

#include <opencv2/opencv.hpp>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tslam.h"
#include "AIAC/Layer.h"


namespace AIAC
{
    class LayerSlam : public AIAC::Layer
    {
    public:
        LayerSlam() = default;
        ~LayerSlam() = default;

        void OnAttach() override;
        virtual void OnFrameStart() override;
        virtual void OnUIRender() override;

        inline const bool IsTracked() { return m_IsTracked; }
        inline const cv::Mat GetCamPoseCv() { return m_CamPose; }
        glm::mat4 GetCamPoseGlm();

    public:
        tslam::TSlam Slam;

    private:
        cv::Mat m_CamPose = cv::Mat();
        bool m_IsTracked = false;
    };
}