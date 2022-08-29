#pragma once

#include "AIAC/GOSys/GO.h"

#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags


namespace AIAC
{
    class DLoader
    {
    public:
        DLoader() = default;
        ~DLoader() = default;

        bool LoadGOMesh(const char* path, GOMesh& goMesh);

        bool CvtAssimpMeshToGOMesh(const aiMesh* mesh, GOMesh& goMesh);

        void CvtAssimpMeshVerticesToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmVertices);
        void CvtAssimpMeshFacesToGlmVector(const aiMesh* mesh, std::vector<uint32_t>& glmIndices);
        void CvtAssimpMeshNormalsToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmNormals);
        void CvtAssimpMeshColorsToGlmVector(const aiMesh* mesh, std::vector<glm::vec3>& glmColors);
    };
}