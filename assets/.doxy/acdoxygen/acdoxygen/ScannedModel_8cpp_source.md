

# File ScannedModel.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**ScannedModel.cpp**](ScannedModel_8cpp.md)

[Go to the documentation of this file](ScannedModel_8cpp.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#include "aiacpch.h"

#include "GeometryUtils.h"
#include "ScannedModel.h"

namespace AIAC
{
    bool ScannedModel::Load(std::string path) {
        // check if file is good
        if(path.empty()){
            AIAC_ERROR("ACInfoModel::Load() path is empty");
            return false;
        }
        if(!std::filesystem::exists(path)){
            AIAC_ERROR("ACInfoModel::Load() file does not exist");
            return false;
        }

        m_Mesh = GOMesh::LoadPly(path);
        if(m_Mesh == nullptr) return false;
        
        m_Mesh->SetVisibility(false);

        BuildBoundingBox();
        UpdateBboxGOLine();

        return true;
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
        std::vector<Neighbor> neighbors;

        for (auto& v : vertices) {
            auto vec = v - basePt;
            auto dist = glm::length(vec);
            neighbors.emplace_back(dist, vec, v);
        }

        // sort by distance
        std::sort(neighbors.begin(), neighbors.end(), [](Neighbor& a, Neighbor& b) {
            return a.dist < b.dist;
        });

        // filter out duplicate vertices based on point difference
        if (neighbors.size() > 8) {
            for (int i = 0; i < neighbors.size() - 1; i++) {
                if (glm::length(neighbors[i].pt - neighbors[i + 1].pt) < 0.05) {
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
            std::swap(neighbors[1], neighbors[2]);
        }

        basePt = neighbors[4].pt;
        pt1 = neighbors[5].pt - basePt;
        pt2 = neighbors[6].pt - basePt;
        test1 = glm::length(rotationMat * pt1 - pt2);
        test2 = glm::length(rotationMat * pt2 - pt1);
        // if it's in the correct order, test1 should be ~0,
        // therefore, when test1 > test2, it means that the order is wrong
        if (test1 > test2) {
            std::swap(neighbors[5], neighbors[6]);
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

        // testing the rotation is correct
        float minTotalDist = 1e9;
        int rotIndex = -1;
        for(int i = 0 ; i < 4 ; i++){
            float dist = 0;
            for(int j = 0 ; j < 8 ; j+=2){
                dist += glm::length(m_Bbox[j] - m_Bbox[j + 1]);
            }
            if(dist < minTotalDist){
                minTotalDist = dist;
                rotIndex = i;
            }
            // perform rotation
            auto tmp = m_Bbox[0];
            m_Bbox[0] = m_Bbox[3];
            m_Bbox[3] = m_Bbox[7];
            m_Bbox[7] = m_Bbox[4];
            m_Bbox[4] = tmp;
        }
        // rotate to the correct order
        for(int i = 0 ; i < rotIndex ; i++){
            auto tmp = m_Bbox[0];
            m_Bbox[0] = m_Bbox[3];
            m_Bbox[3] = m_Bbox[7];
            m_Bbox[7] = m_Bbox[4];
            m_Bbox[4] = tmp;
        }
    }

    void ScannedModel::UpdateBboxGOLine() {
        // update the GOLine references
        for(auto& line : m_BboxGOLines)
            GOLine::Remove(line);
        
        for(auto& edge : m_BboxEdgesIndices){
            auto i = edge.first, k = edge.second;
            auto vec = glm::normalize(m_Bbox[k] - m_Bbox[i]);
            m_BboxGOLines.push_back(GOLine::Add(m_Bbox[i], m_Bbox[i] + vec, 2.0f));
            m_BboxGOLines.push_back(GOLine::Add(m_Bbox[k], m_Bbox[k] - vec, 2.0f));
        }
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

```


