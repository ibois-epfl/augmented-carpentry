#include "GLObject.h"

namespace AIAC
{
    static const float WEIGHT_TO_CYLINDER_RADIUS_RATE = 1.0 / 20.0f;
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

    void GLObject::DeleteVBOs() {
        glDeleteBuffers(1, &vertexBuf);
        glDeleteBuffers(1, &colorBuf);
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
    //     GLMeshObject     //
    // -------------------- //
    GLMeshObject::GLMeshObject(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, const std::vector<uint32_t> &indices) {
        this->type = GLObjectType::TRIANGLES;
        this->size = indices.size();
        
        this->m_Indices = indices;
        this->m_Vertices = vertices;
        this->m_Colors = colors;

        glGenBuffers(1, &this->indexBuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
        GLObject::BufferData(vertices, colors);
    }

    void GLMeshObject::Draw()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuf);
        
        BindVBOs();
        glDrawElements(GL_TRIANGLES, this->m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    // ---------------------- //
    //   Auxilary functions   //
    // ---------------------- //
    struct CylinderPole {
        GLfloat x, z;
    };

    int GetSectorNum(float radius)
    {
        // TODO: there is a bug if sector number > 8, now we just set it to 8
        // if(radius <= 3){
        //     return 8;
        // }
        // if(radius <= 12){
        //     return 16;
        // }
        // if(radius <= 24){
        //     return 24;
        // }
        return 8;
    }

    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z)
    {
        glm::vec4 point(x, y, z, 1);
        point = transformMat * point;
        return {point.x, point.y, point.z};
    }

    std::vector< std::shared_ptr<GLObject> > CreateCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum){
        // if(sectorNum == -1){
        sectorNum = GetSectorNum(radius);
        // }
        std::vector<CylinderPole> cylinderPoles; // vector of structs

        glm::vec3 x1 = baseCenter, x2 = topCenter;
        glm::vec3 norm = glm::normalize(x2 - x1);
        GLfloat h = glm::length(x2 - x1);

        glm::vec3 newX = glm::normalize(glm::cross(norm, glm::vec3(0, 1, 0)));
        glm::vec3 newZ = glm::normalize(glm::cross(newX, norm));

        glm::mat4 transformMat;

        transformMat[0] = glm::vec4(newX, 0);
        transformMat[1] = glm::vec4(norm, 0);
        transformMat[2] = glm::vec4(newZ, 0);
        transformMat[3] = glm::vec4(x1, 1);

        for (int i = 0; i < sectorNum; ++i){
            GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
            CylinderPole cp{
                    .x = static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
                    .z = static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
            };
            cylinderPoles.push_back(cp);
        }

        std::vector<uint32_t> flattenedIndices;
        std::vector<glm::vec3> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> capContourTop, capContourBase;

        vertices.emplace_back(x1); // 0
        vertices.emplace_back(x2); // 1

        vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z)); // 2
        vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z)); // 3

        capContourBase.push_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
        capContourTop.push_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));

        int baseCenterIdx = 0;
        int topCenterIdx = 1;
        int prevBaseVertexIdx = 2;
        int prevTopVertexIdx = 3;
        int curBaseVertexIdx = 4;
        int curTopVertexIdx = 5;

        for(int i = 1; i < sectorNum; i++){
            capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));
            capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

            vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

            indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
            indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
            indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
            indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

            prevBaseVertexIdx = curBaseVertexIdx;
            prevTopVertexIdx = curTopVertexIdx;
            curBaseVertexIdx += 2;
            curTopVertexIdx += 2;
        }

        // Last one
        curBaseVertexIdx = 2;
        curTopVertexIdx = 3;
        indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
        indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
        indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
        indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

        capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
        capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));


        int counter = 0;
        for(auto vid: indices){
            flattenedIndices.push_back((uint)vid.x);
            flattenedIndices.push_back((uint)vid.y);
            flattenedIndices.push_back((uint)vid.z);
        }

        std::vector<glm::vec4> cylinderColorVec(vertices.size(), color);
        std::vector<glm::vec4> edgeColorVec(vertices.size(), edgeColor);

        std::vector<std::shared_ptr<GLObject>> glObjs;

        glObjs.push_back(std::make_shared<GLMeshObject>(vertices, cylinderColorVec, flattenedIndices));
        glObjs.push_back(std::make_shared<GLLineObject>(capContourBase, edgeColorVec, 1.0f));
        glObjs.push_back(std::make_shared<GLLineObject>(capContourTop, edgeColorVec, 1.0f));

        return glObjs;
    }

    std::vector< std::shared_ptr<GLObject> > CreateCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum){
        if(sectorNum == -1){
            sectorNum = GetSectorNum(radius);
        }

        std::vector<glm::vec3> vertices; // vertices.reserve(sectorNum);
        std::vector<glm::vec3> edges; // edges.reserve(2 * sectorNum);
        std::vector<uint32_t> indices; // indices.reserve(3 * sectorNum);
        vertices.emplace_back(center);

        // Rodrigues' rotation formula ?
        glm::vec3 newX = glm::normalize(glm::cross(normal, glm::vec3(0, 1, 0)));
        glm::vec3 newZ = glm::normalize(glm::cross(newX, normal));

        glm::mat4 transformMat;

        transformMat[0] = glm::vec4(newX, 0);
        transformMat[1] = glm::vec4(normal, 0);
        transformMat[2] = glm::vec4(newZ, 0);
        transformMat[3] = glm::vec4(center, 1);

        for (int i = 0; i < sectorNum; ++i){
            GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
            glm::vec3 vertex = transformMat * glm::vec4(
                    static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
                    0,
                    static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
                    1
            );
            vertices.emplace_back(vertex);
        }

        for (int i = 1; i < sectorNum; ++i){
            indices.emplace_back(0);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }
        indices.emplace_back(0);
        indices.emplace_back(sectorNum);
        indices.emplace_back(1);


        for (int i = 1; i < sectorNum; ++i){
            edges.emplace_back(vertices[i]);
            edges.emplace_back(vertices[i + 1]);
        }
        edges.emplace_back(vertices[sectorNum]);
        edges.emplace_back(vertices[1]);

        std::vector<glm::vec4> faceColorVec(vertices.size(), color);
        std::vector<glm::vec4> edgeColorVec(vertices.size(), edgeColor);

        // auto faceObj = std::make_shared<GLMeshObject>(vertices, faceColorVec, indices);
        auto edgeObj = std::make_shared<GLLineObject>(edges, edgeColorVec, edgeWeight);

        std::vector< std::shared_ptr<GLObject>> glObjs;
        
        glObjs.push_back(edgeObj);
                
        return glObjs;
    }

    std::vector< std::shared_ptr<GLObject> > CreatePolyline(std::vector<glm::vec3> vertices, bool isClosed, glm::vec4 color, float lineWidth){
        // TODO: dealing with lineWidth > 1.0
        auto glObjs = std::vector< std::shared_ptr<GLObject> >();
        if(lineWidth <= 1.0f){
            std::vector<glm::vec3> lineObjVertices; lineObjVertices.reserve(vertices.size() * 2);
            lineObjVertices.emplace_back(vertices[0]);
            for (int i = 1; i < vertices.size() - 1; i++) {
                lineObjVertices.emplace_back(vertices[i]);
                lineObjVertices.emplace_back(vertices[i]);
            }
            lineObjVertices.emplace_back(vertices[vertices.size() - 1]);
            if(isClosed){
                lineObjVertices.emplace_back(vertices[vertices.size() - 1]);
                lineObjVertices.emplace_back(vertices[0]);
            }
            std::vector<glm::vec4> colors(lineObjVertices.size(), color);
            glObjs.emplace_back(std::make_shared<GLLineObject>(lineObjVertices, colors, lineWidth));
        } else {
            for(int i = 1; i < vertices.size(); i++){
                auto radius = WEIGHT_TO_CYLINDER_RADIUS_RATE * lineWidth;
                auto cylinderLine = CreateCylinder(vertices[i - 1], vertices[i], radius, color, color);
                glObjs.insert(glObjs.end(), cylinderLine.begin(), cylinderLine.end());
            }
        }
        return glObjs;
    }

} // namespace AIAC