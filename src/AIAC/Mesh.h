#pragma once
#include "GlHeader.h"

// Include AssImp
#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags

#include "glm/glm.hpp"

namespace AIAC{
class PlyLoader
{

};

class Mesh
{
public:
    Mesh() = default;
    Mesh(const char* path) { Load(path); };
    ~Mesh() = default;

    bool Load(const char* path);

    GLuint GetGLBuffer();
    void Draw();

public:
    std::vector<unsigned short> Indices;
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> Normals;

private:
    GLuint m_Vertexbuffer;
};

}
