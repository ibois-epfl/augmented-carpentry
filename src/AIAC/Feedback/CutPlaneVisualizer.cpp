#include "AIAC/Application.h"
#include "FabFeedback.h"
#include "CutPlaneVisualizer.h"

namespace AIAC{

CutPlaneVisualizer::DistanceVisualizer::DistanceVisualizer(){
    for(int i = 0 ; i < 4 ; i++){
        auto line = GOLine::Add();
        line->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        line->SetWeight(2.0f);
        m_Lines.push_back(line);
        m_AllPrimitives.push_back(line);

        auto text = GOText::Add();
        text->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        text->SetWeight(GOWeight::BoldThick);
        m_Texts.push_back(text);
        m_AllPrimitives.push_back(text);
    }

    Deactivate();
}

CutPlaneVisualizer::CutPlaneVisualizer(){
    m_IntersectFace = GOMesh::Add();
    m_IntersectFace->SetIndices({0, 1, 2, 1, 2, 3});
    m_IntersectFace->SetColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.5f));

    m_IntersectPolyline = GOPolyline::Add();
    m_IntersectPolyline->SetClosed(true);
    m_IntersectPolyline->SetWeight(2.0f);
    m_IntersectPolyline->SetColor(glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));

    m_AllPrimitives.push_back(m_IntersectFace);
    m_AllPrimitives.push_back(m_IntersectPolyline);

    Deactivate();
}

std::vector<glm::vec3> CutPlaneVisualizer:: Update(glm::vec3 faceNorm, glm::vec3 facePt){
    auto bbox = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetBoundingBox();
    auto bboxIndices = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetBboxEdgesIndices();

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

    // Update the intersect face
    m_IntersectFace->SetVertices(intersectPts);

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
    }
    else if(angle12 > angle01 && angle12 > angle02){ // 1 0 2 --- 3 => swap 0 and 1
        std::swap(intersectPts[0], intersectPts[1]);
    }

    m_IntersectPolyline->SetPoints(intersectPts);

    // Update distance indicator
    TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
    if(cut->GetAllNonExposedFaceIDs().size() == 1){
        m_DistanceVisualizer.Activate();
        auto nonExposedFaceID = *(cut->GetAllNonExposedFaceIDs().begin());
        auto nonExposedFace = cut->GetFace(nonExposedFaceID);

        auto faceCorners = nonExposedFace.GetCorners();
        for(int i = 0 ; i<4 ; i++){
            auto line = m_DistanceVisualizer.m_Lines[i];
            auto text = m_DistanceVisualizer.m_Texts[i];

            auto pt = intersectPts[i];
            
            // find the minimal distance between pt and the face corners
            float minDist = std::numeric_limits<float>::max();
            glm::vec3 minDistPt;
            for(auto corner : faceCorners){
                auto dist = glm::distance(pt, corner);
                if(dist < minDist){
                    minDist = dist;
                    minDistPt = corner;
                }
            }
            
            // update the line & text
            line->SetPts(pt, minDistPt);
            text->SetAnchor(pt);
            text->SetText(FeedbackVisualizer::toString(minDist));
        }

    } else {
        m_DistanceVisualizer.Deactivate();
    }

    return intersectPts;
}
}