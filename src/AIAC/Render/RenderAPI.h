#pragma once

#include "GlUtils.h"

namespace AIAC
{
    glm::vec3 getTransformed(glm::mat4 transformMat, float x, float y, float z);
    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);
    void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum=24);

    void DrawTest(bool t=true);
}