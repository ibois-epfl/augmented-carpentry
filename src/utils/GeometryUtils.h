// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#pragma once
// #ifndef GEOMETRY_UTILS_H
// #define GEOMETRY_UTILS_H

#include "glm/glm.hpp"

// --------------------------- //
// Function related to vectors //
// --------------------------- //

/**
 * @brief Get the angle between 2 vectors
 * 
 * @param v1 
 * @param v2 
 * @return float 
 */
inline float GetAngleBetweenVectors(glm::vec3 v1, glm::vec3 v2, bool useDegree = false){
    v1 = glm::normalize(v1);
    v2 = glm::normalize(v2);
    auto rad = glm::acos(glm::dot(v1, v2));
    if(useDegree){
        return glm::degrees(rad);
    }
    return rad;
}

/**
 * @brief Check if 2 vectors are in the same direction (angle < 180 degree)
 * 
 * @param v1 
 * @param v2 
 * @return true if in the same direction
 */
inline bool IsSameDirection(glm::vec3 v1, glm::vec3 v2){
    v1 = glm::normalize(v1);
    v2 = glm::normalize(v2);
    return glm::dot(v1, v2) > 0;
}

// --------------------------------- //
// Function related to point & plane //
// --------------------------------- //

/**
 * @brief Get the projection point of a point on a plane
 * 
 * @param planeNormal Normal of the plane
 * @param planePt A point on the plane
 * @param point The point to project
 * @return glm::vec3 The projection point
 */
inline glm::vec3 GetProjectionPointOnPlane(glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 pt)
{
    planeNormal = glm::normalize(planeNormal);
    glm::vec3 v = pt - planePt;
    float d = glm::dot(planeNormal, v);
    return pt - d * planeNormal;
}

// FIXME: This one may have a bug
/**
 * @brief Get the Nearest Pt On Line object
 * 
 * @param lineVec 
 * @param linePt 
 * @param pt 
 * @return glm::vec3 
 */
inline glm::vec3 GetNearestPtOnLine(glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 pt)
{
    auto dir = glm::normalize(lineVec);
    auto pt2LinePt = pt - linePt;
    auto projLen = glm::dot(pt2LinePt, dir);
    return linePt + projLen * dir;
}

// ---------------------------- //
// Function related to line seg //
// ---------------------------- //

/**
 * @brief Check if a point is between a line segment, no matter if the point is on the line segment or not
 * 
 * @param pt Point to check
 * @param lineSegPt1 Start of the line segment
 * @param lineSegPt2 End of the line segment
 * @return true if the point is between the line segment
 */
inline bool IsPointBetweenLineSeg(glm::vec3 pt, glm::vec3 lineSegPt1, glm::vec3 lineSegPt2)
{
    auto dir1 = glm::normalize(pt - lineSegPt1);
    auto dir2 = glm::normalize(pt - lineSegPt2);
    auto dir3 = glm::normalize(lineSegPt2 - lineSegPt1);
    return glm::dot(dir1, dir3) > 0 && glm::dot(dir2, dir3) < 0;
}

/**
 * @brief Make a line segment longer by a certain length
 * 
 * @param pt1 Start of the line segment
 * @param pt2 End of the line segment
 * @param extendLen Length to extend
 */
inline void ExtendLineSeg(glm::vec3 &pt1, glm::vec3 &pt2, float extendLen)
{
    auto dir = glm::normalize(pt2 - pt1);
    pt1 -= dir * extendLen;
    pt2 += dir * extendLen;
}

/**
 * @brief From a list of points, find 2 point that forms the longest line segment
 * 
 * @param pts Candidate points
 * @param pt1 Start of the line segment
 * @param pt2 End of the line segment
 * @return true if the line segment is formed successfully
 */
inline bool FormLongestLineSeg(const std::vector<glm::vec3> &pts, glm::vec3 &pt1, glm::vec3 &pt2)
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

// ------------------------------ //
// Different intersection methods //
// ------------------------------ //

