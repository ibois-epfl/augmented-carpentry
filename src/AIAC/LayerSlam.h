#pragma once

#include <opencv2/opencv.hpp>

#include "tslam.h"
#include "AIAC/Layer.h"

namespace AIAC
{
    class LayerSlam : public AIAC::Layer
    {
    public:
        LayerSlam() = default;
        ~LayerSlam() = default;

        void OnAttach();
        virtual void OnFrameAwake() override;
        virtual void OnFrameStart() override;
        virtual void OnFrameEnd() override;
        virtual void OnUIRender() override;
        virtual void OnFrameFall() override;
        virtual void OnDetach() override;
        
        cv::Mat GetCamPose();

    public:
        tslam::TSlam Slam;

    private:
        cv::Mat m_CamPose = cv::Mat();
        bool m_IsTracked = false;
    };
}