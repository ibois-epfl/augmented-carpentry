#include "AIAC/Application.h"
#include "FabFeedback.h"
#include "CutPlaneVisualizer.h"

namespace AIAC{

CutPlaneVisualizer::DistanceVisualizer::DistanceVisualizer(){
    for(int i = 0 ; i < 4 ; i++){
        auto line = GOLine::Add();
        line->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        line->SetWeight(2.0f);
        m_AllPrimitives.emplace_back(line);
        m_Lines.emplace_back(line);

        auto text = GOText::Add("", GOPoint(0.0f, 0.0f, 0.0f));
        text->SetColor(GOColor::WHITE);
        text->SetWeight(GOWeight::BoldThick);
        m_AllPrimitives.emplace_back(text);
        m_Texts.emplace_back(text);
    }

    Deactivate();
}

CutPlaneVisualizer::CutPlaneVisualizer(){
    // m_IntersectFace = GOMesh::Add();
    // m_IntersectFace->SetIndices({0, 1, 2, 1, 2, 3});
    // m_IntersectFace->SetColor(AIAC::GOColor::ORANGE_TRANSP);

    m_IntersectFaceThickness = GOMesh::Add();
    m_IntersectFaceThickness->SetIndices({0, 1, 2, 1, 2, 3});
    m_IntersectFaceThickness->SetColor(AIAC::GOColor::ORANGE_TRANSP);

    m_IntersectPolyline = GOPolyline::Add();
    m_IntersectPolyline->SetClosed(true);
    m_IntersectPolyline->SetWeight(2.0f);
    m_IntersectPolyline->SetColor(AIAC::GOColor::ORANGE);

    m_IntersectPolylineThickness = GOPolyline::Add();
    m_IntersectPolylineThickness->SetClosed(true);
    m_IntersectPolylineThickness->SetWeight(2.0f);
    m_IntersectPolylineThickness->SetColor(AIAC::GOColor::ORANGE);

    // m_AllPrimitives.push_back(m_IntersectFace);
    m_AllPrimitives.push_back(m_IntersectPolyline);
    m_AllPrimitives.push_back(m_IntersectPolylineThickness);
    m_AllPrimitives.push_back(m_IntersectFaceThickness);

    Deactivate();
}

void CutPlaneVisualizer::CutPlaneVisualizer::Activate(){
    FeedbackVisualizer::Activate();
    m_DistanceVisualizer.Deactivate();
}

void CutPlaneVisualizer::CutPlaneVisualizer::Deactivate(){
    FeedbackVisualizer::Deactivate();
    m_DistanceVisualizer.Deactivate();
    for (auto &p : m_AllPrimitives) {
        p->SetVisibility(false);
    }
}

std::vector<glm::vec3> CutPlaneVisualizer::Update(glm::vec3 faceNorm, glm::vec3 facePt){
    TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
    auto bbox = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetBoundingBox();
    auto bboxIndices = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetBboxEdgesIndices();
    
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

    std::vector<glm::vec3> intersectPts;
    for(auto [i, j] : bboxIndices){
        glm::vec3 intersectPt;
        if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePt, intersectPt)){
            intersectPts.push_back(intersectPt);
        }
    }

    // The size of intersect Pts should always be 4, otherwise don't show the intersect face
    if(intersectPts.size() != 4){
        Deactivate();
        return std::vector<glm::vec3>();
    }

    std::vector<glm::vec3> intersectPtsThickness = intersectPts;

    // Thicknesses >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

    for (int i = 0; i < intersectPts.size(); i++) {
        intersectPts[i] += displacementTowardsCameraVec;
    }
    for (int i = 0; i < intersectPtsThickness.size(); i++) {
        intersectPtsThickness[i] += displacementAwayFromCameraVec;
    }
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


    // Update the intersect face
    // m_IntersectFace->SetVertices(intersectPts);
    m_IntersectFaceThickness->SetVertices(intersectPtsThickness);

    // Update the intersect polyline
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
        std::swap(intersectPtsThickness[1], intersectPtsThickness[2]);
    }
    else if(angle12 > angle01 && angle12 > angle02){ // 1 0 2 --- 3 => swap 0 and 1
        std::swap(intersectPts[0], intersectPts[1]);
        std::swap(intersectPtsThickness[0], intersectPtsThickness[1]);
    }

    m_IntersectPolyline->SetPoints(intersectPts);
    m_IntersectPolylineThickness->SetPoints(intersectPtsThickness);

    m_DistanceVisualizer.Deactivate();

    // // Update distance indicator
    // if(cut->GetAllNonExposedFaceIDs().size() == 1){
    //     // m_DistanceVisualizer.Activate();
    //     // m_DistanceVisualizer.Deactivate());

    //     auto nonExposedFaceID = *(cut->GetAllNonExposedFaceIDs().begin());
    //     auto nonExposedFace = cut->GetFace(nonExposedFaceID);

    //     auto faceCorners = nonExposedFace.GetCorners();
    //     for(int i = 0 ; i<4 ; i++){
    //         auto line = m_DistanceVisualizer.m_Lines[i];
    //         auto text = m_DistanceVisualizer.m_Texts[i];

    //         auto pt = intersectPts[i];
            
    //         // find the minimal distance between pt and the face corners
    //         float minDist = std::numeric_limits<float>::max();
    //         glm::vec3 minDistPt;
    //         for(auto corner : faceCorners){
    //             auto dist = glm::distance(pt, corner);
    //             if(dist < minDist){
    //                 minDist = dist;
    //                 minDistPt = corner;
    //             }
    //         }

    //         // update the line & text
    //         line->SetPts(pt, minDistPt);
    //         text->SetAnchor(pt);
    //         text->SetText(FeedbackVisualizer::toString(minDist));
    //         if(minDist < 0.5f){
    //             text->SetColor(GOColor::YELLOW);
    //         } else {
    //             text->SetColor(GOColor::WHITE);
    //         }
    //     }
    // } else {
    //     m_DistanceVisualizer.Deactivate();
    // }

    return intersectPts;
}
}