#include "AIAC/Application.h"
#include "FabFeedback.h"
#include "CutPlaneVisualizer.h"

namespace AIAC
{
    CutPlaneVisualizer::CutPlaneVisualizer(){
        m_LongestIntersectSegmentAppCenterA = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LongestIntersectSegmentA1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LongestIntersectSegmentA2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LongestIntersectSegmentAppCenterB = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LongestIntersectSegmentB1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LongestIntersectSegmentB2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LongestIntersectSegmentB1->SetWeight(GOWeight::Light);
        m_LongestIntersectSegmentB2->SetWeight(GOWeight::Light);
        m_LongestIntersectSegmentA1->SetWeight(GOWeight::Light);
        m_LongestIntersectSegmentA2->SetWeight(GOWeight::Light);

        m_LongestIntersectSegmentAppCenterA->SetColor(AIAC::GOColor::CYAN);
        m_LongestIntersectSegmentA1->SetColor(AIAC::GOColor::MAGENTA);
        m_LongestIntersectSegmentA2->SetColor(AIAC::GOColor::MAGENTA);
        m_LongestIntersectSegmentAppCenterB->SetColor(AIAC::GOColor::CYAN);
        m_LongestIntersectSegmentB1->SetColor(AIAC::GOColor::MAGENTA);
        m_LongestIntersectSegmentB2->SetColor(AIAC::GOColor::MAGENTA);

        m_AllPrimitives.push_back(m_LongestIntersectSegmentAppCenterA);
        m_AllPrimitives.push_back(m_LongestIntersectSegmentA1);
        m_AllPrimitives.push_back(m_LongestIntersectSegmentA2);
        m_AllPrimitives.push_back(m_LongestIntersectSegmentAppCenterB);
        m_AllPrimitives.push_back(m_LongestIntersectSegmentB1);
        m_AllPrimitives.push_back(m_LongestIntersectSegmentB2);

        Deactivate();
    }

    void CutPlaneVisualizer::ReorderIntersectPoints(std::vector<glm::vec3>& intersectPts, const glm::vec3& facePt)
    {
        // Reorder intersect points based on angles
        auto vec0 = intersectPts[0] - intersectPts[3];
        auto vec1 = intersectPts[1] - intersectPts[3];
        auto vec2 = intersectPts[2] - intersectPts[3];
        auto angle01 = GetAngleBetweenVectors(vec0, vec1);
        auto angle02 = GetAngleBetweenVectors(vec0, vec2);
        auto angle12 = GetAngleBetweenVectors(vec1, vec2);
        if (angle01 > angle02 && angle01 > angle12) {  // 0 2 1 --- 3 => swap 1 and 2
            std::swap(intersectPts[1], intersectPts[2]);
        } else if (angle12 > angle01 && angle12 > angle02) { // 1 0 2 --- 3 => swap 0 and 1
            std::swap(intersectPts[0], intersectPts[1]);
        }

        // Calculate midpoints of segments
        glm::vec3 m_SegmentMid1 = (intersectPts[0] + intersectPts[1]) / 2.0f;
        glm::vec3 m_SegmentMid2 = (intersectPts[1] + intersectPts[2]) / 2.0f;
        glm::vec3 m_SegmentMid3 = (intersectPts[2] + intersectPts[3]) / 2.0f;
        glm::vec3 m_SegmentMid4 = (intersectPts[3] + intersectPts[0]) / 2.0f;

        // Calculate distances from face point to midpoints
        glm::vec3 facePtToMid1 = m_SegmentMid1 - facePt;
        glm::vec3 facePtToMid2 = m_SegmentMid2 - facePt;
        glm::vec3 facePtToMid3 = m_SegmentMid3 - facePt;
        glm::vec3 facePtToMid4 = m_SegmentMid4 - facePt;
        float dist1 = glm::length(facePtToMid1);
        float dist2 = glm::length(facePtToMid2);
        float dist3 = glm::length(facePtToMid3);
        float dist4 = glm::length(facePtToMid4);
    }

    void CutPlaneVisualizer::CutPlaneVisualizer::Activate(){
        FeedbackVisualizer::Activate();
    }

