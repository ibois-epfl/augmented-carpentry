#pragma once
#include "GlHeader.h"
#include "GlUtils.h"

// Include AssImp
#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags

#include "glm/glm.hpp"

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

    GLuint GetGLBuffer();
    void Draw();

public:
    std::vector<uint32_t> Indices;
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> Normals;
    std::vector<glm::vec3> Edges;

private:
    GLuint m_Vertexbuffer;
    GLuint m_EdgeBuffer;
};

}
