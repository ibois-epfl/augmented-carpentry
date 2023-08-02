//
// Created by ibois on 7/28/23.
//

#include "AIAC/Application.h"
#include "CutCircularSawFeedback.h"

namespace AIAC {
    CutCircularSawFeedbackVisualizer::CutCircularSawFeedbackVisualizer() {
        m_BottomPoint = GOPoint::Add(GOPoint(0.f, 0.f, 0.f), 5.0f);
        m_LineToBottomPt = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_ProjLineOnFace = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineSide2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_TxtBottomDist = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));

        m_BottomPoint->SetColor(GOColor::YELLOW);
        m_LineToBottomPt->SetColor(GOColor::YELLOW);
        m_ProjLineOnFace->SetColor(GOColor::CYAN);
        m_LineSide2->SetColor(GOColor::BLUE);
        m_TxtBottomDist->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_BottomPoint);
        m_AllPrimitives.push_back(m_LineToBottomPt);
        m_AllPrimitives.push_back(m_ProjLineOnFace);
        m_AllPrimitives.push_back(m_LineSide2);
        m_AllPrimitives.push_back(m_TxtBottomDist);

        Deactivate();
    }

    void CutCircularSawFeedback::Update() {
        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        updatePosition();
        updateRefFaces();
        updateDownVecAndBottomPoint();
    }

    void CutCircularSawFeedback::Activate() {
        m_Visualizer.Activate();
        Update();
    }

    void CutCircularSawFeedback::Deactivate() {
        m_Visualizer.Deactivate();
    }

    void CutCircularSawFeedback::updatePosition() {
        m_Radius = AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        m_Center = AC_FF_TOOL->GetData<CircularSawData>().CenterGO->GetPosition();
        m_NormalStart = m_Center; // AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition(); // this value is not initialized
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
        auto prepPlnCenter = m_Cut->GetFace(m_NearestPerpendicularFaceID).GetCenter();
        auto perpPlnNormal = m_Cut->GetFace(m_NearestPerpendicularFaceID).GetNormal();
        glm::vec3 perpFaceOfBladeVec = glm::normalize(glm::cross(m_Normal, perpPlnNormal));
        glm::vec3 _ptPlaceHolder;
        GetIntersectLineOf2Planes(
            m_Normal, m_Center,
            perpFaceOfBladeVec, m_Center,
            m_DownVec, _ptPlaceHolder
        );
        // get the bottom point and update
        m_BottomPoint = m_Center + m_DownVec * m_Radius;
        m_Visualizer.m_BottomPoint->SetPosition(m_BottomPoint);
        m_Visualizer.m_LineToBottomPt->SetPts(m_Center, m_BottomPoint);

        // side point of the blade
        auto sidePt1 = m_Center + perpFaceOfBladeVec * m_Radius;
        auto projSidePt1 = GetProjectionPointOnPlane(perpPlnNormal, prepPlnCenter, sidePt1);
        auto sidePt2 = m_Center - perpFaceOfBladeVec * m_Radius;
        auto projSidePt2 = GetProjectionPointOnPlane(perpPlnNormal, prepPlnCenter, sidePt2);
        m_Visualizer.m_ProjLineOnFace->SetPts(projSidePt1, projSidePt2);

        // distance to the bottom face
        auto projBtmPt = GetProjectionPointOnPlane(perpPlnNormal, prepPlnCenter, m_BottomPoint);
        auto dist = glm::distance(projBtmPt, m_BottomPoint);
        m_Visualizer.m_TxtBottomDist->SetAnchor(projBtmPt);
        m_Visualizer.m_TxtBottomDist->SetText(FeedbackVisualizer::toString(dist));

    }
}