    void CutPlaneVisualizer::CutPlaneVisualizer::Deactivate(){
        FeedbackVisualizer::Deactivate();
        for (auto &p : m_AllPrimitives) {
            p->SetVisibility(false);
        }
    }

    std::vector<glm::vec3> CutPlaneVisualizer::Update(glm::vec3 faceNorm, glm::vec3 facePt){
        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);

        // getting the scanned model bounding box and its edges indices
        auto bbox = AIAC_APP.GetLayer<LayerModel>()->GetScannedModel().GetBoundingBox();
        auto bboxIndices = AIAC_APP.GetLayer<LayerModel>()->GetScannedModel().GetBboxEdgesIndices();
        
        // current tool type and its normal
        auto currentToolType = AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolheadType();
        glm::vec3 normStart;
        glm::vec3 normEnd;
        if (currentToolType == ACToolHeadType::CHAINSAW) {
            normStart = AC_FF_TOOL->GetData<ChainSawData>().NormStartGO->GetPosition();
            normEnd = AC_FF_TOOL->GetData<ChainSawData>().NormEndGO->GetPosition();
        } else if (currentToolType == ACToolHeadType::CIRCULARSAW) {
            normStart = AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition();
            normEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
        }

        // translate the facePt and faceNorm with the thickness of the blade
        float bladeThicknessScaled;
        float overHangThicknessScaled;
        if (currentToolType == ACToolHeadType::CHAINSAW) {
            bladeThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().ThicknessACIT;
            overHangThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().OverhangACIT;
        } else if (currentToolType == ACToolHeadType::CIRCULARSAW) {
            bladeThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().ThicknessACIT;
            overHangThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().OverhangACIT;
        }
        glm::vec3 normalVec = glm::normalize(normEnd - normStart);
        glm::vec3 oppositeNormalVec = -normalVec;
        float displacementTowardsCamera = overHangThicknessScaled;
        float displacementAwayFromCamera = bladeThicknessScaled - overHangThicknessScaled;
        glm::vec3 displacementTowardsCameraVec = displacementTowardsCamera * normalVec;
        glm::vec3 displacementAwayFromCameraVec = displacementAwayFromCamera * oppositeNormalVec;

        glm::vec3 facePtTowardsCamera = facePt + displacementTowardsCameraVec;
        glm::vec3 facePtAwayFromCamera = facePt + displacementAwayFromCameraVec;

