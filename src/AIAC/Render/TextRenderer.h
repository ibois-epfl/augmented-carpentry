#pragma once
#include "AIAC/GlHeader.h"

#include "Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace AIAC
{
    // Character stores a character's texture and property
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    // Since a TextRenderer has to hold the information of the font (i.e. a list of "struct Character"),
    // it is wrapped into a class that exporting a static global instance.
    // The initialization `Init(G)` has to be called before any rendering happening (now it's in `Renderer.Init()`).
    // When you want to render a text through the TextRenderer directly, use something like:
    // `TextRenderer::GetInstance().RenderTextOnScreen()` to get the static instance and render the text.
    class TextRenderer {

    public:
        TextRenderer() = default;
        ~TextRenderer() = default;

        /**
         * @brief Initialize the static TextRenderer instance
         */
        static void Init();

        /**
         * @brief Render text that is parallel to the screen
         * @param text Text to show
         * @param x X-axis, (0, 0) is the left-bottom corner
         * @param y Y-axis, (0, 0) is the left-bottom corner
         * @param w Width of the Screen
         * @param h Height of the Screen
         * @param color Text color
         * @param scale Text scale, default = 1.0f
         */
        static void RenderTextOnScreen(std::string text, float x, float y, float w, float h, glm::vec4 color, float scale=1.0f);

        /**
         * @brief Render text that is parallel to the screen
         * @param text Text to show
         * @param position Position of the left-bottom corner of the text in the 3D space.
         * @param color Text color
         * @param scale Scale of the text, default = 1.0f
         * @param projection Projection matrix
         */
        static void RenderText(std::string text, glm::vec3 position, float w, float h, glm::vec4 color, float scale=1.0f);

        /**
         * @brief Get the static instance of the TextRenderer
         * @return The global instance of TextRenderer
         */
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