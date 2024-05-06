//
// Created by ibois on 7/28/23.
//

#include "AIAC/Application.h"
#include "CutChainSawFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC
{
    CutOrientationVisualizer::CutOrientationVisualizer()
    {
        // Normal face line 
        m_LineFaceNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineBladeNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineFaceNormal->SetColor(GOColor::CYAN);
        m_LineBladeNormal->SetColor(GOColor::MAGENTA);
        
        m_AllPrimitives.push_back(m_LineFaceNormal);
        m_AllPrimitives.push_back(m_LineBladeNormal);

        Deactivate();
    }

    CutChainSawAngleFeedVisualizer::CutChainSawAngleFeedVisualizer()
    {
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

    CutChainSawDepthFeedVisualizer::CutChainSawDepthFeedVisualizer()
    {
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

    CutChainSawFeedVisualizer::CutChainSawFeedVisualizer()
    {
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

    void CutChainSawFeedback::updateCutPlane ()
    {
        if(m_ToShowCutPlane) m_CutPlaneVisualizer.Update(m_NormalVec, m_NormStart);
    }

    void CutChainSawFeedback::Update()
    {
        // calculate tool normal
        m_NormStart = AC_FF_TOOL->GetData<ChainSawData>().NormStartGO->GetPosition();
        m_NormEnd = AC_FF_TOOL->GetData<ChainSawData>().NormEndGO->GetPosition();
        m_ChainBase = AC_FF_TOOL->GetData<ChainSawData>().ChainBaseGO->GetPosition();
        m_ChainMid = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
        m_ChainEnd = AC_FF_TOOL->GetData<ChainSawData>().ChainEndGO->GetPosition();
        m_NormalVec = glm::normalize(m_NormEnd - m_NormStart);

        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        auto& angleVisualizer = this->m_Visualizer.GetAngleFeedVisualizer();
        auto& depthVisualizer = this->m_Visualizer.GetDepthFeedVisualizer();

        if(m_ToShowCutPlane) updateCutPlane();
        
        // if it's a single face, only show the red cutting plane
        if(cut->IsSingleFace()) {
            this->m_Visualizer.Deactivate();
            angleVisualizer.Deactivate();
            depthVisualizer.Deactivate();
            return;
        }

        float nearestParallelFaceDist = 1e9f;
        std::string nearestParallelFaceID;
        float nearestPerpendicularFaceDist = 1e9f;
        std::string nearestPerpendicularFaceID;
        std::vector<std::string> parallelFaceIDs;
        std::vector<std::string> perpendicularFaceIDs;

        for(auto const& [faceID, faceInfo]: cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = glm::acos(glm::dot(faceNormal, m_NormalVec)/(glm::length(faceNormal)*glm::length(m_NormalVec)));

            auto distChainBase = glm::distance(faceInfo.GetCenter(), m_ChainBase);
            auto distChainEnd = glm::distance(faceInfo.GetCenter(), m_ChainEnd);
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

        double parallelEndDist = 0.0f;
        double parallelChainBaseDist = 0.0f;
        double parallelChainEndDist = 0.0f;
        double perpendicularFaceEdge1Dist = 0.0f;
        double perpendicularFaceEdge2Dist = 0.0f;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2; // for depth text anchor

        // update angle visualizer
        if(!nearestParallelFaceID.empty())
        {
            hasParallelFace = true;
            angleVisualizer.Activate();

            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projNormStart = GetProjectionPointOnPlane(faceNormal, faceCenter, m_NormStart);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, m_ChainBase);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, m_ChainEnd);

            // update the m_Visualizer
            angleVisualizer.m_LineEnd->SetPts(m_NormStart, projNormStart);
            angleVisualizer.m_LineChainBase->SetPts(m_ChainBase, projChainBase);
            angleVisualizer.m_LineChainEnd->SetPts(m_ChainEnd, projChainEnd);

            parallelEndDist = glm::distance(m_NormStart, projNormStart);
            parallelChainBaseDist = glm::distance(m_ChainBase, projChainBase);
            parallelChainEndDist = glm::distance(m_ChainEnd, projChainEnd);

            angleVisualizer.m_LineEnd->SetColor(parallelEndDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
            angleVisualizer.m_LineChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
            angleVisualizer.m_LineChainEnd->SetColor(parallelChainEndDist < 0.5f ? GOColor::YELLOW : GOColor::WHITE);
        }
        else
        {
            angleVisualizer.Deactivate();
        }

        // TODO: test:: orientation visualizer
        if (!nearestParallelFaceID.empty())
        {
            m_CutOrientationVisualizer.Activate();

            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();
            m_CutOrientationVisualizer.m_LineFaceNormal->SetPts(faceCenter, faceCenter + faceNormal);

            auto bladeNormal = glm::normalize(m_NormEnd - m_NormStart);
            m_CutOrientationVisualizer.m_LineBladeNormal->SetPts(m_NormStart, m_NormStart + bladeNormal);
        }
        else
        {
            m_CutOrientationVisualizer.Deactivate();
        }

        // Perpendicular face
        if(!nearestPerpendicularFaceID.empty())
        {
            hasPerpendicularFace = true;

            // find the projection point of the 2 points on the face
            auto faceInfo = cut->GetFace(nearestPerpendicularFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            // Get the intersection line of the tool plane and the face plane
            glm::vec3 intersectLineVec, intersectLinePt;
            if(!GetIntersectLineOf2Planes(faceNormal, faceCenter,
                                          m_NormalVec, m_ChainBase,
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
            auto projChainBase = GetNearestPtOnLine(intersectLineVec, intersectLinePt, m_ChainBase);
            auto projChainEnd = GetNearestPtOnLine(intersectLineVec, intersectLinePt, m_ChainEnd);

            depthVisualizer.m_LineIntersect->SetPts(projChainBase, projChainEnd);

            // Lines based on face edge
            // for face edge dist, we need to find the projection point of the two points on the saw first
            glm::vec3 pt1ProjPt, pt2ProjPt;
            auto pt1OnEndMid = GetNearestPtOnLine(m_ChainEnd - m_ChainMid, m_ChainEnd, perpIntersectLineSegPt1);
            auto pt1OnMidBase = GetNearestPtOnLine(m_ChainMid - m_ChainBase, m_ChainMid, perpIntersectLineSegPt1);
            auto pt2OnEndMid = GetNearestPtOnLine(m_ChainEnd - m_ChainMid, m_ChainEnd, perpIntersectLineSegPt2);
            auto pt2OnMidBase = GetNearestPtOnLine(m_ChainMid - m_ChainBase, m_ChainMid, perpIntersectLineSegPt2);

            bool pt1Found = false, pt2Found = false;
            if(IsPointBetweenLineSeg(pt1OnMidBase, m_ChainMid, m_ChainBase)){
                pt1ProjPt = pt1OnMidBase;
                pt1Found = true;
            } else if(IsPointBetweenLineSeg(pt1OnEndMid, m_ChainEnd, m_ChainMid)){
                pt1ProjPt = pt1OnEndMid;
                pt1Found = true;
            }
            if(IsPointBetweenLineSeg(pt2OnMidBase, m_ChainMid, m_ChainBase)){
                pt2ProjPt = pt2OnMidBase;
                pt2Found = true;
            } else if(IsPointBetweenLineSeg(pt2OnEndMid, m_ChainEnd, m_ChainMid)){
                pt2ProjPt = pt2OnEndMid;
                pt2Found = true;
            }
            if(pt1Found && pt2Found){
                depthVisualizer.m_LineDepthFaceEdge1->SetPts(perpIntersectLineSegPt1, pt1ProjPt);
                depthVisualizer.m_LineDepthFaceEdge2->SetPts(perpIntersectLineSegPt2, pt2ProjPt);

                perpendicularFaceEdge1Dist = glm::distance(perpIntersectLineSegPt1, pt1ProjPt);
                perpendicularFaceEdge2Dist = glm::distance(perpIntersectLineSegPt2, pt2ProjPt);

                // get the direction of tool
                auto toolUpVec = glm::normalize(m_NormStart - m_ChainBase);
                auto chainBaseVec = glm::normalize(m_ChainBase - projChainBase);
                auto chainEndVec = glm::normalize(m_ChainEnd - projChainEnd);
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
                depthVisualizer.Activate();
            } else {
                depthVisualizer.Deactivate();    
            }
        } else
        {
            depthVisualizer.Deactivate();
        }

        if(hasParallelFace || hasPerpendicularFace)
        {
            m_Visualizer.Activate();

            auto strEnd = FeedbackVisualizer::toString(parallelEndDist);
            auto strChainBase = FeedbackVisualizer::toString(parallelChainBaseDist);
            auto strChainEnd = FeedbackVisualizer::toString(parallelChainEndDist);

            this->m_Visualizer.m_GuideTxtEnd->SetText(strEnd);
            this->m_Visualizer.m_GuideTxtChainBase->SetText(strChainBase);
            this->m_Visualizer.m_GuideTxtChainEnd->SetText(strChainEnd);

            this->m_Visualizer.m_GuideTxtFaceEdgeDepth1->SetText(FeedbackVisualizer::toString(perpendicularFaceEdge1Dist));
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth2->SetText(FeedbackVisualizer::toString(perpendicularFaceEdge2Dist));

            this->m_Visualizer.m_GuideTxtEnd->SetAnchor(m_NormStart);
            this->m_Visualizer.m_GuideTxtChainBase->SetAnchor(m_ChainBase);
            this->m_Visualizer.m_GuideTxtChainEnd->SetAnchor(m_ChainEnd);

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

    void CutChainSawFeedback::Activate()
    {
        Update();
        // m_Visualizer.Activate();
        if(m_ToShowCutPlane)
        {
            this->m_CutPlaneVisualizer.Activate();
        }
    }
 
    void CutChainSawFeedback::Deactivate()
    {
        this->m_Visualizer.Deactivate();

        this->m_CutPlaneVisualizer.Deactivate();
        this->m_Visualizer.m_AngleFeedVisualizer.Deactivate();
        this->m_Visualizer.m_DepthFeedVisualizer.Deactivate();

        this->m_CutOrientationVisualizer.Deactivate();
    }
}

