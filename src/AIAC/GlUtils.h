#pragma  once

#include "GlHeader.h"
#include "glm/glm.hpp"
#include <vector>

namespace AIAC {
    extern void DrawPoint3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize);
    extern void DrawPoint3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize);

    extern void DrawLine3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
    extern void DrawLine3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

    extern void DrawTriangle3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
    extern void DrawTriangle3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);
}