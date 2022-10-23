//
// Created by tpp on 26.08.22.
//

#include <map>
#include <iostream>
#include <utility>

#include "TextRenderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "AIAC/Log.h"

namespace AIAC{

    TextRenderer* TextRenderer::s_instance = nullptr;
    bool TextRenderer::s_Initialized;
    GLuint TextRenderer::s_ShaderProgram;
    GLuint TextRenderer::s_VAO, TextRenderer::s_VBO;
    std::map<char, Character> TextRenderer::Characters;

    void TextRenderer::Init() {
        s_instance = new TextRenderer();

        glGenVertexArrays(1, &s_VAO);

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
            s_instance->Characters.insert(std::pair<char, Character>(c, character));
        }

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        s_instance->s_ShaderProgram = LoadShaders(
                "assets/opengl/TextShader.vs",
                "assets/opengl/TextShader.fs");

        glGenBuffers(1, &(s_instance->s_VBO));
        s_instance->s_Initialized = true;

    }

    void TextRenderer::RenderTextOnScreen(std::string text, float x, float y, float w, float h, glm::vec4 color, float scale){
        RenderText(std::move(text), glm::vec3(x, y, 0), w, h, color, scale);
    }

    void TextRenderer::RenderText(std::string text, glm::vec3 position, float w, float h, glm::vec4 color, float scale)
    {
        if(!s_Initialized){
            throw std::runtime_error("Try to render text before init.");
        }

        GLint prevProgram;
        glGetIntegerv(GL_PROGRAM, &prevProgram);
        glUseProgram(s_ShaderProgram);
        glUniform4f(glGetUniformLocation(s_ShaderProgram, "textColor"), color.r, color.g, color.b, color.a);
        glm::mat4 orthoProjection = glm::ortho(0.0f, w, 0.0f, h);
        glUniformMatrix4fv(glGetUniformLocation(s_ShaderProgram, "projection"), 1, GL_FALSE, &orthoProjection[0][0]);

        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(s_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // iterate through all characters
        std::string::const_iterator c;
//        glm::vec4 positionOnScreen = projection * glm::vec4(position, 1.0f);
//        float x = positionOnScreen.x;
//        float y = positionOnScreen.y;
        float x = position.x;
        float y = position.y;

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
            glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
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
    }
}

