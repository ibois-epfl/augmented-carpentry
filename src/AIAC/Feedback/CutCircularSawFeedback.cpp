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
        m_ProjLineOfBlade = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_TxtBottomDist = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));

        m_BottomPoint->SetColor(GOColor::YELLOW);
        m_LineToBottomPt->SetColor(GOColor::YELLOW);
        m_ProjLineOnFace->SetColor(GOColor::CYAN);
        m_ProjLineOfBlade->SetColor(GOColor::CYAN);
        m_TxtBottomDist->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_BottomPoint);
        m_AllPrimitives.push_back(m_LineToBottomPt);
        m_AllPrimitives.push_back(m_ProjLineOnFace);
        m_AllPrimitives.push_back(m_ProjLineOfBlade);
        m_AllPrimitives.push_back(m_TxtBottomDist);

        Deactivate();
    }

    void CutCircularSawFeedback::Update() {
        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        updateToolPosition();
        updateRefFaces();
        updateFeedback();
    }

    void CutCircularSawFeedback::Activate() {
        Update();
    }

    void CutCircularSawFeedback::Deactivate() {
        m_CutPlaneVisualizer.Deactivate();
        m_GeneralVisualizer.Deactivate();
    }

    void CutCircularSawFeedback::updateToolPosition() {
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
        // if the saw is place on the side for adjusting the height, there should be no parallel face
        if(nearestParallelFaceID.empty()){
            if(perpenFaces.size() < 2) {
                // TODO: catch error
                return;
            }
            m_NearestParallelFaceID = perpenFaces[0].first;
            m_NearestPerpendicularFaceID = perpenFaces[1].first;
        } else {
            m_NearestParallelFaceID = nearestParallelFaceID;
            if(!perpenFaces.empty()){
                m_NearestPerpendicularFaceID = perpenFaces[0].first;
            } else {
                m_NearestPerpendicularFaceID.clear();
            }
        }
    }

    void CutCircularSawFeedback::updateFeedback() {
        if(!m_NearestPerpendicularFaceID.empty()){
            m_GeneralVisualizer.Activate();
            updateGeneralFeedback();
        }
        m_CutPlaneVisualizer.Activate();
        updateCutPlaneFeedback();
    }

    /**
     * @brief The "General" situation means that we have a perpendicular face that served as 
     * the "bottom" face, where the bottom of the saw blade should be placed on. Therefore, the
     * m_DownVec, which indicate the direction from the center to the bottom of the saw blade,
     * is calculated based on the perpendicular face.
     * 
     */
    void CutCircularSawFeedback::updateGeneralFeedback(){
        auto prepFaceInfo = m_Cut->GetFace(m_NearestPerpendicularFaceID);
        auto prepPlnCenter = prepFaceInfo.GetCenter();
        auto perpPlnNormal = prepFaceInfo.GetNormal();
        glm::vec3 perpFaceOfBladeVec = glm::normalize(glm::cross(m_Normal, perpPlnNormal));
        glm::vec3 _ptPlaceHolder;
        GetIntersectLineOf2Planes(
            m_Normal, m_Center,
            perpFaceOfBladeVec, m_Center,
            m_DownVec, _ptPlaceHolder
        );

        if(glm::distance(m_Center + m_DownVec * m_Radius, prepFaceInfo.GetCenter()) >
           glm::distance(m_Center - m_DownVec * m_Radius, prepFaceInfo.GetCenter())){
            m_DownVec = -m_DownVec;
        }

        // get the bottom point and update
        m_BottomPoint = m_Center + m_DownVec * m_Radius;
        m_GeneralVisualizer.m_BottomPoint->SetPosition(m_BottomPoint);
        m_GeneralVisualizer.m_LineToBottomPt->SetPts(m_Center, m_BottomPoint);

        // side point of the blade
        auto sidePt1 = m_Center + perpFaceOfBladeVec * m_Radius;
        auto sidePt2 = m_Center - perpFaceOfBladeVec * m_Radius;
        glm::vec3 projSidePt1, projSidePt2;
        GetIntersectPointOfLineAndPlane(m_DownVec, sidePt1, perpPlnNormal, prepPlnCenter, projSidePt1);
        GetIntersectPointOfLineAndPlane(m_DownVec, sidePt2, perpPlnNormal, prepPlnCenter, projSidePt2);
        m_GeneralVisualizer.m_ProjLineOfBlade->SetPts(projSidePt1, projSidePt2);

        // distance to the bottom face
        auto projBtmPt = GetProjectionPointOnPlane(perpPlnNormal, prepPlnCenter, m_BottomPoint);
        auto dist = glm::distance(projBtmPt, m_BottomPoint);

        if(IsPointBetweenLineSeg(m_BottomPoint, m_Center, projBtmPt)){
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::WHITE);
        } else {
            dist = -dist;
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::RED);
        }

        m_GeneralVisualizer.m_TxtBottomDist->SetAnchor(projBtmPt);
        m_GeneralVisualizer.m_TxtBottomDist->SetText(FeedbackVisualizer::toString(dist));

        // Projection line on face
        // Find all intersection points on the edges of the perpendicular face, and form the longest segment
        std::vector<glm::vec3> intersectPts;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2;
        for(auto const& edgeID: prepFaceInfo.GetEdges()){
            auto edge = m_Cut->GetEdge(edgeID);
            auto edgePt1 = edge.GetStartPt().GetPosition();
            auto edgePt2 = edge.GetEndPt().GetPosition();
            ExtendLineSeg(edgePt1, edgePt2, 1.0f);
            glm::vec3 intersectPt;
            if(GetIntersectPointOfLineAndLineSeg((projSidePt2 - projSidePt1), projSidePt1, edgePt1, edgePt2, intersectPt)) {
                intersectPts.push_back(intersectPt);
            }
        }
        FormLongestLineSeg(intersectPts, perpIntersectLineSegPt1, perpIntersectLineSegPt2);
        m_GeneralVisualizer.m_ProjLineOnFace->SetPts(perpIntersectLineSegPt1, perpIntersectLineSegPt2);
    }

    /**
     * @brief Show the intersection plane of the tool and virtual model.
     * When there is no perpendicular face, it will be very useful.
     */
    void CutCircularSawFeedback::updateCutPlaneFeedback(){
        m_CutPlaneVisualizer.Update(m_Normal, m_Center);
    }
}