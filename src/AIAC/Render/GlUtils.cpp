#include "aiacpch.h"
#include "GlUtils.h"

namespace AIAC {
    void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize) {
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

    void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize) {
        std::vector<glm::vec4> colors(vertices.size(), color);
        glDrawPoints3d(vertices, std::move(colors), pointSize);
    }

    void glDrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors) {
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

    void glDrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color) {
        std::vector<glm::vec4> colors(edges.size(), color);
        glDrawLines3d(edges, colors);
    }

    void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors){
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
    void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &color){
        std::vector<glm::vec4> colors(vertices.size(), color);
        glDrawTriangles3d(vertices, indices, colors);
    }
    glm::vec2 GetProjectAxisOnScreen(const glm::vec3 position, const glm::mat4 cameraMat, const glm::mat4 projectionMat, const int h, const int w){
        auto coordCameraView = cameraMat * glm::vec4(position, 1.0f);
        auto coordFinalView = projectionMat * coordCameraView;
        coordFinalView.w = -coordCameraView.z;
        if (coordFinalView.w != 0){
            coordFinalView.w = 1.0 / coordFinalView.w;
            coordFinalView.x *= coordFinalView.w;
            coordFinalView.y *= coordFinalView.w;
            coordFinalView.z *= coordFinalView.w;
        }
        // TODO: times w and h and return the vector
    }
}