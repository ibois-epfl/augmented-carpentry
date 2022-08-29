#include "RenderAPI.h"
#include "AIAC/Log.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace AIAC
{
    static TextRenderer textRenderer;

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize) {
        std::vector<glm::vec3> mapPoints(map->map_points.size());
        for(const auto& mapPoint: map->map_points){
            if(mapPoint.isValid()){
                mapPoints.emplace_back(mapPoint.getCoordinates().x, mapPoint.getCoordinates().y, mapPoint.getCoordinates().z);
            }
        }
        DrawPoints3d(mapPoints, YELLOW, pointSize);

        std::vector<glm::vec3> markerEdges(map->map_markers.size() * 4 * 2);
        std::vector<glm::vec4> markerEdgeColors(map->map_markers.size() * 4 * 2, BLUE);
        for(const auto& mapMarker: map->map_markers){
            auto points = mapMarker.second.get3DPoints();
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);
            for(int i = 1 ; i < 4; i++){
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
            }
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);

            markerEdgeColors.emplace_back(RED);
            markerEdgeColors.emplace_back(RED);
            markerEdgeColors.emplace_back(RED);
            markerEdgeColors.emplace_back(RED);
            markerEdgeColors.emplace_back(BLUE);
            markerEdgeColors.emplace_back(BLUE);
            markerEdgeColors.emplace_back(BLUE);
            markerEdgeColors.emplace_back(BLUE);

        }

        DrawLines3d(markerEdges, markerEdgeColors);
    }

    glm::vec3 GetTransformed(glm::mat4 transformMat, float x, float y, float z){
        glm::vec4 point(x, y, z, 1);
        point = transformMat * point;
        return {point.x, point.y, point.z};
    }

    void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum){
        std::vector<CylinderPole> cylinderPoles; // vector of structs

        glm::vec3 x1 = baseCenter, x2 = topCenter;
        glm::vec3 norm = glm::normalize(x2 - x1);
        GLfloat h = glm::length(x2 - x1);

        vector<glm::vec3> points;
        points.emplace_back(x1);
        points.emplace_back(x2);

        glm::vec3 newX = glm::cross(norm, glm::vec3(0, 1, 0));
        glm::vec3 newZ = glm::cross(newX, norm);

        glm::mat4 transformMat;

        transformMat[0] = glm::vec4(newX, 0);
        transformMat[1] = glm::vec4(norm, 0);
        transformMat[2] = glm::vec4(newZ, 0);
        transformMat[3] = glm::vec4(x1, 1);

        for (int i = 0; i < sectorNum; ++i){
            GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
            CylinderPole cp{
                    .x = static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
                    .z = static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
            };
            cylinderPoles.push_back(cp);
        }

        vector<uint32_t> flattenedIndices;
        vector<glm::vec3> indices;
        vector<glm::vec3> vertices;
        vector<glm::vec3> capContourTop, capContourBase;

        vertices.emplace_back(x1); // 0
        vertices.emplace_back(x2); // 1

        vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z)); // 2
        vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z)); // 3

        capContourBase.push_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
        capContourTop.push_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));

        int baseCenterIdx = 0;
        int topCenterIdx = 1;
        int prevBaseVertexIdx = 2;
        int prevTopVertexIdx = 3;
        int curBaseVertexIdx = 4;
        int curTopVertexIdx = 5;

        for(int i = 1; i < sectorNum; i++){
            capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));
            capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

            vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
            vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

            indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
            indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
            indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
            indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

            prevBaseVertexIdx = curBaseVertexIdx;
            prevTopVertexIdx = curTopVertexIdx;
            curBaseVertexIdx += 2;
            curTopVertexIdx += 2;
        }

        // Last one
        curBaseVertexIdx = 2;
        curTopVertexIdx = 3;
        indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
        indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
        indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
        indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

        capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
        capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));

        for(auto vid: indices){
            flattenedIndices.push_back((uint)vid.x);
            flattenedIndices.push_back((uint)vid.y);
            flattenedIndices.push_back((uint)vid.z);
        }

        DrawTriangles3d(vertices, flattenedIndices, color);
        DrawLines3d(capContourBase, edgeColor);
        DrawLines3d(capContourTop, edgeColor);
        DrawPoints3d(points, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 5.0f);
    }


    void DrawTest(bool t, glm::mat4 projection){
        if(!textRenderer.IsInitialized()){ textRenderer.Init(); }
        textRenderer.RenderText("Hello World", 0, 0, 0.1, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), projection);
    }
}
