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

#include <opencv2/opencv.hpp>


namespace AIAC
{
    class LayerUI : public AIAC::Layer
    {
    public:
        LayerUI() = default;
        virtual ~LayerUI() = default;

        virtual void OnAttach() override;
        virtual void OnUIRender() override;
        // virtual void OnDetach() override;

    private:
        GLuint* m_CurrentFrameGlTextureID;

    };
}