#include "AIAC/Application.h"
#include "FabFeedback.h"
#include "CutPlaneVisualizer.h"

namespace AIAC{

CutPlaneVisualizer::CutPlaneVisualizer(){
    m_LongestIntersectSegmentAppCenter = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
    m_LongestIntersectSegment1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
    m_LongestIntersectSegment2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

    m_LongestIntersectSegment1->SetWeight(GOWeight::Medium);
    m_LongestIntersectSegment2->SetWeight(GOWeight::Medium);

    m_LongestIntersectSegmentAppCenter->SetColor(AIAC::GOColor::CYAN);
    m_LongestIntersectSegment1->SetColor(AIAC::GOColor::ORANGE);
    m_LongestIntersectSegment2->SetColor(AIAC::GOColor::ORANGE);

    m_AllPrimitives.push_back(m_LongestIntersectSegmentAppCenter);
    m_AllPrimitives.push_back(m_LongestIntersectSegment1);
    m_AllPrimitives.push_back(m_LongestIntersectSegment2);

    Deactivate();
}

void CutPlaneVisualizer::CutPlaneVisualizer::Activate(){
    FeedbackVisualizer::Activate();
    // m_DistanceVisualizer.Deactivate();
}

void CutPlaneVisualizer::CutPlaneVisualizer::Deactivate(){
    FeedbackVisualizer::Deactivate();
    // m_DistanceVisualizer.Deactivate();
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

    // intersect the normal of the tool face with the bbox
    std::vector<glm::vec3> intersectPts;
    for(auto [i, j] : bboxIndices){
        glm::vec3 intersectPt;
        if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePt, intersectPt)){
            intersectPts.push_back(intersectPt);
        }
    }

    // if 2 it's impossible to have a cut plane
    if (intersectPts.size() < 2) {
        Deactivate();
        AIAC_WARN("Not enough intersect points for the cut plane visualizer");
        return std::vector<glm::vec3>();
    }

    // the intersection feedback is limited to 4 points (aka romboid intersection)
    if (intersectPts.size() >= 4) {
        // To place the points in the correct order, we take [0], [1], [2] as the initial triangle,
        // and find the angle between vector {0,3}, {1,3}, {2,3}, and find the biggest one as [3]'s 2 neighbor
        auto vec0 = intersectPts[0] - intersectPts[3];
        auto vec1 = intersectPts[1] - intersectPts[3];
        auto vec2 = intersectPts[2] - intersectPts[3];
        auto angle01 = GetAngleBetweenVectors(vec0, vec1);
        auto angle02 = GetAngleBetweenVectors(vec0, vec2);
        auto angle12 = GetAngleBetweenVectors(vec1, vec2);
        if(angle01 > angle02 && angle01 > angle12){  // 0 2 1 --- 3 => swap 1 and 2
            std::swap(intersectPts[1], intersectPts[2]);
        }
        else if(angle12 > angle01 && angle12 > angle02){ // 1 0 2 --- 3 => swap 0 and 1
            std::swap(intersectPts[0], intersectPts[1]);
        }

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
            m_LongestIntersectSegmentAppCenter->SetPts(intersectPts[0], intersectPts[1]);
        } else if (dist2 < dist1 && dist2 < dist3 && dist2 < dist4) {
            closestMidPt = m_SegmentMid2;
            m_LongestIntersectSegmentAppCenter->SetPts(intersectPts[1], intersectPts[2]);
        } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4) {
            closestMidPt = m_SegmentMid3;
            m_LongestIntersectSegmentAppCenter->SetPts(intersectPts[2], intersectPts[3]);
        } else {
            closestMidPt = m_SegmentMid4;
            m_LongestIntersectSegmentAppCenter->SetPts(intersectPts[3], intersectPts[0]);
        }

        // add the thickness
        float bladeThicknessScaled;
        float overHangThicknessScaled;
        if (currentToolType == ACToolHeadType::CHAINSAW) {
            bladeThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().ThicknessACIT;
            overHangThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().OverhangACIT;
        } else if (currentToolType == ACToolHeadType::CIRCULARSAW) {
            bladeThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().ThicknessACIT;
            overHangThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().OverhangACIT;
        }
        float displacementTowardsCamera = bladeThicknessScaled;
        float displacementAwayFromCamera = bladeThicknessScaled - overHangThicknessScaled;

        glm::vec3 normalVec = glm::normalize(normEnd - normStart);
        glm::vec3 oppositeNormalVec = -normalVec;

        glm::vec3 displacementTowardsCameraVec = displacementTowardsCamera * normalVec;
        glm::vec3 displacementAwayFromCameraVec = displacementAwayFromCamera * oppositeNormalVec;

        glm::vec3 startAppCenter = m_LongestIntersectSegmentAppCenter->GetPStart();
        glm::vec3 endAppCenter = m_LongestIntersectSegmentAppCenter->GetPEnd();

        glm::vec3 startAppCenterTowardsCameraVec = startAppCenter + displacementTowardsCameraVec;
        glm::vec3 endAppCenterTowardsCameraVec = endAppCenter + displacementTowardsCameraVec;

        glm::vec3 startAppCenterAwayFromCameraVec = startAppCenter + displacementAwayFromCameraVec;
        glm::vec3 endAppCenterAwayFromCameraVec = endAppCenter + displacementAwayFromCameraVec;

        m_LongestIntersectSegment1->SetPts(startAppCenterTowardsCameraVec, endAppCenterTowardsCameraVec);
        m_LongestIntersectSegment2->SetPts(startAppCenterAwayFromCameraVec, endAppCenterAwayFromCameraVec);
        m_LongestIntersectSegmentAppCenter->ExtendBothEnds(2.f);
    }

    return intersectPts;
}
}