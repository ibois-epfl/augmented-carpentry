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
#include "CutCircularSawFeedback.h"

#include <sstream>
#include <iomanip>
#include <climits> // For INT_MIN and INT_MAX
#include <cmath> // For std::isfinite☺


namespace AIAC
{
    CutCircularSawDepthVisualizer::CutCircularSawDepthVisualizer()
    {
        m_LineDepth = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_TxtDepth = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));
        m_PtBlade2ThicknessLineA = GOPoint::Add(GOPoint(0.f, 0.f, 0.f));
        m_PtBlade2ThicknessLineB = GOPoint::Add(GOPoint(0.f, 0.f, 0.f));

        m_LineDepth->SetColor(GOColor::PINK_TRANSP);
        m_TxtDepth->SetColor(GOColor::YELLOW);
        m_PtBlade2ThicknessLineA->SetColor(GOColor::PURPLE_TRANSP07);
        m_PtBlade2ThicknessLineB->SetColor(GOColor::PINK_TRANSP07);

        m_PtBlade2ThicknessLineA->SetWeight(GOWeight::MediumThick);
        m_PtBlade2ThicknessLineB->SetWeight(GOWeight::MediumThick);

        m_TxtDepth->SetTextSize(GOTextSize::BitSmall);

        m_AllPrimitives.push_back(m_LineDepth);
        m_AllPrimitives.push_back(m_TxtDepth);
        m_AllPrimitives.push_back(m_PtBlade2ThicknessLineA);
        m_AllPrimitives.push_back(m_PtBlade2ThicknessLineB);

        Deactivate();
    }

    CutCircularSawPositionStartVisualizer::CutCircularSawPositionStartVisualizer()
    {
        this->m_LineDistStart = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f), GOWeight::Thick);
        this->m_TxtDistStart = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));
        this->m_LineToBottomPt = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_LineDistStart->SetColor(GOColor::YELLOW);
        this->m_TxtDistStart->SetColor(GOColor::WHITE);
        this->m_LineToBottomPt->SetColor(GOColor::YELLOW);
        this->m_LineToBottomPt->SetVisibility(false);  // only for debugging

        this->m_TxtDistStart->SetTextSize(GOTextSize::BitSmall);

        this->m_AllPrimitives.push_back(m_LineDistStart);
        this->m_AllPrimitives.push_back(m_TxtDistStart);

        Deactivate();
    }

    CutCircularOrientationVisualizer::CutCircularOrientationVisualizer()
    {
        m_LineFaceNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineBladeNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugA = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugB = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugC = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugD = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDebugE = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LinePitchFeed = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f), GOWeight::ExtraThick);
        m_GuideTxtRollPitch = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));

        m_LineFaceNormal->SetColor(GOColor::BLUE);
        m_LineBladeNormal->SetColor(GOColor::MAGENTA);
        m_LineDebugA->SetColor(GOColor::ORANGE);
        m_LineDebugB->SetColor(GOColor::GREEN);
        m_LineDebugC->SetColor(GOColor::RED);
        m_LineDebugD->SetColor(GOColor::YELLOW);
        m_LineDebugE->SetColor(GOColor::WHITE);
        m_LinePitchFeed->SetColor(GOColor::RED);
        m_GuideTxtRollPitch->SetColor(GOColor::WHITE);

        m_GuideTxtRollPitch->SetTextSize(GOTextSize::BitSmall);

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

    void CutCircularSawFeedback::Update() {
        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);

        if(m_Cut->IsSingleFace()) {
            this->EnableCutPlane(true);
        }

        UpdateToolPosition();
        UpdateRefFaces();
        UpdateFeedback();
    }

    void CutCircularSawFeedback::Activate() {
        m_OrientationVisualizer.Activate();
        m_PositionStartVisualizer.Activate();
        m_ThicknessVisualizer.Activate();
        m_DepthVisualizer.Activate();
        Update();
    }

    void CutCircularSawFeedback::Deactivate() {
        m_CutPlaneVisualizer.Deactivate();
        m_OrientationVisualizer.Deactivate();
        m_PositionStartVisualizer.Deactivate();
        m_ThicknessVisualizer.Deactivate();
        m_DepthVisualizer.Deactivate();
    }

    void CutCircularSawFeedback::UpdateToolPosition() {
        m_Radius = AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        m_Center = AC_FF_TOOL->GetData<CircularSawData>().CenterGO->GetPosition();
        m_NormalStart = m_Center; // AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition(); // this value is not initialized
        m_NormalEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
        m_Normal = glm::normalize(m_NormalEnd - m_NormalStart);
    }

    void CutCircularSawFeedback::ManuallyScrollRefFace(int scrollDirection) {
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

    void CutCircularSawFeedback::UpdateRefFaces()
    {
        // --------------------------------------------------------------------
        // update the reference faces (parallel / perpendicular)
        if (IsRefFacesSelectedManually) {
            // In manually selection mode, when the m_cut is switched, we have to update the face
            if (m_Cut->GetAllFaces().find(m_NearestParallelFaceID) == m_Cut->GetAllFaces().end()){
                m_NearestParallelFaceID = m_Cut->GetAllFaces().begin()->first;
            }
        } else {
            // automatically determine the reference faces
            std::string nearestParallelFaceID;
            std::vector<std::pair<std::string, float>> allValidFaces;
            std::vector<std::pair<std::string, float>> perpenFaces;

            // get the distances to the blade circle
            for(auto const& [faceID, faceInfo]: m_Cut->GetAllFaces()){
                if (faceInfo.IsExposed()) continue;
                glm::vec3 ptOnCircleBlade = GOCircle::ClosestPointToCircle(
                        faceInfo.GetCenter(),
                        m_Center,
                        m_Normal,
                        m_Radius
                );
                auto dist = glm::abs(glm::distance(ptOnCircleBlade, faceInfo.GetCenter()));
                allValidFaces.push_back(std::make_pair(faceID, dist));
            }
            // filter the vector with an angle threshold, erase those elements in the vector that do not respect the check
            auto thresholdAngle = 0.7853f; // 45 degrees
            allValidFaces.erase(
                    std::remove_if(allValidFaces.begin(), allValidFaces.end(), [this, thresholdAngle](auto const& a){
                        auto faceInfo = m_Cut->GetFace(a.first);
                        auto faceNormal = faceInfo.GetNormal();
                        auto theta = glm::acos(
                                glm::dot(faceNormal, m_Normal) /
                                (glm::length(faceNormal) * glm::length(m_Normal))
                        );
                        return theta > thresholdAngle && (3.14159 - theta) > thresholdAngle;
                    }),
                    allValidFaces.end()
            );
            // reorder the faces by the abs distance
            std::sort(allValidFaces.begin(), allValidFaces.end(), [](auto const& a, auto const& b){
                return a.second < b.second;
            });
            // put the rest in the perpendicular faces
            for (auto const& [faceID, dist]: allValidFaces){
                if(faceID == nearestParallelFaceID) continue;
                perpenFaces.push_back(std::make_pair(faceID, dist));
            }
            // if it is the first time, nearestParallelFaceID.empty() gives the first face as the nearest parallel face
            nearestParallelFaceID = nearestParallelFaceID.empty() ? allValidFaces[0].first : nearestParallelFaceID;
            // sort perpendicular faces by distance
            std::sort(perpenFaces.begin(), perpenFaces.end(), [](auto const& a, auto const& b){
                return a.second < b.second;
            });

            // --------------------------------------------------------------------
            // update class members

            // Case 1: If the saw is place on the side for adjusting the height, there should be no parallel face
            // Therefore, the closest face would be considered as the face to be cut,
            // and the secondly closest face would be considered as the perpendicular surface that sits
            // at the bottom of the blade.
            // Case 2: During cut, everything is defined as normal
            if(nearestParallelFaceID.empty())
            {
                if(perpenFaces.size() < 2) {
                    // TODO: catch error
                    return;
                }
                m_NearestParallelFaceID = perpenFaces[0].first;
            } else {
                m_NearestParallelFaceID = nearestParallelFaceID;
            }
        }

        // --------------------------------------------------------------------
        // get the first and secondly closest neighbour face to the highlighted face and to the blade's center
        std::map<std::string, AIAC::TimberInfo::Cut::Face> neighbouringFaces = 
            this->m_Cut->GetFaceNeighbors(m_NearestParallelFaceID);
        float minDist = std::numeric_limits<float>::max();
        for (auto const& [faceID, faceInfo] : neighbouringFaces)
        {
            auto projCenter = GetProjectionPointOnPlane(
                faceInfo.GetNormal(),
                faceInfo.GetCenter(),
                m_Center);
            float distAbs = glm::abs(glm::distance(m_Center, projCenter));
            if (distAbs < minDist && distAbs > m_Radius)
            {
                minDist = distAbs;
                m_NearestNeighbourFaceIDToParallelFace = faceID;
            }
        }
        minDist = std::numeric_limits<float>::max();
        for (auto const& [faceID, faceInfo] : neighbouringFaces)
        {
            if (faceID == m_NearestNeighbourFaceIDToParallelFace) continue;
            auto projCenter = GetProjectionPointOnPlane(
                faceInfo.GetNormal(),
                faceInfo.GetCenter(),
                m_Center);
            float distAbs = glm::abs(glm::distance(m_Center, projCenter));
            if (distAbs < minDist && distAbs > m_Radius)
            {
                minDist = distAbs;
                m_SecondNearestNeighbourFaceIDToParallelFace = faceID;
            }
        }
    }

    void CutCircularSawFeedback::UpdateFeedback() {
        if(this->m_ToShowCutPlane || this->m_Cut->IsSingleFace())
        {
            this->m_CutPlaneVisualizer.Activate();
            UpdateCutPlaneFeedback();
        }
        else
            this->m_CutPlaneVisualizer.Deactivate();

        this->UpdateOrientationFeedback();
        this->UpdateThicknessFeedback();
        this->UpdateDepthFeedback();
        this->UpdateStartPosFeedback();
    }

    void CutCircularSawFeedback::UpdateOrientationFeedback()
    {
        if (!this->m_NearestParallelFaceID.empty())
        {
            this->m_Cut->HighlightFace(m_NearestParallelFaceID);
            auto faceInfo = m_Cut->GetFace(m_NearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();
            this->m_OrientationVisualizer.m_LineFaceNormal->SetPts(faceCenter, faceCenter + faceNormal);

            auto bladeNormal = glm::normalize(m_Normal);
            this->m_OrientationVisualizer.m_LineBladeNormal->SetPts(faceCenter, faceCenter + bladeNormal);

            // get the axis system of the face with the projection of the blade normal
            glm::vec3 zVec = glm::normalize(faceNormal);
            glm::vec3 xVec = glm::normalize(glm::cross(faceNormal, faceCenter));
            glm::vec3 yVec = glm::normalize(glm::cross(faceNormal, xVec));
            glm::vec3 bladeNormalProjOnFace = (m_NormalEnd - m_NormalStart) - glm::dot(m_NormalEnd - m_NormalStart, zVec) * zVec;

            xVec = glm::normalize(bladeNormalProjOnFace);
            yVec = glm::normalize(glm::cross(zVec, xVec));

            // draw the rotated x axis as a GOLine
            this->m_OrientationVisualizer.m_LineDebugB->SetPts(faceCenter, faceCenter + xVec);
            this->m_OrientationVisualizer.m_LineDebugC->SetPts(faceCenter, faceCenter + yVec);

            // draw the line between the end of the m_LineBladeNormal and the end of the lineDebugC
            float pitch = glm::degrees(atan2(bladeNormalProjOnFace.y, bladeNormalProjOnFace.z));
            this->m_OrientationVisualizer.m_LineDebugD->SetPts(
                this->m_OrientationVisualizer.m_LineBladeNormal->GetPEnd(),
                this->m_OrientationVisualizer.m_LineDebugB->GetPEnd());
            // draw the line between the end of the m_LineBladeNormal and the end of the lineDebugB
            this->m_OrientationVisualizer.m_LineDebugE->SetPts(
                this->m_OrientationVisualizer.m_LineBladeNormal->GetPEnd(),
                this->m_OrientationVisualizer.m_LineDebugC->GetPEnd());
            
            // calculare the angle between m_LineDebugE and m_LineDebugC (the pitch)
            float anglePitch = this->m_OrientationVisualizer.m_LineDebugD->ComputeSignedAngle(
                this->m_OrientationVisualizer.m_LineDebugB
                );
            float anglePitchDiffNeg = -45.0f - anglePitch;
            float anglePitchDiffPos = 45.0f - anglePitch;
            float anglePitchDiff = std::abs(anglePitchDiffNeg) < std::abs(anglePitchDiffPos) ? anglePitchDiffNeg : anglePitchDiffPos;
            anglePitchDiff = std::round(anglePitchDiff * 10) / 10;
            
            // Set the axis system on the blade
            glm::vec3 bladeZVec = glm::normalize(m_NormalEnd - m_NormalStart);
            glm::vec3 bladeXVec = glm::normalize(glm::cross(m_Center - m_BottomPoint, bladeZVec));
            glm::vec3 bladeYVec = glm::normalize(glm::cos(1.5708f) * bladeXVec + glm::sin(1.5708f) * bladeZVec);

            // Pitch guidance
            // show the degree difference in text
            this->m_OrientationVisualizer.m_GuideTxtRollPitch->SetAnchor(m_Center + bladeYVec * 0.5f);
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(1) << anglePitchDiff;
            std::string anglePitchDiffStr = stream.str();
            this->m_OrientationVisualizer.m_GuideTxtRollPitch->SetText("r:" + anglePitchDiffStr);
            if (anglePitchDiff > -this->m_OrientationVisualizer.m_tolAangleAcceptance && anglePitchDiff < this->m_OrientationVisualizer.m_tolAangleAcceptance)
                this->m_OrientationVisualizer.m_GuideTxtRollPitch->SetColor(GOColor::GREEN);
            else
                this->m_OrientationVisualizer.m_GuideTxtRollPitch->SetColor(GOColor::WHITE);
            
            // give a visual line feedback on the orientation
            if (anglePitchDiff > this->m_OrientationVisualizer.m_tolAangleAcceptance)
            {
                this->m_OrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::MAGENTA);
                this->m_OrientationVisualizer.m_LinePitchFeed->SetPts(m_Center, m_Center + bladeYVec * anglePitchDiff);
            }
            else if (anglePitchDiff < -this->m_OrientationVisualizer.m_tolAangleAcceptance)
            {
                this->m_OrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::RED);
                this->m_OrientationVisualizer.m_LinePitchFeed->SetPts(m_Center, m_Center + bladeYVec * anglePitchDiff);
            }
            else if (anglePitchDiff > -this->m_OrientationVisualizer.m_tolAangleAcceptance && anglePitchDiff < this->m_OrientationVisualizer.m_tolAangleAcceptance)
            {
                this->m_OrientationVisualizer.m_LinePitchFeed->SetColor(GOColor::GREEN);
                this->m_OrientationVisualizer.m_LinePitchFeed->SetPts(m_Center, m_Center + bladeYVec * 0.3f);
            }

            // set the visibility off for the debug lines
            this->m_OrientationVisualizer.m_LineFaceNormal->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineBladeNormal->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineDebugA->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineDebugB->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineDebugC->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineDebugD->SetVisibility(false);
            this->m_OrientationVisualizer.m_LineDebugE->SetVisibility(false);
            this->m_OrientationVisualizer.m_LinePitchFeed->SetVisibility(true);
            this->m_OrientationVisualizer.m_GuideTxtRollPitch->SetVisibility(true);
        }
        else
        {
            this->m_OrientationVisualizer.Deactivate();
        }

    }

    void CutCircularSawFeedback::UpdateCutPlaneFeedback()
    {
        if(m_ToShowCutPlane) m_CutPlaneVisualizer.Update(m_Normal, m_Center);
    }

    void CircularSawCutBladeThicknessVisualizer::UpdateToolheadsData()
    {
        this->m_BladeTotalThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().ThicknessACIT;
        this->m_BladeOverhangScaled = AC_FF_TOOL->GetData<CircularSawData>().OverhangACIT;
        this->m_ToolheadRefCenter = AC_FF_TOOL->GetData<CircularSawData>().CenterGO->GetPosition();
        this->m_ToolheadRefNormStart = this->m_ToolheadRefCenter;
        this->m_ToolheadRefNormEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
        this->m_NormalUnitized = glm::normalize(this->m_ToolheadRefNormEnd - this->m_ToolheadRefNormStart);
        this->m_NormalOppositeUnitized = -this->m_NormalUnitized;
        this->m_DisplacedCenterTowardsCamera = this->m_ToolheadRefCenter + this->m_NormalUnitized * this->m_BladeOverhangScaled;
        this->m_DisplacedCenterAwayFromCamera = this->m_ToolheadRefCenter + this->m_NormalOppositeUnitized * (this->m_BladeTotalThicknessScaled - this->m_BladeOverhangScaled);
    }

    bool CircularSawCutBladeThicknessVisualizer::IntersectBladeWithNeighbours(
        TimberInfo::Cut* cut,
        TimberInfo::Cut::Face& face,
        bool isTowardsCamera,
        bool isDetectToolPlane,
        std::shared_ptr<GOLine>& lineIntersection)
    {
        glm::vec3 centerBlade;
        glm::vec3 normalBlade;
        if (!isDetectToolPlane)
        {
            if (isTowardsCamera)
            {
                normalBlade = this->m_NormalUnitized;
                centerBlade = this->m_DisplacedCenterTowardsCamera;
            }
            else
            {
                normalBlade = this->m_NormalOppositeUnitized;
                centerBlade = this->m_DisplacedCenterAwayFromCamera;
            }
        }
        else
        {
            normalBlade = this->m_NormalUnitized;
            centerBlade = this->m_ToolheadRefCenter;
        }
        glm::vec3 downVecBlade;
        auto prepFaceACenter = face.GetCenter();
        auto perpFaceANormal = face.GetNormal();
        glm::vec3 perpFaceOfBladeVec = glm::normalize(glm::cross(normalBlade, perpFaceANormal));
        glm::vec3 _ptPlaceHolder;
        GetIntersectLineOf2Planes(
            normalBlade,
            centerBlade,
            perpFaceOfBladeVec,
            centerBlade,
            downVecBlade,
            _ptPlaceHolder
        );

        auto sidePt1 = centerBlade + perpFaceOfBladeVec * AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        auto sidePt2 = centerBlade - perpFaceOfBladeVec * AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        glm::vec3 projSidePt1, projSidePt2;
        GetIntersectPointOfLineAndPlane(downVecBlade, sidePt1, perpFaceANormal, prepFaceACenter, projSidePt1);
        GetIntersectPointOfLineAndPlane(downVecBlade, sidePt2, perpFaceANormal, prepFaceACenter, projSidePt2);
        if (projSidePt1 == projSidePt2)
        {
            lineIntersection->SetPts(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
            return false;
        }

        std::vector<glm::vec3> intersectPts;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2;
        for(auto const& edgeID: face.GetEdges()){
            auto edge = cut->GetEdge(edgeID);
            auto edgePt1 = edge.GetStartPt().GetPosition();
            auto edgePt2 = edge.GetEndPt().GetPosition();
            ExtendLineSeg(edgePt1, edgePt2, 1.0f);
            glm::vec3 intersectPt;
            if(GetIntersectPointOfLineAndLineSeg((projSidePt2 - projSidePt1), projSidePt1, edgePt1, edgePt2, intersectPt)) {
                intersectPts.push_back(intersectPt);
            }
        }
        FormLongestLineSeg(intersectPts, perpIntersectLineSegPt1, perpIntersectLineSegPt2);

        if (intersectPts.size() == 0)
        {
            lineIntersection->SetPts(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
            return false;
        }
        lineIntersection->SetPts(perpIntersectLineSegPt1, perpIntersectLineSegPt2);
        return true;
    }

    void CutCircularSawFeedback::UpdateThicknessFeedback()
    {
        this->m_ThicknessVisualizer.Deactivate();
        this->m_ThicknessVisualizer.UpdateToolheadsData();
        
        std::map<std::string, AIAC::TimberInfo::Cut::Face> neighbouringFaces = 
            this->m_Cut->GetHighlightedFaceNeighbors();
        if (neighbouringFaces.size() > 2)
        {
            AIAC_WARN("The neighbouring faces are more than 2, this is not possible to show the thickness feedback");
            return;
        }

        AIAC::TimberInfo::Cut::Face faceNeighbour1 = this->m_Cut->GetFace(this->m_NearestNeighbourFaceIDToParallelFace);
        if (neighbouringFaces.size() == 1)
        {
            bool isfaceNeighbour1Intersected = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, true, true, this->m_ThicknessVisualizer.m_LongestIntersectSegmenDetectToolPlane);
            bool isfaceNeighbour1IntersectedOnce = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, true, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraA);
            bool isfaceNeighbour1IntersectedTwice = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, false, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraA);

            if (this->m_ThicknessVisualizer.IsSegmenDetectToolPlaneVisible)
                this->m_ThicknessVisualizer.m_LongestIntersectSegmenDetectToolPlane->SetVisibility(isfaceNeighbour1Intersected);
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraA->SetVisibility((isfaceNeighbour1IntersectedOnce && isfaceNeighbour1IntersectedTwice));
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraA->SetVisibility((isfaceNeighbour1IntersectedOnce && isfaceNeighbour1IntersectedTwice));
        }
        else if (neighbouringFaces.size() == 2)
        {
            AIAC::TimberInfo::Cut::Face faceNeighbour2 = this->m_Cut->GetFace(this->m_SecondNearestNeighbourFaceIDToParallelFace);
            bool isfaceNeighbour1Intersected = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, true, true, this->m_ThicknessVisualizer.m_LongestIntersectSegmenDetectToolPlane);
            bool isfaceNeighbour1IntersectedOnce = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, true, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraA);
            bool isfaceNeighbour1IntersectedTwice = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour1, false, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraA);
            bool isfaceNeighbour2IntersectedOnce = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour2, true, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraB);
            bool isfaceNeighbour2IntersectedTwice = this->m_ThicknessVisualizer.IntersectBladeWithNeighbours(
                this->m_Cut, faceNeighbour2, false, false, this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraB);

            if (this->m_ThicknessVisualizer.IsSegmenDetectToolPlaneVisible)
                this->m_ThicknessVisualizer.m_LongestIntersectSegmenDetectToolPlane->SetVisibility(isfaceNeighbour1Intersected);
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraA->SetVisibility((isfaceNeighbour1IntersectedOnce && isfaceNeighbour1IntersectedTwice));
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraA->SetVisibility((isfaceNeighbour1IntersectedOnce && isfaceNeighbour1IntersectedTwice));
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraB->SetVisibility((isfaceNeighbour2IntersectedOnce && isfaceNeighbour2IntersectedTwice));
            this->m_ThicknessVisualizer.m_LongestIntersectSegmentAwayFromCameraB->SetVisibility((isfaceNeighbour2IntersectedOnce && isfaceNeighbour2IntersectedTwice));
        }
        else
        {
            this->m_ThicknessVisualizer.Deactivate();
        }
    }

    void CutCircularSawFeedback::UpdateStartPosFeedback()
    {
        if (!this->m_NearestParallelFaceID.empty())
        {
            this->m_PositionStartVisualizer.Activate();

            AIAC::TimberInfo::Cut::Face faceInfo = this->m_Cut->GetFace(this->m_NearestParallelFaceID);
            glm::vec3 faceNormal = faceInfo.GetNormal();
            glm::vec3 faceCenter = faceInfo.GetCenter();

            // closest displaced center of the blade (towards or away from the camera)
            glm::vec3 projBladeNorm;
            glm::vec3 centerBlade;
            glm::vec3 projBladeCenterTowards2Face = GetProjectionPointOnPlane(
                faceNormal,
                faceCenter,
                this->m_ThicknessVisualizer.m_DisplacedCenterTowardsCamera
            );
            glm::vec3 projBladeCenterAway2Face = GetProjectionPointOnPlane(
                faceNormal,
                faceCenter,
                this->m_ThicknessVisualizer.m_DisplacedCenterAwayFromCamera
            );
            // get the closest one
            float distTowards = glm::abs(glm::distance(this->m_ThicknessVisualizer.m_DisplacedCenterTowardsCamera, projBladeCenterTowards2Face));
            float distAway = glm::abs(glm::distance(this->m_ThicknessVisualizer.m_DisplacedCenterAwayFromCamera, projBladeCenterAway2Face));
            if (distTowards < distAway)
            {
                projBladeNorm = projBladeCenterTowards2Face;
                centerBlade = this->m_ThicknessVisualizer.m_DisplacedCenterTowardsCamera;
            }
            else
            {
                projBladeNorm = projBladeCenterAway2Face;
                centerBlade = this->m_ThicknessVisualizer.m_DisplacedCenterAwayFromCamera;
            }
            // calculate the distance
            glm::vec3 centerBladeProjOnFace = GetProjectionPointOnPlane(
                faceNormal,
                faceCenter,
                centerBlade);
            float parallelDistCtrBlade2PtFace = glm::distance(
                centerBlade,
                centerBladeProjOnFace);

            ////////////////////////////////////////////////////////
            // Visualization
            ////////////////////////////////////////////////////////
            // set the visuals and print the distance feed
            // move the center down of half the radius
            auto prepFaceInfo = m_Cut->GetFace(this->m_NearestNeighbourFaceIDToParallelFace);
            auto prepPlnCenter = prepFaceInfo.GetCenter();
            auto perpPlnNormal = prepFaceInfo.GetNormal();
            glm::vec3 perpFaceOfBladeVec = glm::normalize(glm::cross(m_Normal, perpPlnNormal));
            glm::vec3 _ptPlaceHolder;
            GetIntersectLineOf2Planes(
                m_Normal, m_Center,
                perpFaceOfBladeVec, m_Center,
                m_DownVec, _ptPlaceHolder
            );

            if(glm::distance(m_Center + m_DownVec * m_Radius, faceInfo.GetCenter()) >
            glm::distance(m_Center - m_DownVec * m_Radius, faceInfo.GetCenter())){
                m_DownVec = -m_DownVec;
            }

            // get the bottom point and update
            glm::vec3 bottomPoint = m_Center + m_DownVec * m_Radius;
            this->m_PositionStartVisualizer.m_LineToBottomPt->SetPts(m_Center, bottomPoint);
            ////////////////////////////

            // set the visuals and print the distance feed
            glm::vec3 midPt = this->m_PositionStartVisualizer.m_LineToBottomPt->GetMidPointValues();
            glm::vec3 midPtProj = GetProjectionPointOnPlane(
                faceNormal,
                faceCenter,
                midPt);
            this->m_PositionStartVisualizer.m_LineDistStart->SetPts(
                midPt,
                midPtProj);

            std::ostringstream stream;
            stream << std::fixed << std::setprecision(1) << parallelDistCtrBlade2PtFace;
            std::string parallelDistCtrBlade2PtFaceStr = stream.str();
            this->m_PositionStartVisualizer.m_TxtDistStart->SetAnchor(
                midPtProj
                );
            this->m_PositionStartVisualizer.m_TxtDistStart->SetText("s:" + parallelDistCtrBlade2PtFaceStr);
            this->m_PositionStartVisualizer.m_TxtDistStart->SetColor(
                parallelDistCtrBlade2PtFace < this->m_PositionStartVisualizer.ToleranceStartThreshold ? GOColor::GREEN : GOColor::YELLOW);
            this->m_PositionStartVisualizer.m_LineDistStart->SetColor(
                parallelDistCtrBlade2PtFace < this->m_PositionStartVisualizer.ToleranceStartThreshold ? GOColor::GREEN : GOColor::YELLOW);
        }
        else
        {
            this->m_PositionStartVisualizer.Deactivate();
        }
    }

    void CutCircularSawFeedback::UpdateDepthFeedback()
    {
        if (!this->m_NearestParallelFaceID.empty() && !m_Cut->IsSingleFace())
        {
            // calculate distances (closest point to line/segment to circle)
            float distLineDepth = GOCircle::ClosestDistanceFromLineToCircle(
            this->m_ThicknessVisualizer.m_LongestIntersectSegmenDetectToolPlane,
                m_Center,
                m_Radius
            );
            std::pair<float, std::pair<glm::vec3, glm::vec3>> res = GOCircle::ClosestDistanceFromSegmentToCircle(
                this->m_ThicknessVisualizer.m_LongestIntersectSegmentTowardsCameraA,
                m_Center,
                m_Radius
            );
            float distSegDepth = res.first;
            float distLineDepthAbs = glm::abs(distLineDepth);
            float distSegDepthAbs = glm::abs(distSegDepth);

            // visualization
            auto prepFaceInfo = m_Cut->GetFace(this->m_NearestNeighbourFaceIDToParallelFace);
            auto prepPlnCenter = prepFaceInfo.GetCenter();
            auto perpPlnNormal = prepFaceInfo.GetNormal();
            auto projBladeCenter = GetProjectionPointOnPlane(
                perpPlnNormal,
                prepPlnCenter,
                m_Center);
            this->m_DepthVisualizer.m_TxtDepth->SetAnchor(projBladeCenter);
            this->m_DepthVisualizer.m_LineDepth->SetPts(m_Center, projBladeCenter);

            this->m_DepthVisualizer.m_TxtDepth->SetText(
                "d:" + FeedbackVisualizer::toString(distLineDepth) +
                "|" + FeedbackVisualizer::toString(distSegDepthAbs) + ""
                );
            if (std::isfinite(distLineDepth) && distLineDepth > static_cast<float>(INT_MIN) && distLineDepth < static_cast<float>(INT_MAX))
            {
                if (distLineDepthAbs < this->m_DepthVisualizer.m_ToleranceDepthThreshold)
                    this->m_DepthVisualizer.m_TxtDepth->SetColor(GOColor::GREEN);
                else if (distLineDepthAbs < this->m_DepthVisualizer.m_ToleranceDepthThreshold * 20)
                    this->m_DepthVisualizer.m_TxtDepth->SetColor(GOColor::YELLOW);
                else
                    this->m_DepthVisualizer.m_TxtDepth->SetColor(GOColor::RED);
            }
            else
            {
                this->m_DepthVisualizer.m_TxtDepth->SetText("///");
                this->m_DepthVisualizer.m_TxtDepth->SetColor(GOColor::MAGENTA);
            }


            this->m_DepthVisualizer.m_PtBlade2ThicknessLineA->SetPosition(res.second.first);
            this->m_DepthVisualizer.m_PtBlade2ThicknessLineB->SetPosition(res.second.second);


        }
        else
        {
            this->m_DepthVisualizer.Deactivate();
        }
    }

}