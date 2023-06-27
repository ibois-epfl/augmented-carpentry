#include "aiacpch.h"

#include "ScannedModel.h"

using namespace std;

//FIXME:: do we still need this class?
namespace AIAC
{
    void ScannedModel::Load(std::string path) {
        m_MeshID = GOMesh::LoadPly(path);
        BuildBoundingBox();
    }

    void ScannedModel::BuildBoundingBox() {
        auto vertices = GOMesh::Get(m_MeshID)->GetVertices();
        auto basePt = vertices[0];

        // print all vertices
        for (auto& v : vertices) {
            cout << v.x << " " << v.y << " " << v.z << endl;
        }
    }
} // namespace AIAC

