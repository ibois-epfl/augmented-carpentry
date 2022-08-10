#include "AIAC/LayerExample.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

namespace AIAC
{
    void LayerExample::OnAttach()
    {
        AIAC_INFO("LayerExample attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();
    }

    void LayerExample::OnFrameAwake()
    {
        AIAC_INFO("LayerExample OnFrameAwake");
    }

    void LayerExample::OnFrameStart()
    {
        AIAC_INFO("LayerExample frame start");
    }

    void LayerExample::OnFrameEnd()
    {
        AIAC_INFO("LayerExample frame end");
    }

    void LayerExample::OnUIRender()
    {
    }

    void LayerExample::OnFrameFall()
    {
        AIAC_INFO("LayerExample is fall");
    }

    void LayerExample::OnDetach()
    {
        AIAC_INFO("LayerExample detached");
    }
}