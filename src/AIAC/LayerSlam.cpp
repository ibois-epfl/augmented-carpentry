#include "AIAC/LayerSlam.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

namespace AIAC
{
    void LayerSlam::OnAttach()
    {
        AIAC_INFO("LayerSlam attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();

        Slam.setMap("/home/tpp/UCOSlam-IBOIS/build/utils/long_new_param_comb.map");
        Slam.setVocabulary("/home/tpp/UCOSlam-IBOIS/orb.fbow");
        Slam.setCamParams("/home/tpp/UCOSlam-IBOIS/example/calibration_webcam.yml");
        Slam.setInstancing(true);
    }

    void LayerSlam::OnFrameAwake()
    {
        AIAC_INFO("LayerSlam OnFrameAwake");
    }

    void LayerSlam::OnFrameStart()
    {
        AIAC_INFO("LayerSlam frame start");

        cv::Mat currentFrame =
            AIAC::Application::GetInstance().GetLayer<AIAC::LayerCamera>()
                ->GetCurrentFrame().GetCvMat();
        
        m_IsTracked = Slam.process(currentFrame, m_CamPose);
        
        AIAC_INFO(m_IsTracked);
    }

    void LayerSlam::OnFrameEnd()
    {
        AIAC_INFO("LayerSlam frame end");
    }

    void LayerSlam::OnUIRender()
    {
    }

    void LayerSlam::OnFrameFall()
    {
        AIAC_INFO("LayerSlam is fall");
    }

    void LayerSlam::OnDetach()
    {
        AIAC_INFO("LayerSlam detached");
    }
}