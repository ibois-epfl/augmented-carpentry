#include "aiacpch.h"
#include "GlUtils.h"

namespace AIAC {
    void DrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize) {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        GLfloat prevPointSize;
        glGetFloatv(GL_POINT_SIZE, &prevPointSize);
        glPointSize(pointSize);

        glDrawArrays(GL_POINTS, 0, (GLsizei) vertices.size());

        glPointSize(prevPointSize);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &colorBuffer);
    }

    void DrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize) {
        std::vector<glm::vec4> colors(vertices.size(), color);
        DrawPoints3d(vertices, std::move(colors), pointSize);
    }

    void DrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors) {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(glm::vec3), &edges[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        glDrawArrays(GL_LINES, 0, (GLsizei) edges.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &colorBuffer);
    }

    void DrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color) {
        std::vector<glm::vec4> colors(edges.size(), color);
        DrawLines3d(edges, colors);
    }

    void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors){
        GLuint elementBuffer;
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr     // array buffer offset
        );

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDeleteBuffers(1, &elementBuffer);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &colorBuffer);

    }
    void DrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &color){
        std::vector<glm::vec4> colors(vertices.size(), color);
        DrawTriangles3d(vertices, indices, colors);
    }

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize) {
        std::vector<glm::vec3> mapPoints(map->map_points.size());
        for(const auto& mapPoint: map->map_points){
            if(mapPoint.isValid()){
                mapPoints.emplace_back(mapPoint.getCoordinates().x, mapPoint.getCoordinates().y, mapPoint.getCoordinates().z);
            }
        }
        DrawPoints3d(mapPoints, OGL_YELLOW, pointSize);

        std::vector<glm::vec3> markerEdges(map->map_markers.size() * 4 * 2);
        std::vector<glm::vec4> markerEdgeColors(map->map_markers.size() * 4 * 2, OGL_BLUE);
        for(const auto& mapMarker: map->map_markers){
            auto points = mapMarker.second.get3DPoints();
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);
            for(int i = 1 ; i < 4; i++){
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
            }
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);

            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);

        }

        DrawLines3d(markerEdges, markerEdgeColors);
    }
}