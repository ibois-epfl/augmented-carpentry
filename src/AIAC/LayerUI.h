#pragma once

#include "AIAC/Layer.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace AIAC
{
    struct ImTexture
        {
            ImTextureID ID;
            ImVec2 Size;
        };

    class LayerUI : public AIAC::Layer
    {
    public:
        LayerUI() = default;
        virtual ~LayerUI() = default;

        virtual void OnAttach() override;
        virtual void OnUIRender() override;
        // virtual void OnDetach() override;

    private:
        bool LoadImgFromFile(const char* path, GLuint& glTextureID, int32_t img_mod);

        void CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture);
        void CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size);



    };
}