        std::vector<glm::vec3> intersectPtsTowardsCamera;
        std::vector<glm::vec3> intersectPtsAwayFromCamera;
        std::vector<glm::vec3> intersectPts;
        for(auto [i, j] : bboxIndices)
        {
            glm::vec3 intersectPt;
            if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePt, intersectPt)){
                intersectPts.push_back(intersectPt);
            }
            glm::vec3 intersectPtTC;
            if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePtTowardsCamera, intersectPtTC)){
                intersectPtsTowardsCamera.push_back(intersectPtTC);
            }
            glm::vec3 intersectPtAC;
            if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePtAwayFromCamera, intersectPtAC)){
                intersectPtsAwayFromCamera.push_back(intersectPtAC);
            }
        }

        if (intersectPts.size() != 4
        || intersectPtsTowardsCamera.size() != 4
        || intersectPtsAwayFromCamera.size() != 4) {
            return std::vector<glm::vec3>();
        }

        this->ReorderIntersectPoints(intersectPts, facePt);
        this->ReorderIntersectPoints(intersectPtsTowardsCamera, facePtTowardsCamera);
        this->ReorderIntersectPoints(intersectPtsAwayFromCamera, facePtAwayFromCamera);


        // get the closest segment to the toolhead's face point
        glm::vec3 m_SegmentMid1 = (intersectPts[0] + intersectPts[1]) / 2.0f;
        glm::vec3 m_SegmentMid2 = (intersectPts[1] + intersectPts[2]) / 2.0f;
        glm::vec3 m_SegmentMid3 = (intersectPts[2] + intersectPts[3]) / 2.0f;
        glm::vec3 m_SegmentMid4 = (intersectPts[3] + intersectPts[0]) / 2.0f;
        glm::vec3 facePtToMid1 = m_SegmentMid1 - facePt;
        glm::vec3 facePtToMid2 = m_SegmentMid2 - facePt;
        glm::vec3 facePtToMid3 = m_SegmentMid3 - facePt;
        glm::vec3 facePtToMid4 = m_SegmentMid4 - facePt;
        float dist1 = glm::length(facePtToMid1);
        float dist2 = glm::length(facePtToMid2);
        float dist3 = glm::length(facePtToMid3);
        float dist4 = glm::length(facePtToMid4);

        glm::vec3 closestMidPt;

        if (dist1 < dist2 && dist1 < dist3 && dist1 < dist4) {
            closestMidPt = m_SegmentMid1;
            m_LongestIntersectSegmentAppCenterA->SetPts(intersectPts[0], intersectPts[1]);
            m_LongestIntersectSegmentA1->SetPts(intersectPtsTowardsCamera[0], intersectPtsTowardsCamera[1]);
            m_LongestIntersectSegmentA2->SetPts(intersectPtsAwayFromCamera[0], intersectPtsAwayFromCamera[1]);
            // find the closest between 2 and 4
            if (dist2 < dist4) {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[1], intersectPts[2]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[1], intersectPtsTowardsCamera[2]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[1], intersectPtsAwayFromCamera[2]);
            } else {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[3], intersectPts[0]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[3], intersectPtsTowardsCamera[0]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[3], intersectPtsAwayFromCamera[0]);
            }
        } else if (dist2 < dist1 && dist2 < dist3 && dist2 < dist4) {
            closestMidPt = m_SegmentMid2;
            m_LongestIntersectSegmentAppCenterA->SetPts(intersectPts[1], intersectPts[2]);
            m_LongestIntersectSegmentA1->SetPts(intersectPtsTowardsCamera[1], intersectPtsTowardsCamera[2]);
            m_LongestIntersectSegmentA2->SetPts(intersectPtsAwayFromCamera[1], intersectPtsAwayFromCamera[2]);
            if (dist1 < dist3) {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[0], intersectPts[1]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[0], intersectPtsTowardsCamera[1]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[0], intersectPtsAwayFromCamera[1]);
            } else {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[2], intersectPts[3]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[2], intersectPtsTowardsCamera[3]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[2], intersectPtsAwayFromCamera[3]);
            }
        } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4) {
            closestMidPt = m_SegmentMid3;
            m_LongestIntersectSegmentAppCenterA->SetPts(intersectPts[2], intersectPts[3]);
            m_LongestIntersectSegmentA1->SetPts(intersectPtsTowardsCamera[2], intersectPtsTowardsCamera[3]);
            m_LongestIntersectSegmentA2->SetPts(intersectPtsAwayFromCamera[2], intersectPtsAwayFromCamera[3]);
            if (dist2 < dist4) {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[1], intersectPts[2]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[1], intersectPtsTowardsCamera[2]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[1], intersectPtsAwayFromCamera[2]);
            } else {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[3], intersectPts[0]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[3], intersectPtsTowardsCamera[0]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[3], intersectPtsAwayFromCamera[0]);
            }
        } else {
            closestMidPt = m_SegmentMid4;
            m_LongestIntersectSegmentAppCenterA->SetPts(intersectPts[3], intersectPts[0]);
            m_LongestIntersectSegmentA1->SetPts(intersectPtsTowardsCamera[3], intersectPtsTowardsCamera[0]);
            m_LongestIntersectSegmentA2->SetPts(intersectPtsAwayFromCamera[3], intersectPtsAwayFromCamera[0]);
            if (dist1 < dist3) {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[0], intersectPts[1]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[0], intersectPtsTowardsCamera[1]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[0], intersectPtsAwayFromCamera[1]);
            } else {
                m_LongestIntersectSegmentAppCenterB->SetPts(intersectPts[2], intersectPts[3]);
                m_LongestIntersectSegmentB1->SetPts(intersectPtsTowardsCamera[2], intersectPtsTowardsCamera[3]);
                m_LongestIntersectSegmentB2->SetPts(intersectPtsAwayFromCamera[2], intersectPtsAwayFromCamera[3]);
            }
        }

        m_LongestIntersectSegmentAppCenterA->ExtendBothEnds(2.f);
        m_LongestIntersectSegmentAppCenterB->ExtendBothEnds(2.f);

        return intersectPts;
    }
}
