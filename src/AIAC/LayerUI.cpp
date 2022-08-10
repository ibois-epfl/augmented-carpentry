#include "AIAC/LayerUI.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include <GL/gl.h>
// #include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

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

   void LayerUI::OnAttach()
   {
         AIAC_INFO("LayerUI attached");
        // load image from memory
        // create new GL texture
        // bind texture
        // set texture parameters
        // upload image data to texture
        // unbind texture

        GLuint texture;

        int width, height, nrChannels;
        unsigned char* image = stbi_load("icons/logo_linux_gray_light.png.png", &width, &height, &nrChannels, 0);
        if (image)
        {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(image);

        // Show image on background



        // ImTextureID my_tex_id = (void*)(intptr_t)texture;
        // ImVec2 my_tex_sz = ImVec2(16, 16);
        // ImGui::Image(my_tex_id, my_tex_sz, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

        // // Show imag


   }


    void LayerUI::OnUIRender()
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
        
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::ShowDemoWindow();
        ImGui::End();

    }

}