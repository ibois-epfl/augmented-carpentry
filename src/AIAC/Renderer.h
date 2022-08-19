#pragma once

#include "glm/glm.hpp"

#include "AIAC/Mesh.h"
#include "AIAC/GlHeader.h"
#include "AIAC/Layer.h"


namespace AIAC
{
    class Renderer
    {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        void Init();
        void OnRender();
        GLuint GetOverlayBuffer() { return m_OverlayFrameBuffer; }

    public:
        std::vector<AIAC::Mesh> Meshes;

    private:
        float m_CamW, m_CamH;

        GLuint m_ProgramId;
        GLuint m_MatrixId;

        glm::mat4 m_ProjMatrix;

        GLuint m_OverlayFrameBuffer;
    };
}