//
// Created by ibois on 7/28/23.
//

#include "AIAC/Application.h"
#include "CutCircularSawFeedback.h"

namespace AIAC {
    CutCircularSawFeedbackVisualizer::CutCircularSawFeedbackVisualizer() {
        m_LineBottom = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineSide1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineSide2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineBottom->SetColor(GOColor::CYAN);
        m_LineSide1->SetColor(GOColor::YELLOW);
        m_LineSide2->SetColor(GOColor::YELLOW);

        m_AllPrimitives.push_back(m_LineBottom);
        m_AllPrimitives.push_back(m_LineSide1);
        m_AllPrimitives.push_back(m_LineSide2);

        Deactivate();
    }

    CutCircularSawFeedback::CutCircularSawFeedback() {
        
    }

    void CutCircularSawFeedback::Update() {
        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        updatePosition();
        updateRefFaces();
    }

    void CutCircularSawFeedback::updatePosition() {
        m_Radius = AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        m_Center = AC_FF_TOOL->GetData<CircularSawData>().CenterACIT;
        m_NormalStart = AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition();
        m_NormalEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
        m_Normal = glm::normalize(m_NormalEnd - m_NormalStart);
    }

    void CutCircularSawFeedback::updateRefFaces() {
        float nearestParallelFaceDist = 0.f;
        std::string nearestParallelFaceID;

        std::vector<std::pair<std::string, float>> perpenFaces;

        for(auto const& [faceID, faceInfo]: m_Cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = glm::acos(
                            glm::dot(faceNormal, m_Normal) / 
                            (glm::length(faceNormal) * glm::length(m_Normal))
                        );

            auto dist = glm::distance(faceInfo.GetCenter(), m_Center);

            // for parallel faces, find the nearest one
            auto threshold = 0.7853f; // 45 degrees
            if(theta < threshold || (3.14159 - theta) < threshold) {
                // update nearest parallel face
                if(nearestParallelFaceID.empty() || dist < nearestParallelFaceDist){
                    nearestParallelFaceID = faceID;
                    nearestParallelFaceDist = dist;
                }
            } else {
                perpenFaces.push_back(std::make_pair(faceID, dist));
            }
        }

        // sort perpendicular faces by distance
        std::sort(perpenFaces.begin(), perpenFaces.end(), [](auto const& a, auto const& b){
            return a.second < b.second;
        });

        // update class members
        if(nearestParallelFaceID.empty()){
            if(perpenFaces.size() < 2) {
                // TODO: catch error
                return;
            }
            m_NearestParallelFaceID = perpenFaces[0].first;
            m_NearestPerpendicularFaceID = perpenFaces[1].first;
        } else {
            m_NearestParallelFaceID = nearestParallelFaceID;
            m_NearestPerpendicularFaceID = perpenFaces[0].first;
        }
    }

    void CutCircularSawFeedback::updateDownVecAndBottomPoint() {
        glm::vec3 perpFaceOfBladeVec = glm::normalize(glm::cross(m_Normal, m_Cut->GetNormal()));
        glm::vec3 _ptPlaceHolder;
        GetIntersectLineOf2Planes(
            m_Normal, m_Center,
            perpFaceOfBladeVec, m_Center,
            m_DownVec, _ptPlaceHolder
        );

        // TODO: get the bottom point and update
    }
}