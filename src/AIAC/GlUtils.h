#pragma  once

#include "GlHeader.h"
#include "glm/glm.hpp"
#include <vector>

namespace AIAC {
    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize);
    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize);

    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);
}