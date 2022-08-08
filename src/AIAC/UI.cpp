
#include "AIAC/UI.hpp"


namespace AIAC::UI
{
    // void ShowUI(bool* p_open)
    // {
    //     // AIAC_CLI_INFO("Showing UI");
    //     ImGui::Begin("Hello, world!", p_open);
    //     ImGui::Button("Hello");
    //     static float value = 0.0f;
    //     ImGui::DragFloat("Value", &value, 0.1f);
    //     ImGui::End();
    //     return ;
    // }
    struct AppUISpecification
    {
        std::string WindowName = "augmented-carpentry";
        uint32_t Width = 1600;
        uint32_t Height = 900;
    };


    void ShowWinARViewport(bool* p_open) 
    {
        return;
    }

    void ShowWinPanel(bool* p_open)
    {
        return;
    }

    void ShowWin3DViewport(bool* p_open)
    {
        return;
    }
}
