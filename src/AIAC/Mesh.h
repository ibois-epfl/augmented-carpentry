#pragma once
#include "GlHeader.h"
#include "AIAC/Render/GlUtils.h"

// Include AssImp
#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags

#include "glm/glm.hpp"

//FIXME:: do we still need this class?
namespace AIAC{
class Mesh
{
public:
    Mesh() = default;
    Mesh(const char* path) { Load(path); };
    Mesh(std::string path) { Load(path); };
    ~Mesh() = default;

    bool Load(const char* path);
    bool Load(std::string path);

    glm::vec3 GetBboxCenter() { return BoundingBoxCenter; };

    void Draw();
    void DrawVertices(glm::vec4 color, GLfloat pointSize);
    void DrawEdges(glm::vec4 color);
    void DrawFaces(glm::vec4 color);
    void DrawBoundingBoxEdges(glm::vec4 color);

public:
    std::vector<uint32_t> Indices;
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> Normals;
    std::vector<glm::vec3> Edges;

    std::map<int, glm::vec3> BoundingBox;
    std::pair<float, float> BoundingBoxX = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    std::pair<float, float> BoundingBoxY = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    std::pair<float, float> BoundingBoxZ = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    glm::vec3 BoundingBoxCenter;
    std::vector<glm::vec3> BoundingBoxEdges;

private:
    GLuint m_Vertexbuffer;
    GLuint m_EdgeBuffer;
};

}
