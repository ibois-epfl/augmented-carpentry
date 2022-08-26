#pragma once

#include "GlUtils.h"

namespace AIAC
{
    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);
    void DrawTest(bool t=true);
}