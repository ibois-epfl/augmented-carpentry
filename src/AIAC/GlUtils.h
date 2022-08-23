#pragma  once

#include <vector>

#include "GlHeader.h"

#include "tslam.h"

#include "glm/glm.hpp"

namespace AIAC {
    const static glm::vec4 BLACK   = glm::vec4(0, 0, 0, 1);
    const static glm::vec4 RED     = glm::vec4(1, 0, 0, 1);
    const static glm::vec4 GREEN   = glm::vec4(0, 1, 0, 1);
    const static glm::vec4 BLUE    = glm::vec4(0, 0, 1, 1);
    const static glm::vec4 YELLOW  = glm::vec4(1, 1, 0, 1);
    const static glm::vec4 MAGENTA = glm::vec4(1, 0, 1, 1);
    const static glm::vec4 CYAN    = glm::vec4(0, 1, 1, 1);
    const static glm::vec4 WHITE   = glm::vec4(1, 1, 1, 1);

    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize);
    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize);

    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);

    extern void DrawSlamMap(const std::shared_ptr<tslam::Map> &map, const glm::vec4 &color);
}