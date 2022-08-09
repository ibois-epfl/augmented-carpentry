#include "AIAC/LayerExample.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace AIAC
{
    void LayerExample::OnAttach()
    {
        AIAC_INFO("LayerExample attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();

        app.LayerExampleRef = this;  // FIXME: find a way to add to Layer class 
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
        ImGui::Begin("Hello LayerExample");
        ImGui::Button("Button LayerExample");
        ImGui::Text("This is my UI stuff for the LayerExample");
        ImGui::End();
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