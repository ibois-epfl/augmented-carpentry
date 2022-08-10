#include "AIAC/LayerCamera.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

namespace AIAC
{
    void LayerCamera::OnAttach()
    {
        AIAC_INFO("LayerCamera attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();
    }

    void LayerCamera::OnFrameAwake()
    {
        AIAC_INFO("LayerCamera OnFrameAwake");
    }

    void LayerCamera::OnFrameStart()
    {
        AIAC_INFO("LayerCamera frame start");
    }

    void LayerCamera::OnFrameEnd()
    {
        AIAC_INFO("LayerCamera frame end");
    }

    void LayerCamera::OnUIRender()
    {
    }

    void LayerCamera::OnFrameFall()
    {
        AIAC_INFO("LayerCamera is fall");
    }

    void LayerCamera::OnDetach()
    {
        AIAC_INFO("LayerCamera detached");
    }
}