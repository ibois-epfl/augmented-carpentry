#include "AIAC/LayerUI.h"
#include "AIAC/Log.h"
#include "AIAC/Image.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <iostream>



namespace AIAC
{
    inline static void glfwErrorCallback(int error, const char* description) {
    AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }




   static GLuint textureID;

   void LayerUI::OnAttach()
   {
        // LoadImgFromFile("/home/as/augmented-carpentry/icons/logo_linux_gray_light.png", textureID, GL_RGBA);
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
    }
}