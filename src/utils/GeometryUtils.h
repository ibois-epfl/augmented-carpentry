#include "glm/glm.hpp"

inline glm::vec3 GetProjectionPointOnPlane(glm::vec3 planeNormal, glm::vec3 planePoint, glm::vec3 point)
{
    glm::vec3 v = point - planePoint;
    float d = glm::dot(planeNormal, v);
    return point - d * planeNormal;
}

// https://stackoverflow.com/questions/6408670/line-of-intersection-between-two-planes
bool GetIntersectLine(glm::vec3 p1Norm, glm::vec3 pt1,
                      glm::vec3 p2Norm, glm::vec3 pt2,
                      glm::vec3 &lineVec, glm::vec3 &linePt){
    auto p3Norm = glm::cross(p1Norm, p2Norm);
    auto vecLen = glm::length(p3Norm);
    auto det = vecLen * vecLen;
    if(det < 1e-4f){
        return false;
    }
    lineVec = p3Norm;
    linePt = (glm::cross(p3Norm, p2Norm) * pt1 + glm::cross(p1Norm, p3Norm) * pt2) / det;
    return true;
}