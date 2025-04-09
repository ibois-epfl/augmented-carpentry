

# File TextRenderer.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Render**](dir_4231f99b70cbd7a69a19f070b3954fcb.md) **>** [**TextRenderer.h**](TextRenderer_8h.md)

[Go to the documentation of this file](TextRenderer_8h.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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

        static void Init();

        static inline void SetProjection(glm::mat4 projection) { s_Projection = projection; }

        static void RenderTextIn3DSpace(std::string text, glm::vec3 position, glm::vec4 color, float scale=1.0f);

    private:
        static void RenderText(std::string text, float x, float y, glm::vec4 color, float scale=1.0f);

    public:
        static std::map<char, Character> Characters;

    private:
        static bool s_Initialized;
        static GLuint s_ShaderProgram;
        static GLuint s_VBO;
        static TextRenderer* s_instance;
        static glm::mat4 s_Projection;
    };
}
```


