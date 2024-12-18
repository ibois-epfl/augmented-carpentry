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

#include <memory>
#include <vector>

#include "map.h" // TSLAM map

#include "TextRenderer.h"
#include "AIAC/GOSys/GOPrimitive.h"

namespace AIAC
{
    struct CylinderPole {
        GLfloat x, z;
    };

    /**
     * @brief Combine 3 points into a glm::vec3 and transform it based on the given transformation matrix.
     * @param transformMat A 4x4 transformation matrix.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     */
    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z);

    /**
     * @brief Render Slam map on the current frame.
     * @param map A tslam map to be rendered.
     * @param color PointCloud's color.
     * @param pointSize PointCloud's size.
     */
    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);

    /**
     * @brief Draw all the GOs present in the GORegistry.
     * @param projection OpenGL projection matrix.
     */
    void DrawAllGOs(glm::mat4 projection = glm::mat4(1.0f), float textScale = 1.0f);

    /**
     * @brief Draw a GOPrimitive. (This function neglects the "isVisible" attribute of the object and will draw it anyway)
     * @param goPrimitive Object to draw.
     */
    void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive);

    /**
     * @brief Draw a GOPoint
     * @param goPoint The point to draw.
     */
    void DrawPoint(const GOPoint& goPoint);
    void DrawPoints(const std::vector<std::shared_ptr<GOPoint>>& goPoints);

    /**
     * @brief Draw a line on two glm::vec3.
     * @param p1 First point.
     * @param p2 Second point.
     * @param weight Weight of the line.
     * @param color RGBA Color of the line.
     */
    void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight = GOWeight::Default, const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    /**
     * @brief Draw multiple lines.
     * @param vertices A vector of glm::vec3. If you have line [p1, p2] and [p2, p3], the vector should be construct as [p1, p2, p2, p3, ...]
     * @param weight Weight of the line.
     * @param color RGBA Color of the line.
     */
    void DrawLines(const vector<glm::vec3> &vertices, float weight, const glm::vec4 &color);
    void DrawLine(const GOLine& goLine);
    void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines);

    /**
     * @brief Draw a single circle.
     * @param center Center of the circle.
     * @param normal The normal of plane on which the circle lays.
     * @param radius Radius of the circle.
     * @param color RGBA Color of the face.
     * @param edgeColor RGBA Color of the edge.
     * @param edgeWeight Weight of the edge.
     * @param sectorNum Number of sectors, can be derived from GetSectorNum(radius).
     */
    void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum = 24);
    void DrawCircle(const GOCircle& goCircle);
    void DrawCircles(const std::vector<std::shared_ptr<GOCircle>>& goCircles);

    /**
     * @brief Draw a Cylinder, this is also used for drawing lines with heavy weight (>1.0f).
     * @param baseCenter Base center (bottom) of the cylinder.
     * @param topCenter Top center (top) of the cylinder.
     * @param radius Radius of the cylinder; For drawing line, radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE.
     * @param color Color of the cylinder.
     * @param edgeColor The color of the edges of the caps.
     * @param sectorNum Number of sectors of the cylinder. Can call `GetSectorNum(radius)` to get the default value.
     */
    void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter,
                      GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum = 24);
    void DrawCylinder(const GOCylinder& goCylinder);
    void DrawCylinders(const std::vector<std::shared_ptr<GOCylinder>>& goCylinders);

    void DrawPolyline(const GOPolyline& goPolyline);
    void DrawPolylines(const std::vector<std::shared_ptr<GOPolyline>>& goPolylines);

    void DrawTriangle(const GOTriangle& goTriangle);
    void DrawTriangles(const std::vector<std::shared_ptr<GOTriangle>>& goTriangles);

    void DrawMesh(const GOMesh& goMesh);
    void DrawMeshes(const std::vector<std::shared_ptr<GOMesh>> &goMeshes);

    void DrawText(const GOText& goText, float scale = 1.0f, const glm::mat4& projection = glm::mat4(1.0f));
    void DrawTexts(std::vector<GOText> goTexts, float scale = 1.0f, const glm::mat4& projection = glm::mat4(1.0f));
}