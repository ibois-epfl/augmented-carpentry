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

    void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive);
    void DrawGOs(const std::vector<shared_ptr<GOPrimitive>>& goPrimitive);

    void DrawPoint(const GOPoint& goPoint);
    void DrawPoints(const std::vector<std::shared_ptr<GOPoint>>& goPoints);

    // void DrawLine(const GOPoint &p1, const GOPoint &p2);
    void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight = GOWeight::Default, const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    void DrawLines(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, float weight);
    void DrawLine(const GOLine& goLine);
    void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines);

    void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum = 24);
    void DrawCircle(const GOCircle& goCircle);
    void DrawCircles(const std::vector<std::shared_ptr<GOCircle>>& goCircles);

    void DrawCylinder(const GOCylinder& goCylinder);
    void DrawCylinders(const std::vector<std::shared_ptr<GOCylinder>>& goCylinders);
    void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter,
                      GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum = 24);

    void DrawPolyline(const GOPolyline& goPolyline);
    void DrawPolylines(const std::vector<std::shared_ptr<GOPolyline>>& goPolylines);

    void DrawTriangle(const GOTriangle& goTriangle);
    void DrawTriangles(const std::vector<std::shared_ptr<GOTriangle>>& goTriangles);

    void DrawMesh(const GOMesh& goMesh);
    void DrawMeshes(const std::vector<std::shared_ptr<GOMesh>> &goMeshes);

    void DrawText(const GOText& goText);
    void DrawTexts(std::vector<GOText> goTexts);

    void DrawTest(bool t = true, glm::mat4 projection = glm::mat4(1.0f));
}