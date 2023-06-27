#include "aiacpch.h"

#include "GeometryUtils.h"
#include "ScannedModel.h"

using namespace std;

namespace AIAC
{
    void ScannedModel::Load(std::string path) {
        m_MeshID = GOMesh::LoadPly(path);
        BuildBoundingBox();
    }

    void ScannedModel::BuildBoundingBox() {
        vector<glm::vec3> sortedVertices(8);

        struct Neighbor{
            Neighbor(){};
            Neighbor(float dist, glm::vec3 vec, glm::vec3 pt): dist(dist), vec(vec), pt(pt) {};
            float dist;
            glm::vec3 vec;
            glm::vec3 pt;
        };

        auto vertices = GOMesh::Get(m_MeshID)->GetVertices();
        auto basePt = vertices[0];
        vector<Neighbor> neighbors;

        // print all vertices
        for (auto& v : vertices) {
            auto vec = v - basePt;
            auto dist = glm::length(vec);
            neighbors.emplace_back(dist, vec, v);
        }

        // sort by distance
        sort(neighbors.begin(), neighbors.end(), [](Neighbor& a, Neighbor& b) {
            return a.dist < b.dist;
        });

        sortedVertices[0] = basePt;

        // filter out duplicate vertices based on point difference
        if (neighbors.size() > 8) {
            for (int i = 0; i < neighbors.size() - 1; i++) {
                if (glm::length(neighbors[i].pt - neighbors[i + 1].pt) < 0.01) {
                    neighbors.erase(neighbors.begin() + i);
                    i--;
                }
            }
        }

        auto rotationMat = GetRotationMatrix(neighbors[4].vec, 3.14159 / 2);
        auto pt1 = neighbors[1].pt - basePt;
        auto pt2 = neighbors[2].pt - basePt;
        auto test1 = glm::length(rotationMat * pt1 - pt2);
        auto test2 = glm::length(rotationMat * pt2 - pt1);
        // if it's in the correct order, test1 should be ~0,
        // therefore, when test1 > test2, it means that the order is wrong
        if (test1 > test2) {
            swap(neighbors[1], neighbors[2]);
        }

        basePt = neighbors[4].pt;
        pt1 = neighbors[5].pt - basePt;
        pt2 = neighbors[6].pt - basePt;
        test1 = glm::length(rotationMat * pt1 - pt2);
        test2 = glm::length(rotationMat * pt2 - pt1);
        // if it's in the correct order, test1 should be ~0,
        // therefore, when test1 > test2, it means that the order is wrong
        if (test1 > test2) {
            swap(neighbors[5], neighbors[6]);
        }

        // print the sorted vertices coordinates
        // for (auto& n : neighbors) {
        //    cout << n.pt.x << " " << n.pt.y << " " << n.pt.z << " / " << n.dist << endl;
        // }

        m_Bbox = {
            neighbors[0].pt,
            neighbors[4].pt,
            neighbors[6].pt,
            neighbors[2].pt,
            neighbors[1].pt,
            neighbors[5].pt,
            neighbors[7].pt,
            neighbors[3].pt
        };
    }
} // namespace AIAC

