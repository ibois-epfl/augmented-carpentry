#include "AIAC/LayerUI.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>


inline static void glfwErrorCallback(int error, const char* description) {
    AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }

namespace AIAC
{
    /*
    UI needs:
    - one pane viewport
    - one pane with Tabs for all layers
    - one pane for 3D scene

    UI todos:
    - get the 
    */


    void LayerUI::OnUIRender()
    {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::ShowDemoWindow();
        ImGui::End();

    }

}