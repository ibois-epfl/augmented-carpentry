#pragma once

#include "TextRenderer.h"
#include "GlUtils.h"
#include "AIAC/GOSys/GOPrimitive.h"

namespace AIAC
{
    struct CylinderPole {
        GLfloat x, z;
    };

    // ut
    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z);

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);
    void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter,
                             GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum = 24);

    void DrawTest(bool t = true, glm::mat4 projection = glm::mat4(1.0f));
}