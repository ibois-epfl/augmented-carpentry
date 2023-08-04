#ifndef CUTPLANEVISUALIZER_H
#define CUTPLANEVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class CutPlaneVisualizer : public FeedbackVisualizer {
    public:
        CutPlaneVisualizer();
        
        /**
         * @brief Update the intersection polyline and face, and return the intersection point
         * 
         * @param bbox 
         * @param faceNorm 
         * @param facePt 
         * @return std::vector<glm::vec3> the intersection point of the bbox and the face
         */
        std::vector<glm::vec3> Update(glm::vec3 faceNorm, glm::vec3 facePt);

    protected:
        std::shared_ptr<GOPolyline> m_IntersectPolyline;
        std::shared_ptr<GOMesh> m_IntersectFace;
    };
}

#endif // CUTPLANEVISUALIZER_H