#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/DLoader.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)

namespace AIAC
{
    bool DLoader::LoadGOMesh(const char* path, GOMesh& goMesh)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, ASSIMP_LOAD_FLAGS);  // aiProcess_JoinIdenticalVertices
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            AIAC_ERROR("Assimp failed to load {0}", importer.GetErrorString());
            return false;
        }
        const aiMesh* mesh = scene->mMeshes[0];
        unsigned int numVerticecs = mesh->mNumVertices;

        std::vector<glm::vec3> glmVertices;
        CvtAssimpMeshVerticesToGlmVector(mesh, glmVertices);
        goMesh.SetVertices(glmVertices);

        std::vector<uint32_t> glmIndices;
        CvtAssimpMeshFacesToGlmVector(mesh, glmIndices);
        goMesh.SetIndices(glmIndices);

        std::vector<glm::vec3> glmNormals;
        CvtAssimpMeshNormalsToGlmVector(mesh, glmNormals);
        goMesh.SetNormals(glmNormals);

        return true;
    }

    void DLoader::CvtAssimpMeshVerticesToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmVertices)
    {
        unsigned int numVerticecs = mesh->mNumVertices;
        for (unsigned int i = 0; i < numVerticecs; i++)
        {
            glm::vec3 vertex;
            vertex.x = mesh->mVertices[i].x;
            vertex.y = mesh->mVertices[i].y;
            vertex.z = mesh->mVertices[i].z;
            glmVertices.push_back(vertex);
        }
    }

    void DLoader::CvtAssimpMeshFacesToGlmVector(const aiMesh* mesh, std::vector<uint32_t>& glmIndices)
    {
        unsigned int numFaces = mesh->mNumFaces;
        for (unsigned int i = 0; i < numFaces; i++)
        {
            glmIndices.push_back(static_cast<uint32_t>(mesh->mFaces[i].mIndices[0]));
            glmIndices.push_back(static_cast<uint32_t>(mesh->mFaces[i].mIndices[1]));
            glmIndices.push_back(static_cast<uint32_t>(mesh->mFaces[i].mIndices[2]));
        }
    }

    void DLoader::CvtAssimpMeshNormalsToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmNormals)
    {
        unsigned int numNormals = mesh->mNumVertices;
        for (unsigned int i = 0; i < numNormals; i++)
        {
            glm::vec3 normal = glm::vec3(mesh->mNormals[i].x,
                                            mesh->mNormals[i].y,
                                            mesh->mNormals[i].z);
            glmNormals.push_back(normal);
        }
    }

    void DLoader::CvtAssimpMeshColorsToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmColors)
    {
        unsigned int numColors = mesh->mNumVertices;
        for (unsigned int i = 0; i < numColors; i++)
        {
            glm::vec3 color = glm::vec3(mesh->mColors[i]->r,
                                        mesh->mColors[i]->g,
                                        mesh->mColors[i]->b);
            glmColors.push_back(color);
        }
    }
}