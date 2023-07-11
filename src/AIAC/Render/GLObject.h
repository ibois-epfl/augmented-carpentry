
#pragma once

#include <vector>
#include "AIAC/GlHeader.h"
#include "glm/glm.hpp"

namespace AIAC {
    enum class GLObjectType {
        POINTS,
        LINES,
        TRIANGLES
    };

    class GLObject {
    public:
        GLObjectType type;
        GLuint vertexBuf;
        GLuint colorBuf;
        GLsizei size; // how many objects to Draw (for glDrawArrays)

        GLObject() = default;
        ~GLObject() {};

        // copy constructor
        GLObject(const GLObject &other) {
            type = other.type;
            vertexBuf = other.vertexBuf;
            colorBuf = other.colorBuf;
            size = other.size;
        }

        GLObject& operator=(const GLObject &other) {
            type = other.type;
            vertexBuf = other.vertexBuf;
            colorBuf = other.colorBuf;
            size = other.size;
            return *this;
        }

        virtual void Draw() = 0;

        // must be called if data is already buffered
        // I didn't do this inside deconstructor because there might be multiple <GLObject> instances holding the same VBOs
        // For example, when operator= or copy operator is called, it shouldn't do this delete
        void DeleteVBOs();

    protected:
        void BindVBOs();
        void BufferData(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors);
    };

    // ----------------- //
    //   GLPointObject   //
    // ----------------- //
    class GLPointObject : public GLObject {
    public:
        GLPointObject() { type = GLObjectType::POINTS; }

        GLPointObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize = 1.0f);
        
        // copy constructor
        GLPointObject(const GLPointObject &other) : GLObject(other) {
            pointSize = other.pointSize;
        }

        GLPointObject& operator=(const GLPointObject &other) {
            GLObject::operator=(other);
            pointSize = other.pointSize;
            return *this;
        }

        virtual void Draw();

    public:
        GLfloat pointSize;
    };

    // ----------------- //
    //   GLLineObject   //
    // ----------------- //
    class GLLineObject : public GLObject {
    public:
        GLLineObject() { type = GLObjectType::LINES; }

        GLLineObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat lineWidth = 1.0f);
        
        // copy constructor
        GLLineObject(const GLLineObject &other) : GLObject(other) {
            lineWidth = other.lineWidth;
        }

        GLLineObject& operator=(const GLLineObject &other) {
            GLObject::operator=(other);
            lineWidth = other.lineWidth;
            return *this;
        }

        virtual void Draw();

    public:
        GLfloat lineWidth;
    };

    // -------------------- //
    //   GLMeshObject   //
    // -------------------- //
    class GLMeshObject : public GLObject {
    public:
        GLMeshObject() { type = GLObjectType::TRIANGLES; }

        GLMeshObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, const std::vector<uint32_t> &indices);
        
        // copy constructor
        GLMeshObject(const GLMeshObject &other) : GLObject(other) {
            indexBuf = other.indexBuf;
            m_Vertices = other.m_Vertices;
            m_Colors = other.m_Colors;
            m_Indices = other.m_Indices;
        }

        GLMeshObject& operator=(const GLMeshObject &other) {
            GLObject::operator=(other);
            indexBuf = other.indexBuf;
            m_Vertices = other.m_Vertices;
            m_Colors = other.m_Colors;
            m_Indices = other.m_Indices;
            return *this;
        }

        virtual void Draw();

    public:
        GLuint indexBuf;
        std::vector<glm::vec3> m_Vertices;
        std::vector<glm::vec4> m_Colors;
        std::vector<uint32_t> m_Indices;
    };

    // --------------------- //
    //   Auxilary function   //
    // --------------------- //
    /**
     * @brief Combine 3 points into a glm::vec3 and transform it based on the given transformation matrix.
     * @param transformMat A 4x4 transformation matrix.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     */
    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z);

    std::vector< std::shared_ptr<GLObject> > CreateCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum=-1);
    std::vector< std::shared_ptr<GLObject> > CreateCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum = -1);
    std::vector< std::shared_ptr<GLObject> > CreatePolyline(std::vector<glm::vec3> vertices, bool isClosed, glm::vec4 color, float lineWidth);
}