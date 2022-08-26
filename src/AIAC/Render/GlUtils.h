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

    /**
     * @brief Draw multiple points
     * @param vertices A vector of 3d points, indicate the position of the vertices.
     * @param colors A RGBA(0~1.0) color, a vector with the same size of the `vertices`.
     * @param pointSize The size of the point.
     * */
    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize=1.0f);
    /**
     * @brief Draw multiple points
     * @param vertices A vector of 3d points, indicate the position of the vertices.
     * @param colors A RGBA(0~1.0) color.
     * @param pointSize The size of the point.
     * */
    extern void DrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize=1.0f);

    /**
     * Draw multiple lines
     *
     * (0, 1, 0) --- (1, 0, 0)
     *     |             |
     *     |             |
     *     |             |
     * (0, 0, 0) --- (0, 0, 1)
     *
     * If you want to draw a square like this, you should construct the `edges` as:
     * [
     *    (0, 0, 0), (0, 0, 1),
     *    (0, 0, 1), (1, 0, 0),
     *    (1, 0, 0), (0, 1, 0),
     *    (0, 1, 0), (0, 0, 0)
     * ]
     *
     * @brief Draw multiple points
     * @param vertices A vector of 3d points, indicate the position of the vertices.
     * @param colors A RGBA(0~1.0) color, a vector with the same size of the `vertices`.
     * */
    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
    /**
    * @brief Draw multiple points
    * @param vertices A vector of 3d points, indicate the position of the vertices.
    * @param colors A RGBA(0~1.0) color.
    * */
    extern void DrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

    /**
     * P2(0, 1, 0) --- P3(1, 0, 0)
     *     |            /    |
     *     |          /      |
     *     |        /        |
     *     |      /          |
     *     |    /            |
     * P0(0, 0, 0) --- P1(0, 0, 1)
     *
     * If you want to draw a mesh of square like this, you should construct the `edges` as:
     * [
     *    (0, 0, 0), // P0
     *    (0, 0, 1), // P1
     *    (1, 0, 0), // P2
     *    (0, 1, 0), // P3
     * ]
     * with `indices`:
     * [
     *     0, 1, 3, // Right-bottom triangle
     *     3, 2, 0  // Left-top triangle
     * ]
     *
     * @brief Draw multiple Triangles
     * @param vertices A vector of 3d points, indicate the position of the vertices.
     * @param indices A vector of all triangle's indices.
     * @param colors: A RGBA(0~1.0) color, a vector with the same size of the vertices.
     * */
    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
    /**
     * @brief Draw multiple Triangles
     * @param vertices A vector of 3d points, indicate the position of the vertices.
     * @param indices A vector of all triangle's indices.
     * @param colors: A RGBA(0~1.0) color, a vector with the same size of the vertices.
     * */
    extern void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);

    /**
     * @brief Draw TSlam map
     * @param map A TSlam map
     * @param color The color of the point cloud
     * */
    extern void DrawSlamMap(const std::shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize=1);
}