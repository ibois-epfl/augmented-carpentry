//
// Created by tpp on 26.08.22.
//

#include <map>
#include <iostream>

#include "TextRenderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "AIAC/Log.h"

namespace AIAC{

    void TextRenderer::Init(GLuint VAO) {
        m_VAO = VAO;
        // Load FreeType
        // --------
        // All functions return a value different from 0 whenever an error occurred
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            throw(std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library"));
        }

        // find path to font
        std::string font_name = "assets/fonts/Antonio-Bold.ttf";
        if (font_name.empty()) {
            std::cerr << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
            throw(std::runtime_error("ERROR::FREETYPE: Failed to load font_name"));
        }

        // load font as face
        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
            std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
            throw(std::runtime_error("ERROR::FREETYPE: Failed to load font"));
        }

        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++) {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_ShaderProgram = LoadShaders(
                "assets/opengl/TextShader.vs",
                "assets/opengl/TextShader.fs");

        glGenBuffers(1, &m_VBO);
        m_Initialized = true;
    }

    /**
     * @brief Render text
     * @param text Text to show
     * @param x X-axis, (0, 0) is the left-bottom corner
     * @param y Y-axis, (0, 0) is the left-bottom corner
     * @param color Text color
     * @param projection Currently unused
     */
    void TextRenderer::RenderTextOnScreen(std::string text, float x, float y, float scale, glm::vec4 color, glm::mat4 projection)
    {
        glm::mat4 orthoProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

        GLint prevProgram;
        glGetIntegerv(GL_PROGRAM, &prevProgram);
        glUseProgram(m_ShaderProgram);
        glUniform4f(glGetUniformLocation(m_ShaderProgram, "textColor"), color.r, color.g, color.b, color.a);
        glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "projection"), 1, GL_FALSE, &orthoProjection[0][0]);

        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }

        // restore previous state
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(prevProgram);

        return;
    }
}

