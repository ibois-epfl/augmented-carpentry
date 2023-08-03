#ifndef SINGLEFACEFEEDBACKVISUALIZER_H
#define SINGLEFACEFEEDBACKVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class SingleFaceFeedbackVisualizer : public FeedbackVisualizer {
    public:
        SingleFaceFeedbackVisualizer() {
            m_IntersectFace = GOMesh::Add();
            m_IntersectFace->SetIndices({0, 1, 2, 1, 2, 3});
            m_IntersectFace->SetColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.5f));

            m_IntersectPolyline = GOPolyline::Add();
            m_IntersectPolyline->SetClosed(true);
            m_IntersectPolyline->SetWeight(2.0f);
            m_IntersectPolyline->SetColor(glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));

            m_AllPrimitives.push_back(m_IntersectFace);
            m_AllPrimitives.push_back(m_IntersectPolyline);
        }

        /**
         * @brief Update the intersection polyline and face, and return the intersection point
         * 
         * @param bbox 
         * @param faceNorm 
         * @param facePt 
         * @return std::vector<glm::vec3> the intersection point of the bbox and the face
         */
        std::vector<glm::vec3> Update(const std::vector<glm::vec3>& bbox, const std::vector<std::pair<int, int>>& bboxIndices, glm::vec3 faceNorm, glm::vec3 facePt){
            std::vector<glm::vec3> intersectPts;
            for(auto [i, j] : bboxIndices){
                glm::vec3 intersectPt;
                if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePt, intersectPt)){
                    intersectPts.push_back(intersectPt);
                }
            }
            // The size of intersect Pts should always be 4
            // assert(intersectPts.size() == 4);

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

            return intersectPts;
        }

    protected:
        std::shared_ptr<GOPolyline> m_IntersectPolyline;
        std::shared_ptr<GOMesh> m_IntersectFace;
    };
}

#endif // SINGLEFACEFEEDBACKVISUALIZER_H