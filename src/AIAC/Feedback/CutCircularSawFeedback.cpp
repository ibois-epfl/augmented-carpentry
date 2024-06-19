//
// Created by ibois on 7/28/23.
//

#include "AIAC/Application.h"
#include "CutCircularSawFeedback.h"

#include <sstream>
#include <iomanip>


namespace AIAC
{
    CutCircularSawPositionStartVisualizer::CutCircularSawPositionStartVisualizer()
    {
        this->m_LineDistStart = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f), GOWeight::Thick);
        this->m_TxtDistStart = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));

        this->m_LineDistStart->SetColor(GOColor::YELLOW);
        this->m_TxtDistStart->SetColor(GOColor::WHITE);

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

        // m_AllPrimitives.push_back(m_LineFaceNormal);
        // m_AllPrimitives.push_back(m_LineBladeNormal);
        m_AllPrimitives.push_back(m_LinePitchFeed);
        m_AllPrimitives.push_back(m_GuideTxtRollPitch);

        Deactivate();
    }

    CutCircularSawFeedbackVisualizer::CutCircularSawFeedbackVisualizer()
    {
        m_BottomPoint = GOPoint::Add(GOPoint(0.f, 0.f, 0.f), 5.0f);
        m_LineToBottomPt = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_ProjLineOnFace = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_ProjLineOnFaceThickness = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_ProjLineOfBlade = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_TxtBottomDist = GOText::Add("0.0", GOPoint(0.f, 0.f, 0.f));

        m_ProjLineOnFace->SetWeight(GOWeight::Light);
        m_ProjLineOnFaceThickness->SetWeight(GOWeight::Light);

        m_BottomPoint->SetColor(GOColor::YELLOW);
        m_LineToBottomPt->SetColor(GOColor::YELLOW);
        m_ProjLineOnFace->SetColor(GOColor::RED);
        m_ProjLineOnFaceThickness->SetColor(GOColor::RED);
        m_ProjLineOfBlade->SetColor(GOColor::CYAN);
        m_TxtBottomDist->SetColor(GOColor::BLACK);

        m_TxtBottomDist->SetTextSize(GOTextSize::BitSmall);

        m_AllPrimitives.push_back(m_BottomPoint);
        m_AllPrimitives.push_back(m_LineToBottomPt);
        m_AllPrimitives.push_back(m_ProjLineOnFace);
        m_AllPrimitives.push_back(m_ProjLineOnFaceThickness);
        m_AllPrimitives.push_back(m_ProjLineOfBlade);
        m_AllPrimitives.push_back(m_TxtBottomDist);

        Deactivate();
    }

    void CutCircularSawFeedback::Update() {
        m_Cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);

        if(m_Cut->IsSingleFace()) {
            this->EnableCutPlane(true);
            m_GeneralVisualizer.Deactivate();
        }
        // else {
        //     this->EnableCutPlane(false);
        // }

        UpdateToolPosition();
        UpdateRefFaces();
        UpdateFeedback();
    }

    void CutCircularSawFeedback::Activate() {
        m_GeneralVisualizer.Activate();
        m_OrientationVisualizer.Activate();
        m_PositionStartVisualizer.Activate();
        Update();
    }

    void CutCircularSawFeedback::Deactivate() {
        m_GeneralVisualizer.Deactivate();
        m_CutPlaneVisualizer.Deactivate();
        m_OrientationVisualizer.Deactivate();
        m_PositionStartVisualizer.Deactivate();
    }

    void CutCircularSawFeedback::UpdateToolPosition() {
        m_Radius = AC_FF_TOOL->GetData<CircularSawData>().RadiusACIT;
        m_Center = AC_FF_TOOL->GetData<CircularSawData>().CenterGO->GetPosition();
        m_NormalStart = m_Center; // AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition(); // this value is not initialized
        m_NormalEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
        m_Normal = glm::normalize(m_NormalEnd - m_NormalStart);
    }

    void CutCircularSawFeedback::UpdateRefFaces()
    {
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
        if(nearestParallelFaceID.empty())
        {
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

    void CutCircularSawFeedback::UpdateFeedback() {
        if(!m_NearestPerpendicularFaceID.empty()){
            m_GeneralVisualizer.Activate();
            updateGeneralFeedback();
        }
        if(m_ToShowCutPlane) {
            m_CutPlaneVisualizer.Activate();
            updateCutPlaneFeedback();
        }
        if(m_Cut->IsSingleFace()) {
            m_GeneralVisualizer.Deactivate();
        }
    }

    void CutCircularSawFeedback::updateGeneralFeedback()
    {
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
        m_GeneralVisualizer.m_TxtBottomDist->SetAnchor(projBtmPt);
        auto dist = glm::distance(projBtmPt, m_BottomPoint);
        m_GeneralVisualizer.m_TxtBottomDist->SetText("d:" + FeedbackVisualizer::toString(dist));

        if(IsPointBetweenLineSeg(m_BottomPoint, m_Center, projBtmPt))
        {
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::BLACK);
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::BLACK);
        }
        else if (-1.f < glm::distance(m_BottomPoint, projBtmPt) < 1.f)
        {
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::GREEN);
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::GREEN);
        }
        else
        {
            dist = -dist;
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::RED);
            m_GeneralVisualizer.m_TxtBottomDist->SetColor(GOColor::RED);
        }

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

        // TODO: clean up values from import
        // Thicknesses >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        float bladeThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().ThicknessACIT;
        float overHangThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().OverhangACIT;
        float displacementTowardsCamera = bladeThicknessScaled;
        float displacementAwayFromCamera = bladeThicknessScaled - overHangThicknessScaled;
        glm::vec3 normalVec = glm::normalize(m_NormalEnd - m_NormalStart);
        glm::vec3 oppositeNormalVec = -(glm::normalize(m_NormalEnd - m_NormalStart));
        auto perpIntersectLineSegPt1TowardsCamera = perpIntersectLineSegPt1 + normalVec * displacementTowardsCamera;
        auto perpIntersectLineSegPt2TowardsCamera = perpIntersectLineSegPt2 + normalVec * displacementTowardsCamera;
        m_GeneralVisualizer.m_ProjLineOnFace->SetPts(perpIntersectLineSegPt1TowardsCamera, perpIntersectLineSegPt2TowardsCamera);
        auto perpIntersectLineSegPt1AwayFromCamera = perpIntersectLineSegPt1 + oppositeNormalVec * displacementAwayFromCamera;
        auto perpIntersectLineSegPt2AwayFromCamera = perpIntersectLineSegPt2 + oppositeNormalVec * displacementAwayFromCamera;
        m_GeneralVisualizer.m_ProjLineOnFaceThickness->SetPts(perpIntersectLineSegPt1AwayFromCamera, perpIntersectLineSegPt2AwayFromCamera);
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        //------------------------------------------------
        if (!this->m_NearestParallelFaceID.empty())
        {
            //the following is the update for the orientation feedback
            if (!m_Cut->IsSingleFace())
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

        // ---------------------------------------------------
            // starting point visualizer
        if (!this->m_NearestParallelFaceID.empty())
        {
            this->m_PositionStartVisualizer.Activate();

            auto faceInfo = this->m_Cut->GetFace(this->m_NearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projNormStart = GetProjectionPointOnPlane(faceNormal, faceCenter, m_NormalStart);
            glm::vec3 midPt = this->m_GeneralVisualizer.m_LineToBottomPt->GetMidPointValues();
            auto midPtProj = GetProjectionPointOnPlane(faceNormal, faceCenter, midPt);

            this->m_PositionStartVisualizer.m_LineDistStart->SetPts(midPt, midPtProj);
            float parallelDistMidPtPlane = glm::distance(midPt, midPtProj);
            this->m_PositionStartVisualizer.m_LineDistStart->SetColor(parallelDistMidPtPlane < 0.9f ? GOColor::GREEN : GOColor::YELLOW);

            std::ostringstream stream;
            stream << std::fixed << std::setprecision(1) << parallelDistMidPtPlane;
            std::string parallelDistMidPtPlaneStr = stream.str();
            this->m_PositionStartVisualizer.m_TxtDistStart->SetAnchor(midPtProj);
            this->m_PositionStartVisualizer.m_TxtDistStart->SetText("s:" + parallelDistMidPtPlaneStr);
            this->m_PositionStartVisualizer.m_TxtDistStart->SetColor(parallelDistMidPtPlane < 0.9f ? GOColor::GREEN : GOColor::YELLOW);
        }
        else
        {
            this->m_PositionStartVisualizer.Deactivate();
        }
    }

    void CutCircularSawFeedback::updateCutPlaneFeedback(){
        if(m_ToShowCutPlane) m_CutPlaneVisualizer.Update(m_Normal, m_Center);
    }
}