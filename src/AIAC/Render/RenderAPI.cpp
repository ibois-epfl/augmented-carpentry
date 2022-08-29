// TODO: cache base cylinder and sphere meshes

#include "RenderAPI.h"
#include "AIAC/Log.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "AIAC/Application.h"

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
        DrawPoints3d(mapPoints, OGL_YELLOW, pointSize);

        std::vector<glm::vec3> markerEdges(map->map_markers.size() * 4 * 2);
        std::vector<glm::vec4> markerEdgeColors(map->map_markers.size() * 4 * 2, OGL_BLUE);
        for(const auto& mapMarker: map->map_markers){
            auto points = mapMarker.second.get3DPoints();
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);
            for(int i = 1 ; i < 4; i++){
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
            }
            markerEdges.emplace_back(points[0].x, points[0].y, points[0].z);

            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_RED);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);
            markerEdgeColors.emplace_back(OGL_BLUE);

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

    void DrawGOPrimitive(GOPrimitive goPrimitive) {

    }

    void DrawPoint(const GOPoint& goPoint) {
        vector<glm::vec3> point(1, goPoint.GetPosition());
        DrawPoints3d(point, goPoint.GetColor(), goPoint.GetSize());
    }

    // TODO: For both Line and Points: Try to use cache to avoid re-construction of the vector (if slow, otherwise no needed)
    // TODO: Draw all point at once (if possible)
    void DrawPoints(const std::vector<std::shared_ptr<GOPoint>>& goPoints) {
        for(const auto& goPoint: goPoints){
            DrawPoint(*goPoint);
        }
//        vector<glm::vec3> points;
//        vector<glm::vec4> colors;
//        for (const auto &goPoint: goPoints) {
//            points.emplace_back(goPoint->GetPosition());
//            colors.emplace_back(goPoint->GetColor());
//        }
//        DrawPoints3d(points, colors, 5.0f);
    }

    void DrawLine(const GOLine& goLine) {
        // TODO: thickness of line
        vector<glm::vec3> vertices(2);
        vertices[0] = goLine.GetPStart().GetPosition();
        vertices[1] = goLine.GetPEnd().GetPosition();
        DrawLines3d(vertices, goLine.GetColor());
    }

    void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines) {
        vector<glm::vec3> vertices(goLines.size() * 2);
        vector<glm::vec4> colors(goLines.size());
        for (const auto &goLine: goLines) {
            vertices.emplace_back(goLine->GetPStart().GetPosition());
            vertices.emplace_back(goLine->GetPEnd().GetPosition());
            colors.emplace_back(goLine->GetColor());
            colors.emplace_back(goLine->GetColor());
        }
        DrawLines3d(vertices, colors);
    }

    void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum) {
        std::vector<glm::vec3> vertices; vertices.reserve(sectorNum + 1);
        std::vector<glm::vec3> edges;    edges.reserve(2 * sectorNum);
        std::vector<uint32_t> indices;  indices.reserve(3 * sectorNum);
        vertices.emplace_back(center);

        glm::vec3 newX = glm::cross(normal, glm::vec3(0, 1, 0));
        glm::vec3 newZ = glm::cross(newX, normal);

        glm::mat4 transformMat;

        transformMat[0] = glm::vec4(newX, 0);
        transformMat[1] = glm::vec4(normal, 0);
        transformMat[2] = glm::vec4(newZ, 0);
        transformMat[3] = glm::vec4(center, 1);

        for (int i = 0; i < sectorNum; ++i){
            GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
            glm::vec3 vertex = transformMat * glm::vec4(
                    static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
                    0,
                    static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
                    1
            );
            vertices.emplace_back(vertex);
        }

        for (int i = 1; i < sectorNum; ++i){
            indices.emplace_back(0);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }
        indices.emplace_back(0);
        indices.emplace_back(sectorNum);
        indices.emplace_back(1);

        for (int i = 1; i < sectorNum; ++i){
            edges.emplace_back(vertices[i]);
            edges.emplace_back(vertices[i + 1]);
        }
        edges.emplace_back(vertices[sectorNum]);
        edges.emplace_back(vertices[1]);

        DrawTriangles3d(vertices, indices, color);
        DrawLines3d(edges, edgeColor);
    }

    void DrawCircle(const GOCircle& goCircle) {
        DrawCircle(goCircle.GetCenter().GetPosition(), goCircle.GetNormal(), goCircle.GetRadius(),
                   goCircle.GetColor(), goCircle.GetEdgeColor(), max(24, int(goCircle.GetRadius() * 3)));
    }

    void DrawCircles(const std::vector<std::shared_ptr<GOCircle>>& goCircles) {
        for (const auto &goCircle: goCircles) {
            DrawCircle(*goCircle);
        }
    }

    void DrawCylinder(const GOCylinder& goCylinder) {
        DrawCylinder(goCylinder.GetPStart().GetPosition(), goCylinder.GetPEnd().GetPosition(),
                     goCylinder.GetRadius(), goCylinder.GetColor(), goCylinder.GetEdgeColor());
    }

    void DrawCylinders(const std::vector<std::shared_ptr<GOCylinder>>& goCylinders) {
        for (const auto &goCylinder: goCylinders) {
            DrawCylinder(*goCylinder);
        }
    }

    void DrawPolyline(const GOPolyline& goPolyline) {
        vector<glm::vec3> vertices(goPolyline.GetPoints().size() * 2);
        vertices.emplace_back(goPolyline.GetPoints()[0].GetPosition());
        for (int i = 1; i < goPolyline.GetPoints().size() - 1; i++) {
            vertices.emplace_back(goPolyline.GetPoints()[i].GetPosition());
            vertices.emplace_back(goPolyline.GetPoints()[i].GetPosition());
        }
        vertices.emplace_back(goPolyline.GetPoints()[goPolyline.GetPoints().size() - 1].GetPosition());

        if(goPolyline.IsClosed()){
            vertices.emplace_back(goPolyline.GetPoints()[goPolyline.GetPoints().size() - 1].GetPosition());
            vertices.emplace_back(goPolyline.GetPoints()[0].GetPosition());
        }
        DrawLines3d(vertices, goPolyline.GetColor());
    }

    void DrawPolylines(const std::vector<std::shared_ptr<GOPolyline>>& goPolylines) {
        for(const auto& goPolyline: goPolylines){
            DrawPolyline(*goPolyline);
        }
    }

    void DrawTriangle(const GOTriangle& goTriangle) {
        vector<glm::vec3> vertices = goTriangle.GetVertices();
        vector<uint32_t> indices{0, 1, 2};
        DrawTriangles3d(vertices, indices, goTriangle.GetColor());
    }

    void DrawTriangles(const std::vector<std::shared_ptr<GOTriangle>>& goTriangles) {
        for (const auto &goTriangle: goTriangles) {
            DrawTriangle(*goTriangle);
        }
    }

    void DrawMesh(const GOMesh& goMesh) {
        DrawTriangles3d(goMesh.GetVertices(), goMesh.GetIndices(), goMesh.GetColor());
    }

    void DrawMeshes(const std::vector<std::shared_ptr<GOMesh>> &goMeshes) {
        for (auto &goMesh: goMeshes) {
            DrawMesh(*goMesh);
        }
    }

    void DrawText(GOText goText){
//        if(!textRenderer.IsInitialized()){ textRenderer.Init(); }
//        textRenderer.RenderText(goText.GetText(), 0, 0, 0.1, goText.GetColor(), glm::mat4(1.0f));
    }

    void DrawTexts(std::vector<GOText> goTexts) {

    }

    void DrawTest(bool t, glm::mat4 projection){
//        std::vector<std::shared_ptr<GOPoint>> points;
//        std::vector<std::shared_ptr<GOLine>> lines;
//        std::vector<std::shared_ptr<GOCircle>> circles;
//        std::vector<std::shared_ptr<GOCylinder>> cylinders;
//        std::vector<std::shared_ptr<GOPolyline>> polylines;
//        std::vector<std::shared_ptr<GOTriangle>> triangles;
//        std::vector<std::shared_ptr<GOText>> texts;
//        AIAC_GOREG->GetAllGOs(points, lines, circles, cylinders, polylines, triangles, texts);

//        DrawPoints(points);
//        DrawLines(lines);
//        DrawPolylines(polylines);
//        DrawTriangles(triangles);

//        DrawCylinders(cylinders);
//        DrawCircles(circles);

//        textRenderer.RenderText("Hello World", 0, 0, 40, glm::vec3(1, 0, 0));
//        if(!textRenderer.IsInitialized()){ textRenderer.Init(); }
//        textRenderer.RenderText("goText.GetText()", 0, 0, 0.1, glm::vec4(0,0,0,0.5), projection);
    }


}
