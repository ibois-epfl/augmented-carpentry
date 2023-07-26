#include "glm/glm.hpp"

inline glm::vec3 GetProjectionPointOnPlane(glm::vec3 planeNormal, glm::vec3 planePoint, glm::vec3 point)
{
    glm::vec3 v = point - planePoint;
    float d = glm::dot(planeNormal, v);
    return point - d * planeNormal;
}

glm::vec3 GetNearestPtOnLine(glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 pt)
{
    auto dir = glm::normalize(lineVec);
    auto pt2LinePt = pt - linePt;
    auto projLen = glm::dot(pt2LinePt, dir);
    return linePt + projLen * dir;
}

// Function related to line seg
inline bool CheckIfPointInsideLineSeg(glm::vec3 pt, glm::vec3 pt1, glm::vec3 pt2)
{
    auto dir1 = glm::normalize(pt - pt1);
    auto dir2 = glm::normalize(pt - pt2);
    auto dir3 = glm::normalize(pt2 - pt1);
    return glm::dot(dir1, dir3) > 0 && glm::dot(dir2, dir3) < 0;
}

inline void ExtendLineSeg(glm::vec3 &pt1, glm::vec3 &pt2, float extendLen)
{
    auto dir = glm::normalize(pt2 - pt1);
    pt1 -= dir * extendLen;
    pt2 += dir * extendLen;
}

bool FormLongestLineSeg(const std::vector<glm::vec3> &pts, glm::vec3 &pt1, glm::vec3 &pt2)
{
    if(pts.size() < 2){
        return false;
    }

    // initial line seg
    pt1 = pts[0];
    pt2 = pts[1];
    if(pts.size() == 2){
        return true;
    }
    auto maxDist = glm::distance(pt1, pt2);

    // try all point and see if we can make it longer
    for(int i = 2; i < pts.size(); i++){
        auto pt = pts[i];
        auto dist1 = glm::distance(pt, pt1);
        auto dist2 = glm::distance(pt, pt2);
        if(dist1 > maxDist){
            maxDist = dist1;
            pt2 = pt;
        }
        if(dist2 > maxDist){
            maxDist = dist2;
            pt1 = pt;
        }
    }
    return true;
}

// Different intersection methods
/**
 * @brief Get the Intersect Point Of 2 Lines
 * @param dir1
 * @param pt1
 * @param dir2
 * @param pt2
 * @param pt
 * @return true if intersect, false if not
 */
bool GetIntersectPointOf2Lines(glm::vec3 dir1, glm::vec3 pt1, glm::vec3 dir2, glm::vec3 pt2, glm::vec3 &pt)
{
    auto dir3 = glm::cross(dir1, dir2);
    auto dir3Len = glm::length(dir3);
    if (dir3Len < 1e-4f)
    {
        return false;
    }
    auto dir3Norm = dir3 / dir3Len;
    auto dir1Len = glm::length(dir1);
    auto dir2Len = glm::length(dir2);
    auto dir1Norm = dir1 / dir1Len;
    auto dir2Norm = dir2 / dir2Len;
    auto det = glm::dot(dir3Norm, glm::cross(dir1Norm, dir2Norm));
    if (det < 1e-4f)
    {
        return false;
    }
    auto t1 = glm::dot(dir3Norm, glm::cross(pt2 - pt1, dir2Norm)) / det;
    auto t2 = glm::dot(dir3Norm, glm::cross(pt2 - pt1, dir1Norm)) / det;
    pt = pt1 + t1 * dir1;
    return true;
}

bool GetIntersectPointOfLineAndLineSeg(glm::vec3 lineVec, glm::vec3 linePt,
                                          glm::vec3 lineSegPt1, glm::vec3 lineSegPt2, glm::vec3& ptInLineSeg)
{
    glm::vec3 intersectPt;
    auto lineSegVec = lineSegPt2 - lineSegPt1;
    if(GetIntersectPointOf2Lines(lineVec, linePt, lineSegVec, lineSegPt1, intersectPt)){
        if(CheckIfPointInsideLineSeg(intersectPt, lineSegPt1, lineSegPt2)){
            ptInLineSeg = intersectPt;
            return true;
        }
    }
    return false;
}

// https://stackoverflow.com/questions/6408670/line-of-intersection-between-two-planes
bool GetIntersectLineOf2Planes(glm::vec3 p1Norm, glm::vec3 pt1,
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