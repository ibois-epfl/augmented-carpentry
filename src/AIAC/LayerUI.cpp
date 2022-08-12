#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <iostream>

namespace AIAC
{

    void LayerUI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsLight();
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);

        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;

        ImGui_ImplGlfw_InitForOpenGL(AIAC_APP().GetWindow(), true);
        ImGui_ImplOpenGL3_Init(AIAC_APP().GetGlslVersion());

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 16.0f);  //FIXME: add to config

        m_IsOpen = new bool(true);

        m_Logo = AIAC::Image("assets/images/logo_linux_gray_light.png", AIAC::ImageType::IM_TEXTURE, ImVec2(60, 60));

        

        //                 Label    Collapse          PaneContent
        StackPane(PaneUI("Example",   true,   std::bind(&SetPaneUIExample)   ));
        StackPane(PaneUI("Camera",    true,   std::bind(&SetPaneUICamera)    ));
        StackPane(PaneUI("Slam",      true,   std::bind(&SetPaneUISlam)      ));
    }

    void LayerUI::OnFrameStart()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void LayerUI::OnUIRender()
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
        // Main Pannel
        ImGui::Begin("augmented_carpentry", m_IsOpen);

        ShowIntroUI();

        for (auto& pane : m_PaneUIStack) pane->Show();

        ImGui::End();

        // 3D Scene Viewport
        ImGui::Begin("scene_viewport", m_IsOpen);

        Image frame =
            AIAC_APP().GetLayer<AIAC::LayerCamera>()
                ->MainCamera.GetCurrentFrame();
        frame.CvtCvMat2ImTexture();
        AIAC::ImTexture frameImTexture = frame.GetImTexture();
        // AIAC::ImTexture frameImTexture = frame.GetImTexture();

        AIAC_INFO("frameImTexture width = {0}", frameImTexture.Size.x);
        AIAC_INFO("frameImTexture height = {0}", frameImTexture.Size.y);

        ImGui::Image(frameImTexture.ID, frameImTexture.Size);

        // frame.CvtCvMat2ImTexture(frame.GetCvMat(), imTexture);

        // ImGui::Image(AIAC_APP().GetLayer<AIAC::LayerCamera>()->GetCurrentFrame().GetImTexture().ID,
        //              AIAC_APP().GetLayer<AIAC::LayerCamera>()->GetCurrentFrame().GetImTexture().Size);


        // ImGui::BeginChild("3DSceneViewport", ImVec2(0, 0), true);
        // ImGui::EndChild();

        ImGui::End();



        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void LayerUI::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }


    void LayerUI::ShowIntroUI()
    {
        ImGui::Image(m_Logo.GetImTexture().ID, m_Logo.GetImTexture().Size, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        ImGui::SameLine();
        ImGui::Text("This is a prototype for augmented_carpentry \n Version 01.00.00 \n Build 2021-01-01 00:00:00 \n IBOIS, EPFL");
    }


    void LayerUI::SetPaneUIExample()
    {
        ImGui::Text("This is a test message for the example layer");
    }

    void LayerUI::SetPaneUICamera()
    {
        ImGui::Text("This layer is responsible for the physical camera.");
        AIAC::Camera& camera = AIAC_APP().GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Camera is %s", camera.IsOpened() ? "open" : "closed");
        ImGui::Text("Camera resolution: %d x %d", camera.GetWidth(), camera.GetHeight());
    }

    void LayerUI::SetPaneUISlam()
    {
        //TODO: fill with debug info for SLAM
    }

}