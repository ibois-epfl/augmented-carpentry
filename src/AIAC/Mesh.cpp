#include "Mesh.h"

// for test only
#include <iostream>
using namespace std;

namespace AIAC
{
    bool Mesh::Load(const char * path){

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
    if( !scene) {
        fprintf( stderr, importer.GetErrorString());
        getchar();
        return false;
    }
    const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

    cout << mesh->mNumVertices << endl;

    // Fill vertices positions
    Vertices.reserve(mesh->mNumVertices);
    for(unsigned int i=0; i<mesh->mNumVertices; i++){
        aiVector3D pos = mesh->mVertices[i];
        Vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
    }

    // Fill face indices
    Indices.reserve(3*mesh->mNumFaces);
    for (unsigned int i=0; i<mesh->mNumFaces; i++) {
        // Assume the model has only triangles.
        Indices.push_back(mesh->mFaces[i].mIndices[0]);
        Indices.push_back(mesh->mFaces[i].mIndices[1]);
        Indices.push_back(mesh->mFaces[i].mIndices[2]);
    }

    glGenBuffers(1, &m_Vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(glm::vec3), &Vertices[0], GL_STATIC_DRAW);

    // The "scene" pointer will be deleted automatically by "importer"
    return true;
}

    GLuint Mesh::GetGLBuffer() {
        return m_Vertexbuffer;
    }

    void Mesh::Draw() {
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);

        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, Vertices.size()); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);
    }
} // namespace AIAC

