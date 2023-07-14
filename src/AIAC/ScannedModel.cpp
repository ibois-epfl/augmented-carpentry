#include "aiacpch.h"

#include "GeometryUtils.h"
#include "ScannedModel.h"

using namespace std;

namespace AIAC
{
    void ScannedModel::Load(std::string path) {
        m_Mesh = GOMesh::LoadPly(path);
        // m_Mesh->SetColor(glm::vec4(0.9f, 0.7f, 0.1f, 0.2f));
        m_Mesh->SetVisibility(false);

        BuildBoundingBox();
        UpdateBboxGOLine();
    }

    void ScannedModel::BuildBoundingBox() {
        struct Neighbor{
            Neighbor(){};
            Neighbor(float dist, glm::vec3 vec, glm::vec3 pt): dist(dist), vec(vec), pt(pt) {};
            float dist;
            glm::vec3 vec;
            glm::vec3 pt;
        };

        auto vertices = m_Mesh->GetVertices();
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

        // re-order the vertices, making it a counter-clockwise order start from the longer edge
        // first bottom, then top
        //
        //   (7)------------------------(6)
        //   / |                       / |  
        // (4)-----------------------(5) |
        //  |  |                      |  |
        //  | (3)---------------------|-(2)
        //  |/                        |/
        // (0)-----------------------(1)
        //
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

    void ScannedModel::UpdateBboxGOLine() {
        // update the GOLine references
        for(auto& line : m_BboxGOLines)
            GOLine::Remove(line);
        
        // bottom
        auto vec = glm::normalize(m_Bbox[1] - m_Bbox[0]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[0], m_Bbox[0] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[1], m_Bbox[1] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[2] - m_Bbox[1]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[1], m_Bbox[1] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[2], m_Bbox[2] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[3] - m_Bbox[2]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[2], m_Bbox[2] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[3], m_Bbox[3] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[0] - m_Bbox[3]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[3], m_Bbox[3] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[0], m_Bbox[0] - vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[0], m_Bbox[1], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[1], m_Bbox[2], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[2], m_Bbox[3], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[3], m_Bbox[0], 2.0f));

        // top
        vec = glm::normalize(m_Bbox[5] - m_Bbox[4]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[4], m_Bbox[4] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[5], m_Bbox[5] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[6] - m_Bbox[5]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[5], m_Bbox[5] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[6], m_Bbox[6] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[7] - m_Bbox[6]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[6], m_Bbox[6] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[7], m_Bbox[7] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[4] - m_Bbox[7]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[7], m_Bbox[7] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[4], m_Bbox[4] - vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[4], m_Bbox[5], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[5], m_Bbox[6], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[6], m_Bbox[7], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[7], m_Bbox[4], 2.0f));

        // side
        vec = glm::normalize(m_Bbox[4] - m_Bbox[0]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[0], m_Bbox[0] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[4], m_Bbox[4] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[5] - m_Bbox[1]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[1], m_Bbox[1] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[5], m_Bbox[5] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[6] - m_Bbox[2]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[2], m_Bbox[2] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[6], m_Bbox[6] - vec, 2.0f));
        vec = glm::normalize(m_Bbox[7] - m_Bbox[3]);
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[3], m_Bbox[3] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(m_Bbox[7], m_Bbox[7] - vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[0], m_Bbox[4], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[1], m_Bbox[5], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[2], m_Bbox[6], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(m_Bbox[3], m_Bbox[7], 2.0f));
    }

    float ScannedModel::GetLength(){
        float dist = 0.0f;
        dist += glm::distance(m_Bbox[0], m_Bbox[1]);
        dist += glm::distance(m_Bbox[2], m_Bbox[3]);
        dist += glm::distance(m_Bbox[4], m_Bbox[5]);
        dist += glm::distance(m_Bbox[6], m_Bbox[7]);
        dist /= 4.0f;

        return dist;
    }

} // namespace AIAC

