#include "AIAC/LayerUI.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <iostream>

#include <opencv2/opencv.hpp>


namespace AIAC
{
    inline static void glfwErrorCallback(int error, const char* description) {
    AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }


    bool LayerUI::LoadImgFromFile2GlTextureID(const char* path, GLuint& glTextureID, int32_t img_mod) 
    {
        if (FILE *file = fopen(path, "r")) {
            fclose(file);
            AIAC_INFO("File exists");
        } else {
            AIAC_ERROR("File does not exist");
            AIAC_BREAK();
        }

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);  // OpenGL flip images
        unsigned char* image = stbi_load(path, &width, &height, &nrChannels, 0);
        if (image)
        {
            glGenTextures(1, &glTextureID);
            glBindTexture(GL_TEXTURE_2D, glTextureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            AIAC_ERROR("Failed to load img from file");
            return false;
        }
        stbi_image_free(image);
        return true;
    }

    void LayerUI::CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture)
    {
        int w, h;
        glBindTexture(GL_TEXTURE_2D, glTextureID);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
        
        imTexture.ID = (void*)(intptr_t)glTextureID;
        imTexture.Size = ImVec2(w, h);
    }
    void LayerUI::CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size)
    {
        imTexture.ID = (void*)(intptr_t)glTextureID;
        imTexture.Size = size;
    }
    void LayerUI::CvtCvMat2GlTextureID(cv::Mat& cvMat, GLuint& glTextureID)
    {
        if(cvMat.empty()) { AIAC_ERROR("cvMat empty"); AIAC_BREAK(); }
        else
        {
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glGenTextures(1, &glTextureID);
            glBindTexture(GL_TEXTURE_2D, glTextureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            cv::cvtColor(cvMat, cvMat, cv::COLOR_RGB2BGR);

            glTexImage2D(GL_TEXTURE_2D,
                        0,
                        GL_RGB,
                        cvMat.cols,
                        cvMat.rows,
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        cvMat.ptr());
        }
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


        ImTexture imTexture = {};
        LoadImgFromFile2GlTextureID("/home/as/augmented-carpentry/icons/logo_linux_gray_light.png", textureID, GL_RGBA);
        
        // AIAC::Application::Get().GetLayerCamera()->



        CvtGlTextureID2ImTexture(textureID, imTexture);
        imTexture.Size = ImVec2(100, 100);
        ImGui::Image(imTexture.ID, imTexture.Size, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));


        ImGui::Begin("Test window");

        ImGui::Text("This is a test image");



        ImGui::End();
    }
}