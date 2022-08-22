#include "aiacpch.h"

#include "Mesh.h"

using namespace std;

namespace AIAC
{
    bool Mesh::Load(const char * path){
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices);
        if( !scene) {
            fprintf( stderr, importer.GetErrorString());
            getchar();
            return false;
        }
        const aiMesh* mesh = scene->mMeshes[0]; // here we use only the 1st mesh

        // Fill vertices positions
        Vertices.reserve(mesh->mNumVertices);
        for(unsigned int i=0; i<mesh->mNumVertices; i++){
            aiVector3D pos = mesh->mVertices[i];
            Vertices.emplace_back(pos.x*1, pos.y*1 , pos.z*1);
        }

        // Fill face indices
        Indices.reserve(3*mesh->mNumFaces);
        for (unsigned int i=0; i<mesh->mNumFaces; i++) {
            // Assume the model has only triangles.
            unsigned int pA = mesh->mFaces[i].mIndices[0];
            unsigned int pB = mesh->mFaces[i].mIndices[1];
            unsigned int pC = mesh->mFaces[i].mIndices[2];

            Indices.push_back(pA);
            Indices.push_back(pB);
            Indices.push_back(pC);

            Edges.emplace_back(Vertices[pA]);
            Edges.emplace_back(Vertices[pB]);
            Edges.emplace_back(Vertices[pB]);
            Edges.emplace_back(Vertices[pC]);
            Edges.emplace_back(Vertices[pC]);
            Edges.emplace_back(Vertices[pA]);
        }
        // The "scene" pointer will be deleted automatically by "importer"
        return true;
    }

    bool Mesh::Load(std::string path){
        return Load(path.c_str());
    }

    GLuint Mesh::GetGLBuffer() {
        return m_Vertexbuffer;
    }

    void Mesh::Draw() {
        DrawPoint3d(Vertices, glm::vec4(0.9, 0.9, 0.9, 0.2), 1);
        DrawLine3d(Edges, glm::vec4(1, 1, 0, 0.5));
        DrawTriangle3d(Vertices, Indices, glm::vec4(0.6, 0.35, 0.2, 0.3));
    }
} // namespace AIAC

