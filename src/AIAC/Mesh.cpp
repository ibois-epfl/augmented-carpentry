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

    GLuint Mesh::GetGLBuffer() {
        return m_Vertexbuffer;
    }

    void Mesh::Draw() {
        glGenBuffers(1, &m_Vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(glm::vec3), &Vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*) nullptr     // array buffer offset
        );
        glDrawArrays(GL_POINTS, 0, (GLsizei)Vertices.size());

        glGenBuffers(1, &m_EdgeBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_EdgeBuffer);
        glBufferData(GL_ARRAY_BUFFER, Edges.size() * sizeof(glm::vec3), &Edges[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_EdgeBuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*) nullptr     // array buffer offset
        );
        glDrawArrays(GL_LINES, 0, (GLsizei)Edges.size());
    }
} // namespace AIAC

