#pragma once

#include "glm/glm.hpp"
#include "AIAC/GlHeader.h"

namespace AIAC{
    class Viewport {
    public:
        Viewport() = default;
        ~Viewport() = default;

        void Init(int w, int h);
        void Activate();
        GLuint GetTexture() const { return m_Texture; };
        void SetSize(int w, int h) { m_W = w; m_H = h; };

        GLuint GetW() const { return m_W; };
        GLuint GetH() const { return m_H; };

    protected:
        GLuint m_FrameBuffer;
        GLuint m_Texture;
        GLuint m_DepthBuffer;
        GLuint m_W;
        GLuint m_H;
    };
}