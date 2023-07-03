#include "GLObject.h"
using namespace std;
namespace AIAC
{
    // GLObject
    void GLObject::BindVBOs(){
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (GLvoid *) 0        // array buffer offset
        );

        glBindBuffer(GL_ARRAY_BUFFER, colorBuf);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (GLvoid *) 0        // array buffer offset
        );
    }

    void GLObject::BufferData(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors) {
        glGenBuffers(1, &this->vertexBuf);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->colorBuf);
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);
    }

    // ----------------- //
    //   GLPointObject   //
    // ----------------- //
    GLPointObject::GLPointObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize) {
        this->type = GLObjectType::POINTS;
        this->size = vertices.size();
        this->pointSize = pointSize;
        
        GLObject::BufferData(vertices, colors);
    }
    
    void GLPointObject::Draw()
    {
        BindVBOs();
        GLfloat prevPointSize;
        glGetFloatv(GL_POINT_SIZE, &prevPointSize);
        glPointSize(pointSize);
        glDrawArrays(GL_POINTS, 0, pointSize);
        glPointSize(prevPointSize);
    }

    // ----------------- //
    //   GLLineObject   //
    // ----------------- //
    GLLineObject::GLLineObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat lineWidth) {
        this->type = GLObjectType::LINES;
        this->size = vertices.size();
        this->lineWidth = lineWidth;

        GLObject::BufferData(vertices, colors);
    }

    void GLLineObject::Draw()
    {
        BindVBOs();
        GLfloat prevLineWidth;
        glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
        glLineWidth(lineWidth);
        glDrawArrays(GL_LINES, 0, size);
        glLineWidth(prevLineWidth);
    }

    // -------------------- //
    //   GLTriangleObject   //
    // -------------------- //
    GLTriangleObject::GLTriangleObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, const std::vector<uint32_t> &indices) {
        this->type = GLObjectType::TRIANGLES;
        this->size = indices.size();

        GLObject::BufferData(vertices, colors);

        glGenBuffers(1, &this->indexBuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
    }

    void GLTriangleObject::Draw()
    {
        BindVBOs();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    }


} // namespace AIAC