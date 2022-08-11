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
        m_CurrentFrame = MainCamera.GetNextFrame();
    }
}