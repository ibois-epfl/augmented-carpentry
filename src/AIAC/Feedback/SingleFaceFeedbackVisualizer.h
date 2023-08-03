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
            std::cout << "SingleFaceFBV::Update()" << std::endl;
            std::vector<glm::vec3> intersectPts;
            for(auto [i, j] : bboxIndices){
                std::cout << i << " " << j << std::endl;
                std::cout << glm::to_string(bbox[i]) << " " << glm::to_string(bbox[j]) << std::endl;
                glm::vec3 intersectPt;
                if(GetIntersectPointOfLineSegAndPlane(bbox[i], bbox[j], faceNorm, facePt, intersectPt)){
                    intersectPts.push_back(intersectPt);
                }
            }
            // The size of intersect Pts should always be 4
            // assert(intersectPts.size() == 4);
            cout << intersectPts.size() << endl;

            // Update the intersect polyline
            m_IntersectFace->SetVertices(intersectPts);

            return intersectPts;
        }

    protected:
        std::shared_ptr<GOPolyline> m_IntersectPolyline;
        std::shared_ptr<GOMesh> m_IntersectFace;
    };
}

#endif // SINGLEFACEFEEDBACKVISUALIZER_H