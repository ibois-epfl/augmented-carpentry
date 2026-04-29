

# File RenderAPI.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Render**](dir_4231f99b70cbd7a69a19f070b3954fcb.md) **>** [**RenderAPI.h**](RenderAPI_8h.md)

[Go to the documentation of this file](RenderAPI_8h.md)


```C++
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

    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z);

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);

    void DrawAllGOs(glm::mat4 projection = glm::mat4(1.0f), float textScale = 1.0f);

    void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive);

    void DrawPoint(const GOPoint& goPoint);
    void DrawPoints(const std::vector<std::shared_ptr<GOPoint>>& goPoints);

    void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight = GOWeight::Default, const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    void DrawLines(const vector<glm::vec3> &vertices, float weight, const glm::vec4 &color);
    void DrawLine(const GOLine& goLine);
    void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines);

    void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum = 24);
    void DrawCircle(const GOCircle& goCircle);
    void DrawCircles(const std::vector<std::shared_ptr<GOCircle>>& goCircles);

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
```


