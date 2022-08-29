#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/DLoader.h"

#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)

namespace AIAC
{
    bool DLoader::LoadMesh(const char* path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, ASSIMP_LOAD_FLAGS);  // aiProcess_JoinIdenticalVertices
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            AIAC_ERROR("Assimp failed to load {0}", importer.GetErrorString());
            return false;
        }
        const aiMesh* mesh = scene->mMeshes[0];
        mesh->mNumVertices;
        mesh->mVertices;
        mesh->mNumFaces;
        mesh->mFaces;
        mesh->mNormals;
        mesh->mColors;
        
        return true;
        
    }
}