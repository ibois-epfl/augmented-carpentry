//
// Created by ibois on 7/28/23.
//

#include "AIAC/Application.h"
#include "CutChainSawFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC {
    CutChainSawAngleFeedVisualizer::CutChainSawAngleFeedVisualizer(){
        // Line
        m_LineEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineChainBase = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineChainEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineEnd->SetColor(GOColor::WHITE);
        m_LineChainBase->SetColor(GOColor::WHITE);
        m_LineChainEnd->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_LineEnd);
        m_AllPrimitives.push_back(m_LineChainBase);
        m_AllPrimitives.push_back(m_LineChainEnd);

        Deactivate();
    }

    CutChainSawDepthFeedVisualizer::CutChainSawDepthFeedVisualizer(){
        // Line
        m_LineIntersect = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineDepthFaceEdge1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthFaceEdge2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineIntersect->SetColor(GOColor::CYAN);
        m_LineDepthFaceEdge1->SetColor(GOColor::YELLOW);
        m_LineDepthFaceEdge2->SetColor(GOColor::YELLOW);

        m_AllPrimitives.push_back(m_LineIntersect);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge1);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge2);

        Deactivate();
    }

    CutChainSawFeedVisualizer::CutChainSawFeedVisualizer(){
        // Text
        m_GuideTxtEnd = GOText::Add("End", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainBase = GOText::Add("ChainBase", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainEnd = GOText::Add("ChainEnd", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtFaceEdgeDepth1 = GOText::Add("FaceEdgeDepth1", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtFaceEdgeDepth2 = GOText::Add("FaceEdgeDepth2", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtEnd->SetColor(GOColor::WHITE);
        m_GuideTxtChainBase->SetColor(GOColor::WHITE);
        m_GuideTxtChainEnd->SetColor(GOColor::WHITE);

        m_GuideTxtFaceEdgeDepth1->SetColor(GOColor::WHITE);
        m_GuideTxtFaceEdgeDepth2->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_GuideTxtEnd);
        m_AllPrimitives.push_back(m_GuideTxtChainBase);
        m_AllPrimitives.push_back(m_GuideTxtChainEnd);

        m_AllPrimitives.push_back(m_GuideTxtFaceEdgeDepth1);
        m_AllPrimitives.push_back(m_GuideTxtFaceEdgeDepth2);

        Deactivate();
    }

    void CutChainSawFeedback::Update(){
        // calculate tool normal
        auto toolNormStartPt = AC_FF_TOOL->GetData<ChainSawData>().NormStartGO->GetPosition();
        auto toolNormEndPt = AC_FF_TOOL->GetData<ChainSawData>().NormEndGO->GetPosition();
        auto toolChainBasePt = AC_FF_TOOL->GetData<ChainSawData>().ChainBaseGO->GetPosition();
        auto toolChainMidPt = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
        auto toolChainEndPt = AC_FF_TOOL->GetData<ChainSawData>().ChainEndGO->GetPosition();
        auto toolNormalVec = glm::normalize(toolNormEndPt - toolNormStartPt);

        float nearestParallelFaceDist = 1e9f;
        std::string nearestParallelFaceID;
        float nearestPerpendicularFaceDist = 1e9f;
        std::string nearestPerpendicularFaceID;
        std::vector<std::string> parallelFaceIDs;
        std::vector<std::string> perpendicularFaceIDs;

        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        for(auto const& [faceID, faceInfo]: cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = glm::acos(glm::dot(faceNormal, toolNormalVec)/(glm::length(faceNormal)*glm::length(toolNormalVec)));

            auto distChainBase = glm::distance(faceInfo.GetCenter(), toolChainBasePt);
            auto distChainEnd = glm::distance(faceInfo.GetCenter(), toolChainEndPt);
            auto totalDist = distChainBase + distChainEnd;

            // for parallel faces, find the nearest one
            auto threshold = 0.7853f; // 45 degrees
            if(theta < threshold || (3.14159 - theta) < threshold) {
                parallelFaceIDs.push_back(faceID);
                // update nearest parallel face
                if(nearestParallelFaceID.empty() || totalDist < nearestParallelFaceDist){
                    nearestParallelFaceID = faceID;
                    nearestParallelFaceDist = totalDist;
                }
            } else {
                perpendicularFaceIDs.push_back(faceID);
                // update nearest perpendicular face
                if(nearestPerpendicularFaceID.empty() || totalDist < nearestPerpendicularFaceDist){
                    nearestPerpendicularFaceID = faceID;
                    nearestPerpendicularFaceDist = totalDist;
                }
            }
        }

        // Highlight the face
        cut->HighlightFace(nearestParallelFaceID);

        // Update the m_Visualizer for the closest parallel face
        bool hasParallelFace = false, hasPerpendicularFace = false;
        auto& angleVisualizer = this->m_Visualizer.GetAngleFeedVisualizer();

        double parallelEndDist = 0.0f;
        double parallelChainBaseDist = 0.0f;
        double parallelChainEndDist = 0.0f;
        double perpendicularFaceEdge1Dist = 0.0f;
        double perpendicularFaceEdge2Dist = 0.0f;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2; // for depth text anchor

        if(!nearestParallelFaceID.empty()){
            hasParallelFace = true;
            angleVisualizer.Activate();

            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projNormStart = GetProjectionPointOnPlane(faceNormal, faceCenter, toolNormStartPt);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainBasePt);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainEndPt);

            // update the m_Visualizer
            angleVisualizer.m_LineEnd->SetPts(toolNormStartPt, projNormStart);
            angleVisualizer.m_LineChainBase->SetPts(toolChainBasePt, projChainBase);
            angleVisualizer.m_LineChainEnd->SetPts(toolChainEndPt, projChainEnd);

            parallelEndDist = glm::distance(toolNormStartPt, projNormStart);
            parallelChainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            parallelChainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            angleVisualizer.m_LineEnd->SetColor(parallelEndDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
            angleVisualizer.m_LineChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
            angleVisualizer.m_LineChainEnd->SetColor(parallelChainEndDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
        } else {
             angleVisualizer.Deactivate();
        }

        // Perpendicular face
        auto& depthVisualizer = this->m_Visualizer.GetDepthFeedVisualizer();
        if(!nearestPerpendicularFaceID.empty()){
            hasPerpendicularFace = true;
            depthVisualizer.Activate();

            // find the projection point of the 2 points on the face
            auto faceInfo = cut->GetFace(nearestPerpendicularFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            // Get the intersection line of the tool plane and the face plane
            glm::vec3 intersectLineVec, intersectLinePt;
            if(!GetIntersectLineOf2Planes(faceNormal, faceCenter,
                                          toolNormalVec, toolChainBasePt,
                                          intersectLineVec, intersectLinePt)){
                AIAC_ERROR("Failed to get the intersect line of two planes");
                // Technically this should not happen
                // TODO: Error handling?
            }

            // Get the intersection point of the intersect line and the face's edges
            std::vector<glm::vec3> intersectPts;
            for(auto const& edgeID: faceInfo.GetEdges()){
                auto edge = cut->GetEdge(edgeID);
                auto edgePt1 = edge.GetStartPt().GetPosition();
                auto edgePt2 = edge.GetEndPt().GetPosition();
                ExtendLineSeg(edgePt1, edgePt2, 0.5f);
                glm::vec3 intersectPt;
                if(GetIntersectPointOfLineAndLineSeg(intersectLineVec, intersectLinePt, edgePt1, edgePt2, intersectPt)) {
                    intersectPts.push_back(intersectPt);
                }
            }
            FormLongestLineSeg(intersectPts, perpIntersectLineSegPt1, perpIntersectLineSegPt2);

            // update the m_Visualizer
            // FIXME: Change to intersection of two planes
            // Lines based on tool
            auto projChainBase = GetNearestPtOnLine(intersectLineVec, intersectLinePt, toolChainBasePt);
            auto projChainEnd = GetNearestPtOnLine(intersectLineVec, intersectLinePt, toolChainEndPt);

            depthVisualizer.m_LineIntersect->SetPts(projChainBase, projChainEnd);

            // Lines based on face edge
            // for face edge dist, we need to find the projection point of the two points on the saw first
            glm::vec3 pt1ProjPt, pt2ProjPt;
            auto pt1OnEndMid = GetNearestPtOnLine(toolChainEndPt - toolChainMidPt, toolChainEndPt, perpIntersectLineSegPt1);
            auto pt1OnMidBase = GetNearestPtOnLine(toolChainMidPt - toolChainBasePt, toolChainMidPt, perpIntersectLineSegPt1);
            auto pt2OnEndMid = GetNearestPtOnLine(toolChainEndPt - toolChainMidPt, toolChainEndPt, perpIntersectLineSegPt2);
            auto pt2OnMidBase = GetNearestPtOnLine(toolChainMidPt - toolChainBasePt, toolChainMidPt, perpIntersectLineSegPt2);

            pt1ProjPt = IsPointBetweenLineSeg(pt1OnMidBase, toolChainMidPt, toolChainBasePt) ? pt1OnMidBase : pt1OnEndMid;
            pt2ProjPt = IsPointBetweenLineSeg(pt2OnMidBase, toolChainMidPt, toolChainBasePt) ? pt2OnMidBase : pt2OnEndMid;

            depthVisualizer.m_LineDepthFaceEdge1->SetPts(perpIntersectLineSegPt1, pt1ProjPt);
            depthVisualizer.m_LineDepthFaceEdge2->SetPts(perpIntersectLineSegPt2, pt2ProjPt);

            perpendicularFaceEdge1Dist = glm::distance(perpIntersectLineSegPt1, pt1ProjPt);
            perpendicularFaceEdge2Dist = glm::distance(perpIntersectLineSegPt2, pt2ProjPt);

            // get the direction of tool
            auto toolUpVec = glm::normalize(toolNormStartPt - toolChainBasePt);
            auto chainBaseVec = glm::normalize(toolChainBasePt - projChainBase);
            auto chainEndVec = glm::normalize(toolChainEndPt - projChainEnd);
            auto faceEdge1Vec = glm::normalize(pt1ProjPt - perpIntersectLineSegPt1);
            auto faceEdge2Vec = glm::normalize(pt2ProjPt - perpIntersectLineSegPt2);

            if(glm::dot(toolUpVec, faceEdge1Vec) < 0){
                depthVisualizer.m_LineDepthFaceEdge1->SetColor(GOColor::RED);
                perpendicularFaceEdge1Dist = -perpendicularFaceEdge1Dist;
            } else {
                depthVisualizer.m_LineDepthFaceEdge1->SetColor(GOColor::YELLOW);
            }
            if(glm::dot(toolUpVec, faceEdge2Vec) < 0){
                depthVisualizer.m_LineDepthFaceEdge2->SetColor(GOColor::RED);
                perpendicularFaceEdge2Dist = -perpendicularFaceEdge2Dist;
            } else {
                depthVisualizer.m_LineDepthFaceEdge2->SetColor(GOColor::YELLOW);
            }

        } else {
            depthVisualizer.Deactivate();
        }

        if(hasParallelFace || hasPerpendicularFace) {
            m_Visualizer.Activate();

            // auto toString = [](double &val) -> std::string {
            //     // TODO: / 50 * 1000 => mm, change this to a variable
            //     int valInt = (int)(val / 50 * 1000);
            //     if(valInt > 99) valInt = 99;
            //     auto retVal = std::to_string(valInt);
            //     if(retVal.length() == 1){
            //         return "0" + retVal;
            //     }
            //     return retVal;
            // };

            auto strEnd = FeedbackVisualizer::toString(parallelEndDist);
            auto strChainBase = FeedbackVisualizer::toString(parallelChainBaseDist);
            auto strChainEnd = FeedbackVisualizer::toString(parallelChainEndDist);

            this->m_Visualizer.m_GuideTxtEnd->SetText(strEnd);
            this->m_Visualizer.m_GuideTxtChainBase->SetText(strChainBase);
            this->m_Visualizer.m_GuideTxtChainEnd->SetText(strChainEnd);

            this->m_Visualizer.m_GuideTxtFaceEdgeDepth1->SetText(FeedbackVisualizer::toString(perpendicularFaceEdge1Dist));
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth2->SetText(FeedbackVisualizer::toString(perpendicularFaceEdge2Dist));

            this->m_Visualizer.m_GuideTxtEnd->SetAnchor(toolNormStartPt);
            this->m_Visualizer.m_GuideTxtChainBase->SetAnchor(toolChainBasePt);
            this->m_Visualizer.m_GuideTxtChainEnd->SetAnchor(toolChainEndPt);

            this->m_Visualizer.m_GuideTxtFaceEdgeDepth1->SetAnchor(perpIntersectLineSegPt1);
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth2->SetAnchor(perpIntersectLineSegPt2);

            auto endColor = GOColor::WHITE;
            auto chainBaseColor = GOColor::WHITE;
            auto chainEndColor = GOColor::WHITE;

            auto faceEdgeTxt1Color = GOColor::WHITE;
            auto faceEdgeTxt2Color = GOColor::WHITE;

            if(parallelEndDist != 0 && parallelEndDist < 0.5f){
                endColor = GOColor::YELLOW;
            }
            if(parallelChainBaseDist != 0 && parallelChainBaseDist < 0.5f){
                chainBaseColor = GOColor::YELLOW;
            }
            if(parallelChainEndDist != 0 && parallelChainEndDist < 0.5f){
                chainEndColor = GOColor::YELLOW;
            }

            if(perpendicularFaceEdge1Dist > 0 && perpendicularFaceEdge1Dist < 0.5f){
                faceEdgeTxt1Color = GOColor::YELLOW;
            } else if (perpendicularFaceEdge1Dist < 0){
                faceEdgeTxt1Color = GOColor::RED;
            }
            if(perpendicularFaceEdge2Dist > 0 && perpendicularFaceEdge2Dist < 0.5f){
                faceEdgeTxt2Color = GOColor::ORANGE;
            } else if (perpendicularFaceEdge2Dist < 0){
                faceEdgeTxt2Color = GOColor::RED;
            }

            this->m_Visualizer.m_GuideTxtEnd->SetColor(endColor);
            this->m_Visualizer.m_GuideTxtChainBase->SetColor(chainBaseColor);
            this->m_Visualizer.m_GuideTxtChainEnd->SetColor(chainEndColor);

            this->m_Visualizer.m_GuideTxtFaceEdgeDepth1->SetColor(faceEdgeTxt1Color);
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth2->SetColor(faceEdgeTxt2Color);

        }
        else m_Visualizer.Deactivate();
    }

    void CutChainSawFeedback::Activate(){
        Update();
        m_Visualizer.Activate();
    }

    void CutChainSawFeedback::Deactivate(){
        m_Visualizer.Deactivate();
    }
}

