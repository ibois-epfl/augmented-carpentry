#pragma once
#include "AIAC/GlHeader.h"

#include "Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace AIAC
{
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    class TextRenderer {

    public:
        TextRenderer() = default;
        ~TextRenderer() = default;

        // The interface of the static TextRenderer
        // The static variable TextRendererInterface is initialized in Renderer.cpp:Init()
        static void Init(GLuint VAO);
        static void RenderTextOnScreen(std::string text, float x, float y, glm::vec4 color, float scale=1.0f);

        inline static TextRenderer& GetInstance() { return *s_instance; }

    public:
        static std::map<char, Character> Characters;

    private:
        static bool s_Initialized;
        static GLuint s_ShaderProgram;
        static GLuint s_VAO, s_VBO;
        static TextRenderer* s_instance;
    };
}