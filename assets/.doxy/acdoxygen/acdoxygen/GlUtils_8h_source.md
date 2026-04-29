

# File GlUtils.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Render**](dir_4231f99b70cbd7a69a19f070b3954fcb.md) **>** [**GlUtils.h**](GlUtils_8h.md)

[Go to the documentation of this file](GlUtils_8h.md)


```C++
#pragma once

#include "AIAC/GlHeader.h"

#include "tslam.h"

#include "glm/glm.hpp"

namespace AIAC {
    const static glm::vec4 OGL_BLACK   = glm::vec4(0, 0, 0, 1);
    const static glm::vec4 OGL_RED     = glm::vec4(1, 0, 0, 1);
    const static glm::vec4 OGL_GREEN   = glm::vec4(0, 1, 0, 1);
    const static glm::vec4 OGL_BLUE    = glm::vec4(0, 0, 1, 1);
    const static glm::vec4 OGL_YELLOW  = glm::vec4(1, 1, 0, 1);
    const static glm::vec4 OGL_MAGENTA = glm::vec4(1, 0, 1, 1);
    const static glm::vec4 OGL_CYAN    = glm::vec4(0, 1, 1, 1);
    const static glm::vec4 OGL_WHITE   = glm::vec4(1, 1, 1, 1);

    
    extern void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize=1.0f);
    extern void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize=1.0f);

    extern void glDrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
    extern void glDrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

    extern void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
    extern void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);

    extern void DrawSlamMap(const std::shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize=1);
}
```


