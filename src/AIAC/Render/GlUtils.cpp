#include "aiacpch.h"
#include "GlUtils.h"

namespace AIAC {
    // void glDrawObject(GLObject &glObject) {
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.vertexBuf)
    //     glEnableVertexAttribArray(0);
    //     glVertexAttribPointer(
    //             0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //             3,                  // size
    //             GL_FLOAT,           // type
    //             GL_FALSE,           // normalized?
    //             0,                  // stride
    //             (GLvoid *) 0        // array buffer offset
    //     );

    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.colorBuf);
    //     glEnableVertexAttribArray(1);
    //     glVertexAttribPointer(
    //             1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
    //             4,                  // size
    //             GL_FLOAT,           // type
    //             GL_FALSE,           // normalized?
    //             0,                  // stride
    //             (GLvoid *) 0        // array buffer offset
    //     );
        
    //     switch (glObject.type) {
    //         case GLObjectType::POINTS:
    //             GLfloat prevPointSize;
    //             glGetFloatv(GL_POINT_SIZE, &prevPointSize);
    //             glPointSize(glObject.weight);
    //             glDrawArrays(GL_POINTS, 0, glObject.size);
    //             glPointSize(prevPointSize);
    //             break;
    //         case GLObjectType::LINES:
    //             glDrawArrays(GL_LINES, 0, glObject.size);
    //             break;
    //         case GLObjectType::TRIANGLES:
    //             glDrawArrays(GL_TRIANGLES, 0, glObject.size);
    //             break;
    //     }
    // }

    // void glRemoveObject(GLObject &glObject) {
    //     glDeleteBuffers(1, &glObject.vertexBuf);
    //     glDeleteBuffers(1, &glObject.colorBuf);
    // }

    // // Creator for points
    // GLObject glAddPoints(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize) {
    //     GLObject glObject;
    //     glObject.type = GLObjectType::POINTS;
    //     glObject.size = vertices.size();
    //     glObject.weight = pointSize;

    //     glGenBuffers(1, &glObject.vertexBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.vertexBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    //     glGenBuffers(1, &glObject.colorBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.colorBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

    //     return glObject;
    // }

    // // Creator for lines
    // GLObject glAddLines(const std::vector<glm::vec3> &endPts, const std::vector<glm::vec4> &colors, GLfloat weight) {
    //     GLObject glObject;
    //     glObject.type = GLObjectType::LINES;
    //     glObject.size = endPts.size() / 2;
    //     glObject.weight = weight;

    //     glGenBuffers(1, &glObject.vertexBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.vertexBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(endPts) * sizeof(glm::vec3), &endPts[0], GL_STATIC_DRAW);

    //     glGenBuffers(1, &glObject.colorBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.colorBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

    //     return glObject;
    // }

    // // Creator for triangles
    // GLObject glAddTriangles(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat weight) {
    //     GLObject glObject;
    //     glObject.type = GLObjectType::TRIANGLES;
    //     glObject.size = vertices.size() / 3;
    //     glObject.weight = weight;

    //     glGenBuffers(1, &glObject.vertexBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.vertexBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    //     glGenBuffers(1, &glObject.colorBuf);
    //     glBindBuffer(GL_ARRAY_BUFFER, glObject.colorBuf);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

    //     return glObject;
    // }

    

    void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize) {
        // GLuint vbo;
        // glGenBuffers(1, &vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(
        //         0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        //         3,                  // size
        //         GL_FLOAT,           // type
        //         GL_FALSE,           // normalized?
        //         0,                  // stride
        //         (void *) nullptr     // array buffer offset
        // );

        // GLuint colorBuffer;
        // glGenBuffers(1, &colorBuffer);
        // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        // glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(
        //         1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
        //         4,                  // size
        //         GL_FLOAT,           // type
        //         GL_FALSE,           // normalized?
        //         0,                  // stride
        //         (void *) nullptr     // array buffer offset
        // );

        // GLfloat prevPointSize;
        // glGetFloatv(GL_POINT_SIZE, &prevPointSize);
        // glPointSize(pointSize);

        // glDrawArrays(GL_POINTS, 0, (GLsizei) vertices.size());

        // glPointSize(prevPointSize);
        // // glDisableVertexAttribArray(0);
        // // glDisableVertexAttribArray(1);
        // // glDeleteBuffers(1, &vbo);
        // // glDeleteBuffers(1, &colorBuffer);
    }

    void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize) {
        // std::vector<glm::vec4> colors(vertices.size(), color);
        // glDrawPoints3d(vertices, std::move(colors), pointSize);
    }

    void glDrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors) {
        // GLuint vbo;
        // glGenBuffers(1, &vbo);
    
        // // show current vao
        // // GLint vao;
        // // glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
        // // cout << "vbo: " << vbo << " vao: " << vao << endl;
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(glm::vec3), &edges[0], GL_STATIC_DRAW);
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(
        //         0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        //         3,                  // size
        //         GL_FLOAT,           // type
        //         GL_FALSE,           // normalized?
        //         0,                  // stride
        //         (void *) nullptr     // array buffer offset
        // );

        // GLuint colorBuffer;
        // glGenBuffers(1, &colorBuffer);
        // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        // glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(
        //         1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
        //         4,                  // size
        //         GL_FLOAT,           // type
        //         GL_FALSE,           // normalized?
        //         0,                  // stride
        //         (void *) nullptr     // array buffer offset
        // );

        // glDrawArrays(GL_LINES, 0, (GLsizei) edges.size() / 2);

        // // glDisableVertexAttribArray(0);
        // // glDisableVertexAttribArray(1);
        // // glDeleteBuffers(1, &vbo);
        // // glDeleteBuffers(1, &colorBuffer);
    }

    void glDrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color) {
        // std::vector<glm::vec4> colors(edges.size(), color);
        // glDrawLines3d(edges, colors);
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

        // // glDisableVertexAttribArray(0);
        // // glDisableVertexAttribArray(1);
        // // glDeleteBuffers(1, &elementBuffer);
        // // glDeleteBuffers(1, &vbo);
        // // glDeleteBuffers(1, &colorBuffer);

    }
    void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &color){
        // std::vector<glm::vec4> colors(vertices.size(), color);
        // glDrawTriangles3d(vertices, indices, colors);
    }
}