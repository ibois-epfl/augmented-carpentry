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

        try
        {
            MainCamera.Open(0);
        }
        catch(const std::runtime_error& e)
        {
            AIAC_ERROR(e.what());
        }
    }

    void LayerCamera::OnFrameStart()
    {
        AIAC_INFO("LayerCamera frame start");
        
        m_CurrentFrame = MainCamera.GetNextFrame();
    }
}