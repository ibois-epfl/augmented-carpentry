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

#include "AIAC/Application.h"
#include "CutChainSawFeedback.h"
#include "utils/GeometryUtils.h"

#include <sstream>
#include <iomanip>

namespace AIAC
{
    CutOrientationVisualizer::CutOrientationVisualizer()
    {
        // Normal face line 
        m_LineFaceNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineBladeNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugA = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugB = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugC = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugD = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugE = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LinePitchFeed = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f), GOWeight::MediumThick);
        m_GuideTxtRollPitch = GOText::Add("RollPitch", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtRollPitch->SetTextSize(GOTextSize::Average);

        m_LineFaceNormal->SetColor(GOColor::BLUE);
        m_LineBladeNormal->SetColor(GOColor::MAGENTA);
        m_LineDebugA->SetColor(GOColor::ORANGE);
        m_LineDebugB->SetColor(GOColor::GREEN);
        m_LineDebugC->SetColor(GOColor::RED);
        m_LineDebugD->SetColor(GOColor::YELLOW);
        m_LineDebugE->SetColor(GOColor::WHITE);
        m_LinePitchFeed->SetColor(GOColor::RED);
        m_GuideTxtRollPitch->SetColor(GOColor::WHITE);

        m_LineFaceNormal->SetVisibility(false);
        m_LineBladeNormal->SetVisibility(false);
        m_LineDebugA->SetVisibility(false);
        m_LineDebugB->SetVisibility(false);
        m_LineDebugC->SetVisibility(false);
        m_LineDebugD->SetVisibility(false);
        m_LineDebugE->SetVisibility(false);
        
        m_AllPrimitives.push_back(m_LinePitchFeed);
        m_AllPrimitives.push_back(m_GuideTxtRollPitch);

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

        m_LineEnd->SetWeight(GOWeight::Bold);
        m_LineChainBase->SetWeight(GOWeight::MediumThick);
        m_LineChainEnd->SetWeight(GOWeight::MediumThick);

        m_AllPrimitives.push_back(m_LineEnd);
        m_AllPrimitives.push_back(m_LineChainBase);
        m_AllPrimitives.push_back(m_LineChainEnd);

        Deactivate();
    }

    CutChainSawDepthFeedVisualizer::CutChainSawDepthFeedVisualizer()
    {
        // Line
        m_LineIntersect = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineIntersectThickness = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineDepthFaceEdge1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthFaceEdge2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineIntersect->SetWeight(GOWeight::Light);
        m_LineIntersectThickness->SetWeight(GOWeight::Light);

        m_LineIntersect->SetColor(GOColor::RED);
        m_LineIntersectThickness->SetColor(GOColor::RED);
        m_LineDepthFaceEdge1->SetColor(GOColor::YELLOW);
        m_LineDepthFaceEdge2->SetColor(GOColor::YELLOW);

        m_LineIntersect->SetWeight(GOWeight::Medium);
        m_LineIntersectThickness->SetWeight(GOWeight::Medium);
        m_LineDepthFaceEdge1->SetWeight(GOWeight::MediumThick);
        m_LineDepthFaceEdge2->SetWeight(GOWeight::MediumThick);

        m_AllPrimitives.push_back(m_LineIntersect);
        m_AllPrimitives.push_back(m_LineIntersectThickness);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge1);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge2);

        Deactivate();
    }

    CutChainSawFeedVisualizer::CutChainSawFeedVisualizer()
    {
        // Text
        m_GuideTxtChainBase = GOText::Add("ChainBase", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtFaceEdgeDepth = GOText::Add("FaceEdgeDepth2", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtChainBase->SetTextSize(GOTextSize::Small);
        m_GuideTxtFaceEdgeDepth->SetTextSize(GOTextSize::Average);

        m_GuideTxtChainBase->SetColor(GOColor::BLACK);
        m_GuideTxtFaceEdgeDepth->SetColor(GOColor::BLACK);

        m_AllPrimitives.push_back(m_GuideTxtChainBase);
        m_AllPrimitives.push_back(m_GuideTxtFaceEdgeDepth);

        Deactivate();
    }

    void CutChainSawFeedback::UpdateCutPlane ()
    {
        if(m_ToShowCutPlane) m_CutPlaneVisualizer.Update(m_NormalVec, m_NormStart);
    }

    void CutChainSawFeedback::UpdateRefFaces() {
        if (IsRefFacesSelectedManually) {
            // In manually selection mode, when the m_cut is switched, we have to update the face
            if (m_Cut->GetAllFaces().find(m_NearestParallelFaceID) == m_Cut->GetAllFaces().end()){
                m_NearestParallelFaceID = m_Cut->GetAllFaces().begin()->first;
            }

            // get the first closest neighbour face to the highlighted face as the perpendicular face
            // ** As we're limiting the cut to have maximum 3 faces, it doesn't really matter how to calculate.
            // the perpendicular plane. I think a better idea is to take the furthest neighbor of the nearest parallel
            // face or the face that maximum the length of the projection line formed by the m_ChainBase and m_ChainEnd.
            // However, since it's working, I'm not dare to touch it :3
            m_NearestPerpendicularFaceID = "";
            std::map<std::string, AIAC::TimberInfo::Cut::Face> neighbouringFaces =
                    this->m_Cut->GetFaceNeighbors(m_NearestParallelFaceID);
            float minDist = std::numeric_limits<float>::max();
            for (auto const& [faceID, faceInfo] : neighbouringFaces)
            {
                auto projCenter = GetProjectionPointOnPlane(
                        faceInfo.GetNormal(),
                        faceInfo.GetCenter(),
                        m_ChainMid);
                float distAbs = glm::abs(glm::distance(m_ChainMid, projCenter));
                if (distAbs < minDist)
                {
                    minDist = distAbs;
                    m_NearestPerpendicularFaceID = faceID;
                }
            }
        } else {
            // Find the nearest parallel/perpendicular face to highlight
            float nearestParallelFaceDist = 1e9f;
            float nearestPerpendicularFaceDist = 1e9f;
            std::vector<std::string> parallelFaceIDs;
            std::vector<std::string> perpendicularFaceIDs;

            for (auto const &[faceID, faceInfo]: m_Cut->GetAllFaces()) {
                if (faceInfo.IsExposed()) continue;
                auto faceNormal = faceInfo.GetNormal();
                auto theta = glm::acos(
                        glm::dot(faceNormal, m_NormalVec) / (glm::length(faceNormal) * glm::length(m_NormalVec)));

                auto distChainBase = glm::distance(faceInfo.GetCenter(), m_ChainBase);
                auto distChainEnd = glm::distance(faceInfo.GetCenter(), m_ChainEnd);
                auto totalDist = distChainBase + distChainEnd;

                // for parallel faces, find the nearest one
                auto threshold = 0.7853f; // 45 degrees
                if (theta < threshold || (3.14159 - theta) < threshold) {
                    parallelFaceIDs.push_back(faceID);
                    // update nearest parallel face
                    if (m_NearestParallelFaceID.empty() || totalDist < nearestParallelFaceDist) {
                        m_NearestParallelFaceID = faceID;
                        nearestParallelFaceDist = totalDist;
                    }
                } else {
                    perpendicularFaceIDs.push_back(faceID);
                    // update nearest perpendicular face
                    if (m_NearestPerpendicularFaceID.empty() || totalDist < nearestPerpendicularFaceDist) {
                        m_NearestPerpendicularFaceID = faceID;
                        nearestPerpendicularFaceDist = totalDist;
                    }
                }
            }
        }
    }

    void CutChainSawFeedback::ManuallyScrollRefFace(int scrollDirection) {
        auto iter = m_Cut->GetAllFaces().find(m_NearestParallelFaceID);

        // if scroll direction > 0 => goes to next, otherwise, goes back
        if (scrollDirection > 0) {
            iter++;
            if (iter == m_Cut->GetAllFaces().end()){
                iter = m_Cut->GetAllFaces().begin();
            }
        } else {
            if (iter == m_Cut->GetAllFaces().begin()){
                iter = m_Cut->GetAllFaces().end();
            }
            iter--;
        }

        m_NearestParallelFaceID = iter->first;

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

        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        auto& angleVisualizer = this->m_Visualizer.GetAngleFeedVisualizer();
        auto& depthVisualizer = this->m_Visualizer.GetDepthFeedVisualizer();

        if(m_ToShowCutPlane) UpdateCutPlane();
        
        // if it's a single face show the cutting plane
        if(m_Cut->IsSingleFace()) {
            this->EnableCutPlane(true);
        }

        this->UpdateRefFaces();

        // Highlight the face
        if (!m_Cut->IsSingleFace())
            m_Cut->HighlightFace(m_NearestParallelFaceID);

        // Update the m_Visualizer for the closest parallel face
        bool hasParallelFace = false, hasPerpendicularFace = false;

        double parallelEndDist = 0.0f;
        double parallelChainBaseDist = 0.0f;
        double perpendicularFaceEdge1Dist = 0.0f;
        double perpendicularFaceEdge2Dist = 0.0f;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2; // for depth text anchor

        // update angle visualizer
        if(!m_NearestParallelFaceID.empty())
        {
            hasParallelFace = true;
            angleVisualizer.Activate();

            // find the projection point of the three points on the face
            auto faceInfo = m_Cut->GetFace(m_NearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projNormStart = GetProjectionPointOnPlane(faceNormal, faceCenter, m_NormStart);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, m_ChainBase);

            // update the m_Visualizer
            angleVisualizer.m_LineChainBase->SetPts(m_ChainBase, projChainBase);
            parallelChainBaseDist = glm::distance(m_ChainBase, projChainBase);
            angleVisualizer.m_LineChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
        }
        else
        {
            angleVisualizer.Deactivate();
        }

        // extra orientation
        if (!m_NearestParallelFaceID.empty() or m_Cut->IsSingleFace())
        {
            m_CutOrientationVisualizer.Activate();

            // face and blade normal
            auto faceInfo = m_Cut->GetFace(m_NearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();
            m_CutOrientationVisualizer.m_LineFaceNormal->SetPts(faceCenter, faceCenter + faceNormal);

            auto bladeNormal = glm::normalize(m_NormEnd - m_NormStart);
            m_CutOrientationVisualizer.m_LineBladeNormal->SetPts(faceCenter, faceCenter + bladeNormal);

            // get the axis system of the face with the projection of the blade normal
            glm::vec3 zVec = glm::normalize(faceNormal);
            glm::vec3 xVec = glm::normalize(glm::cross(faceNormal, faceCenter));
            glm::vec3 yVec = glm::normalize(glm::cross(faceNormal, xVec));
            glm::vec3 bladeNormalProjOnFace = (m_NormEnd - m_NormStart) - glm::dot(m_NormEnd - m_NormStart, zVec) * zVec;

            xVec = glm::normalize(bladeNormalProjOnFace);
            yVec = glm::normalize(glm::cross(zVec, xVec));

            // draw the rotated x axis as a GOLine
            m_CutOrientationVisualizer.m_LineDebugB->SetPts(faceCenter, faceCenter + xVec);
            m_CutOrientationVisualizer.m_LineDebugC->SetPts(faceCenter, faceCenter + yVec);

            // draw the line between the end of the m_LineBladeNormal and the end of the lineDebugC
            float pitch = glm::degrees(atan2(bladeNormalProjOnFace.y, bladeNormalProjOnFace.z));
            m_CutOrientationVisualizer.m_LineDebugD->SetPts(
                m_CutOrientationVisualizer.m_LineBladeNormal->GetPEnd(),
                m_CutOrientationVisualizer.m_LineDebugB->GetPEnd());
            // draw the line between the end of the m_LineBladeNormal and the end of the lineDebugB
            m_CutOrientationVisualizer.m_LineDebugE->SetPts(
                m_CutOrientationVisualizer.m_LineBladeNormal->GetPEnd(),
                m_CutOrientationVisualizer.m_LineDebugC->GetPEnd());
            
            // calculare the angle between m_LineDebugE and m_LineDebugC (the pitch)
            float anglePitch = m_CutOrientationVisualizer.m_LineDebugD->ComputeSignedAngle(
                m_CutOrientationVisualizer.m_LineDebugB
                );
            float anglePitchDiffNeg = -45.0f - anglePitch;
            float anglePitchDiffPos = 45.0f - anglePitch;
            float anglePitchDiff = std::abs(anglePitchDiffNeg) < std::abs(anglePitchDiffPos) ? anglePitchDiffNeg : anglePitchDiffPos;
            anglePitchDiff = std::round(anglePitchDiff * 10) / 10;
            
            // Set the axis system on the blade
            glm::vec3 bladeZVec = glm::normalize(m_NormEnd - m_NormStart);
            glm::vec3 bladeXVec = glm::normalize(glm::cross(m_ChainMid - m_ChainBase, bladeZVec));
            glm::vec3 bladeYVec = glm::normalize(glm::cos(1.5708f) * bladeXVec + glm::sin(1.5708f) * bladeZVec);

            // Pitch guidance
            // show the degree difference in text
            m_CutOrientationVisualizer.m_GuideTxtRollPitch->SetAnchor(m_ChainMid + bladeYVec * 0.5f);
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(1) << anglePitchDiff;
            std::string anglePitchDiffStr = stream.str();
            m_CutOrientationVisualizer.m_GuideTxtRollPitch->SetText("r:" + anglePitchDiffStr +"°");
            if (anglePitchDiff > -m_CutOrientationVisualizer.m_tolAangleAcceptance && anglePitchDiff < m_CutOrientationVisualizer.m_tolAangleAcceptance)
                m_CutOrientationVisualizer.m_GuideTxtRollPitch->SetColor(GOColor::GREEN);
            else
                m_CutOrientationVisualizer.m_GuideTxtRollPitch->SetColor(GOColor::WHITE);
            
            // give a visual line feedback on the orientation
            if (anglePitchDiff > m_CutOrientationVisualizer.m_tolAangleAcceptance)
            {
                m_CutOrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::MAGENTA);
                m_CutOrientationVisualizer.m_LinePitchFeed->SetPts(m_ChainMid, m_ChainMid + bladeYVec * anglePitchDiff);
            }
            else if (anglePitchDiff < -m_CutOrientationVisualizer.m_tolAangleAcceptance)
            {
                m_CutOrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::RED);
                m_CutOrientationVisualizer.m_LinePitchFeed->SetPts(m_ChainMid, m_ChainMid + bladeYVec * anglePitchDiff);
            }
            else if (anglePitchDiff > -m_CutOrientationVisualizer.m_tolAangleAcceptance && anglePitchDiff < m_CutOrientationVisualizer.m_tolAangleAcceptance)
            {
                m_CutOrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::GREEN);
                m_CutOrientationVisualizer.m_LinePitchFeed->SetPts(m_ChainMid, m_ChainMid + bladeYVec * 0.3f);
            }

            // set the visibility off for the debug lines
            m_CutOrientationVisualizer.m_LinePitchFeed->SetVisibility(true);
            m_CutOrientationVisualizer.m_GuideTxtRollPitch->SetVisibility(true);

        }
        else
        {
            m_CutOrientationVisualizer.Deactivate();
        }

        // Perpendicular face
        if(!m_NearestPerpendicularFaceID.empty() and !m_Cut->IsSingleFace())
        {
            hasPerpendicularFace = true;

            // find the projection point of the 2 points on the face
            auto faceInfo = m_Cut->GetFace(m_NearestPerpendicularFaceID);
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
                auto edge = m_Cut->GetEdge(edgeID);
                auto edgePt1 = edge.GetStartPt().GetPosition();
                auto edgePt2 = edge.GetEndPt().GetPosition();
                ExtendLineSeg(edgePt1, edgePt2, 0.5f);
                glm::vec3 intersectPt;
                if(GetIntersectPointOfLineAndLineSeg(intersectLineVec, intersectLinePt, edgePt1, edgePt2, intersectPt)) {
                    intersectPts.push_back(intersectPt);
                }
            }
            FormLongestLineSeg(intersectPts, perpIntersectLineSegPt1, perpIntersectLineSegPt2);

            // FIXME: here we should intersect instead of translate the lines at the end
            // TODO: clean up the thickness section
            // Thicknesses >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            float bladeThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().ThicknessACIT;
            float overHangThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().OverhangACIT;
            float displacementTowardsCamera = overHangThicknessScaled;
            float displacementAwayFromCamera = bladeThicknessScaled - overHangThicknessScaled;

            // Lines based on tool
            auto projChainBase = GetNearestPtOnLine(intersectLineVec, intersectLinePt, m_ChainBase);
            auto projChainEnd = GetNearestPtOnLine(intersectLineVec, intersectLinePt, m_ChainEnd);
            glm::vec3 normalVec = glm::normalize(m_NormEnd - m_NormStart);
            auto projChainBaseTranslatedTwardsoCamera = projChainBase + normalVec * displacementTowardsCamera;
            auto projChainEndTranslatedTwardsoCamera = projChainEnd + normalVec * displacementTowardsCamera;
            depthVisualizer.m_LineIntersect->SetPts(projChainBaseTranslatedTwardsoCamera, projChainEndTranslatedTwardsoCamera);

            // depthVisualizer.m_LineIntersect->SetPts(projChainBase, projChainEnd);
            glm::vec3 oppositeNormalVec = -(glm::normalize(m_NormEnd - m_NormStart));
            auto projChainBaseTranslatedAwayFromCamera = projChainBase + oppositeNormalVec * displacementAwayFromCamera;
            auto projChainEndTranslatedAwayFromCamera = projChainEnd + oppositeNormalVec * displacementAwayFromCamera;
            depthVisualizer.m_LineIntersectThickness->SetPts(projChainBaseTranslatedAwayFromCamera, projChainEndTranslatedAwayFromCamera);
            // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

            // TODO: next is depth?? <<
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
                float scaleFactor = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
                float realPerpendicularFaceEdge1Dist = perpendicularFaceEdge1Dist / scaleFactor;
                float realPerpendicularFaceEdge2Dist = perpendicularFaceEdge2Dist / scaleFactor;

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

                // if the two guide lines have a close same distance than mark as yellow
                float diffPerpendicularFaceEdgeDist = std::abs(realPerpendicularFaceEdge1Dist - realPerpendicularFaceEdge2Dist);
                if(diffPerpendicularFaceEdgeDist < this->m_Visualizer.m_DistDepthAcceptance){
                    depthVisualizer.m_LineDepthFaceEdge1->SetColor(GOColor::GREEN);
                    depthVisualizer.m_LineDepthFaceEdge2->SetColor(GOColor::GREEN);
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

            this->m_Visualizer.m_GuideTxtChainBase->SetText("s:"+strChainBase);
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth->SetText("d:"+FeedbackVisualizer::toString(perpendicularFaceEdge2Dist));
            this->m_Visualizer.m_GuideTxtChainBase->SetAnchor(m_ChainBase);
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth->SetAnchor(perpIntersectLineSegPt1);

            auto endColor = GOColor::WHITE;
            auto chainBaseColor = GOColor::WHITE;
            auto chainEndColor = GOColor::WHITE;

            auto faceEdgeTxt1Color = GOColor::BLACK;
            auto faceEdgeTxt2Color = GOColor::BLACK;

            if(parallelEndDist != 0 && parallelEndDist < 0.5f){
                endColor = GOColor::GREEN;
            }
            if(parallelChainBaseDist != 0 && parallelChainBaseDist < 0.5f){
                chainBaseColor = GOColor::GREEN;
            }

            if(perpendicularFaceEdge1Dist > 0 && perpendicularFaceEdge1Dist < 0.5f){
                faceEdgeTxt1Color = GOColor::GREEN;
            } else if (perpendicularFaceEdge1Dist < 0){
                faceEdgeTxt1Color = GOColor::RED;
            }
            if(perpendicularFaceEdge2Dist > 0 && perpendicularFaceEdge2Dist < 0.5f){
                faceEdgeTxt2Color = GOColor::ORANGE;
            } else if (perpendicularFaceEdge2Dist < 0){
                faceEdgeTxt2Color = GOColor::RED;
            }

            this->m_Visualizer.m_GuideTxtChainBase->SetColor(chainBaseColor);
            this->m_Visualizer.m_GuideTxtFaceEdgeDepth->SetColor(faceEdgeTxt2Color);
        }
        else m_Visualizer.Deactivate();
    }

    void CutChainSawFeedback::Activate()
    {
        Update();
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

