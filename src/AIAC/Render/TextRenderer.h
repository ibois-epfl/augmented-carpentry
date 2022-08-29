#pragma once
#include "AIAC/GlHeader.h"

#include "Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace AIAC
{
    class TextRenderer {
    public:
        TextRenderer() = default;
        ~TextRenderer() = default;

        void Init();

        bool IsInitialized() const { return m_Initialized; }

        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4 projection);

    public:
        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        std::map<char, Character> Characters;
        unsigned int VAO, VBO;

        GLuint shaderProgram;

    private:
        bool m_Initialized = false;
    };
}