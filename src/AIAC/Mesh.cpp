#include "aiacpch.h"

#include "Mesh.h"

using namespace std;

//FIXME:: do we still need this class?
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
            Vertices.emplace_back(pos.x, pos.y , pos.z);

            BoundingBoxX.first = min(BoundingBoxX.first, pos.x);
            BoundingBoxX.second = max(BoundingBoxX.second, pos.x);
            BoundingBoxY.first = min(BoundingBoxY.first, pos.y);
            BoundingBoxY.second = max(BoundingBoxY.second, pos.y);
            BoundingBoxZ.first = min(BoundingBoxZ.first, pos.z);
            BoundingBoxZ.second = max(BoundingBoxZ.second, pos.z);
        }

        BoundingBoxCenter = glm::vec3(
                (BoundingBoxX.first + BoundingBoxX.second) / 2.0f,
                (BoundingBoxY.first + BoundingBoxY.second) / 2.0f,
                (BoundingBoxZ.first + BoundingBoxZ.second) / 2.0f);

        // Build Bounding Box
        /*000*/ BoundingBox[0] = glm::vec3(BoundingBoxX.first, BoundingBoxY.first, BoundingBoxZ.first);
        /*001*/ BoundingBox[1] = glm::vec3(BoundingBoxX.first, BoundingBoxY.first, BoundingBoxZ.second);
        /*010*/ BoundingBox[2] = glm::vec3(BoundingBoxX.first, BoundingBoxY.second, BoundingBoxZ.first);
        /*011*/ BoundingBox[3] = glm::vec3(BoundingBoxX.first, BoundingBoxY.second, BoundingBoxZ.second);
        /*100*/ BoundingBox[4] = glm::vec3(BoundingBoxX.second, BoundingBoxY.first, BoundingBoxZ.first);
        /*101*/ BoundingBox[5] = glm::vec3(BoundingBoxX.second, BoundingBoxY.first, BoundingBoxZ.second);
        /*110*/ BoundingBox[6] = glm::vec3(BoundingBoxX.second, BoundingBoxY.second, BoundingBoxZ.first);
        /*111*/ BoundingBox[7] = glm::vec3(BoundingBoxX.second, BoundingBoxY.second, BoundingBoxZ.second);

        int edges[] = {
            0, 1,
            0, 2,
            0, 4,
            1, 3,
            1, 5,
            2, 3,
            2, 6,
            3, 7,
            4, 5,
            4, 6,
            5, 7,
            6, 7
        };
        for(int edge: edges) {
            BoundingBoxEdges.emplace_back(Vertices[edge]);
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

    void Mesh::Draw() {
        glDrawPoints3d(Vertices, glm::vec4(0.9, 0.9, 0.9, 0.2), 1);
        glDrawTriangles3d(Vertices, Indices, glm::vec4(0.6, 0.35, 0.2, 0.3));
    }

    void Mesh::DrawBoundingBoxEdges(glm::vec4 color) {
        glDrawLines3d(BoundingBoxEdges, color);
    }

    void Mesh::DrawVertices(glm::vec4 color, GLfloat pointSize) {
        glDrawPoints3d(Vertices, color, pointSize);
    }

    void Mesh::DrawEdges(glm::vec4 color) {
        glDrawLines3d(Edges, color);
    }

    void Mesh::DrawFaces(glm::vec4 color) {
        glDrawTriangles3d(Vertices, Indices, color);
    }
} // namespace AIAC

