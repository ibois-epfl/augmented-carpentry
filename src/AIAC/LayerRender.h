#pragma once

#include "glm/glm.hpp"

#include "AIAC/Mesh.h"
#include "AIAC/GlHeader.h"
#include "AIAC/Layer.h"


namespace AIAC
{
    class LayerRender : public AIAC::Layer
    {
    public:
        LayerRender() = default;
        virtual ~LayerRender() = default;

        void OnAttach() override;
        virtual void OnUIRender() override;
        virtual void OnFrameEnd() override;

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