/**
 * @brief Get the Intersect Point Of Line And Plane object
 * 
 * @param lineVec 
 * @param linePt 
 * @param planeNormal 
 * @param planePt 
 * @param intersectPt 
 * @return true if intersect, false if not
 */
inline bool GetIntersectPointOfLineAndPlane(glm::vec3 lineVec, glm::vec3 linePt, glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 &intersectPt)
{
    lineVec = glm::normalize(lineVec);
    planeNormal = glm::normalize(planeNormal);

    if(glm::dot(lineVec, planeNormal) == 0) return false;

    auto d = glm::dot(planeNormal, planePt - linePt);
    auto t = d / glm::dot(planeNormal, lineVec);
    intersectPt = linePt + t * lineVec;
    return true;
}

/**
 * @brief Get the Intersect Point Of Line Seg And Plane object
 * 
 * @param lineSegPt1 
 * @param lineSegPt2 
 * @param planeNormal 
 * @param planePt 
 * @param intersectPt 
 * @return true 
 * @return false 
 */
inline bool GetIntersectPointOfLineSegAndPlane(glm::vec3 lineSegPt1, glm::vec3 lineSegPt2, glm::vec3 planeNormal, glm::vec3 planePt, glm::vec3 &intersectPt)
{
    auto lineVec = lineSegPt2 - lineSegPt1;
    if(GetIntersectPointOfLineAndPlane(lineVec, lineSegPt1, planeNormal, planePt, intersectPt)){
        if(IsPointBetweenLineSeg(intersectPt, lineSegPt1, lineSegPt2)){
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the Intersect Point Of 2 Lines
 * @param dir1
 * @param pt1
 * @param dir2
 * @param pt2
 * @param pt
 * @return true if intersect, false if not
 */
inline bool GetIntersectPointOf2Lines(glm::vec3 dir1, glm::vec3 pt1, glm::vec3 dir2, glm::vec3 pt2, glm::vec3 &pt)
{
    dir1 = glm::normalize(dir1);
    dir2 = glm::normalize(dir2);
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

/**
 * @brief Get the Intersect Point Of Line And Line Seg object
 * 
 * @param lineVec 
 * @param linePt 
 * @param lineSegPt1 
 * @param lineSegPt2 
 * @param ptInLineSeg 
 * @return true if intersect, false if not
 */
inline bool GetIntersectPointOfLineAndLineSeg(glm::vec3 lineVec, glm::vec3 linePt,
                                              glm::vec3 lineSegPt1, glm::vec3 lineSegPt2,
                                              glm::vec3& ptInLineSeg)
{
    lineVec = glm::normalize(lineVec);
    glm::vec3 intersectPt;
    auto lineSegVec = glm::normalize(lineSegPt2 - lineSegPt1);
    if(GetIntersectPointOf2Lines(lineVec, linePt, lineSegVec, lineSegPt1, intersectPt)){
        if(IsPointBetweenLineSeg(intersectPt, lineSegPt1, lineSegPt2)){
            ptInLineSeg = intersectPt;
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the Intersect Line Of 2 Planes
 * 
 * @param p1Norm 
 * @param pt1 
 * @param p2Norm 
 * @param pt2 
 * @param lineVec 
 * @param linePt 
 * @return true if intersect, false if not
 */
inline bool GetIntersectLineOf2Planes(glm::vec3 p1Norm, glm::vec3 pt1,
                                      glm::vec3 p2Norm, glm::vec3 pt2,
                                      glm::vec3 &lineVec, glm::vec3 &linePt){
    // https://math.stackexchange.com/questions/475953/how-to-calculate-the-intersection-of-two-planes
    p1Norm = glm::normalize(p1Norm);
    p2Norm = glm::normalize(p2Norm);

    lineVec = glm::normalize(glm::cross(p1Norm, p2Norm));
    auto line1Dir = glm::cross(p1Norm, lineVec);
    auto line2Dir = glm::cross(p2Norm, lineVec);
    if(GetIntersectPointOf2Lines(line1Dir, pt1, line2Dir, pt2, linePt)){
        return true;
    }
    return false;
}

// #endif //GEOMETRY_UTILS_H