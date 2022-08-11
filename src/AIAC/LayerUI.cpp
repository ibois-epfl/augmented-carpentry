#include "AIAC/LayerUI.h"
#include "AIAC/Log.h"
#include "AIAC/Image.h"
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

        ImGui_ImplGlfw_InitForOpenGL(AIAC_APP().GetWindow(), true);
        ImGui_ImplOpenGL3_Init(AIAC_APP().GetGlslVersion());

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 16.0f);  //FIXME: add to config
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
        ImGui::Begin("Test window");

        ImGui::Text("This is a test image");


        AIAC::ImTexture imTexture = {};
        // LoadImgFromFile2GlTextureID("/home/as/augmented-carpentry/icons/logo_linux_gray_light.png", textureID, GL_RGBA);
        
        AIAC::Image logo = AIAC::Image("/home/as/augmented-carpentry/icons/logo_linux_gray_light.png", AIAC::ImageType::IM_TEXTURE);



        // AIAC::Image currentFrame = AIAC::Application::GetInstance().GetLayer<AIAC::LayerCamera>()->GetCurrentFrame();
        // cv::Mat cvMat = currentFrame.GetCvMat();

        // CvtCvMat2GlTextureID(cvMat, textureID);
        // CvtGlTextureID2ImTexture(textureID, imTexture);




        // imTexture.Size = ImVec2(100, 100);
        ImGui::Image(logo.GetImTexture().ID, logo.GetImTexture().Size, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

        // ImGui::Image(imTexture.ID, imTexture.Size, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));


        ImGui::Begin("Test window");

        ImGui::Text("This is a test image");



        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void LayerUI::OnFrameEnd()
    {
        
    }

    void LayerUI::OnFrameFall()
    {
        
    }

    void LayerUI::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}