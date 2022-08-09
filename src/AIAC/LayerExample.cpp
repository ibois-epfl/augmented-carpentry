#include "AIAC/LayerExample.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace AIAC
{
    void ExampleLayer::OnAttach()
    {
        AIAC_INFO("ExampleLayer attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();
    }

    void ExampleLayer::OnFrameAwake()
    {
        AIAC_INFO("ExampleLayer OnFrameAwake");
    }

    void ExampleLayer::OnFrameStart()
    {
        AIAC_INFO("ExampleLayer frame start");
    }

    void ExampleLayer::OnFrameEnd()
    {
        AIAC_INFO("ExampleLayer frame end");
    }

    void ExampleLayer::OnUIRender()
    {
        ImGui::Begin("Hello ExampleLayer");
        ImGui::Button("Button ExampleLayer");
        ImGui::Text("This is my UI stuff for the ExampleLayer");
        ImGui::End();
    }

    void ExampleLayer::OnFrameFall()
    {
        AIAC_INFO("ExampleLayer is fall");
    }

    void ExampleLayer::OnDetach()
    {
        AIAC_INFO("ExampleLayer detached");
    }
}