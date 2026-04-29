

# File Viewport.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Render**](dir_4231f99b70cbd7a69a19f070b3954fcb.md) **>** [**Viewport.h**](Viewport_8h.md)

[Go to the documentation of this file](Viewport_8h.md)


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
```


