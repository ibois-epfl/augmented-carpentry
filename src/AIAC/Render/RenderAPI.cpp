// TODO: cache base cylinder and sphere meshes

#include "RenderAPI.h"
#include "TextRenderer.h"
#include "AIAC/Log.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "AIAC/Application.h"

#include "glm/gtx/string_cast.hpp"

namespace AIAC
{
    const float WEIGHT_TO_CYLINDER_RADIUS_RATE = 1.0 / 16.0f;
    extern TextRenderer textRenderer;

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize) {
        std::vector<glm::vec3> mapPoints; mapPoints.reserve(map->map_points.size());
        for(const auto& mapPoint: map->map_points){
            if(mapPoint.isValid()){
                mapPoints.emplace_back(mapPoint.getCoordinates().x, mapPoint.getCoordinates().y, mapPoint.getCoordinates().z);
            }
        }
        DrawPoints3d(mapPoints, OGL_YELLOW, pointSize);

        std::vector<glm::vec3> markerEdges; markerEdges.reserve(map->map_markers.size() * 4 * 2);
        std::vector<glm::vec4> markerEdgeColors; markerEdgeColors.reserve(map->map_markers.size() * 4 * 2);
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
    }

    void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive) {
        if(!goPrimitive->IsVisible()){
            return;
        }
        switch (goPrimitive->GetType()){
            case _GOPoint:
                DrawPoint(*std::static_pointer_cast<GOPoint>(goPrimitive)); break;
            case _GOLine:
                DrawLine(*std::static_pointer_cast<GOLine>(goPrimitive)); break;
            case _GOCircle:
                DrawCircle(*std::static_pointer_cast<GOCircle>(goPrimitive)); break;
            case _GOCylinder:
                DrawCylinder(*std::static_pointer_cast<GOCylinder>(goPrimitive)); break;
            case _GOPolyline:
                DrawPolyline(*std::static_pointer_cast<GOPolyline>(goPrimitive)); break;
            case _GOTriangle:
                DrawTriangle(*std::static_pointer_cast<GOTriangle>(goPrimitive)); break;
            case _GOMesh:
                DrawMesh(*std::static_pointer_cast<GOMesh>(goPrimitive)); break;
//            case _GOText:
//                DrawText(*std::static_pointer_cast<GOText>(goPrimitive)); break;
            default:
                break;
        }
    }

    void DrawGOs(const std::vector<shared_ptr<GOPrimitive>>& goPrimitive){
        for(auto& go: goPrimitive){
            DrawGO(go);
        }
    }

    void DrawPoint(const GOPoint& goPoint) {
        vector<glm::vec3> point(1, goPoint.GetPosition());
        DrawPoints3d(point, goPoint.GetColor(), goPoint.GetWeight());
    }

    // @TODO Try to use cache to avoid re-construction of the vector (if slow, probably no needed)
    // @TODO Draw all point with different size at once (if possible)
    void DrawPoints(const std::vector<std::shared_ptr<GOPoint>>& goPoints) {
        for(const auto& goPoint: goPoints){
            DrawPoint(*goPoint);
        }
    }

    int getSectorNum(float radius){
        if(radius <= 3){
            return 6;
        }
        if(radius <= 12){
            return 12;
        }
        if(radius <= 24){
            return 24;
        }
        return 36;
    }

    void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight, const glm::vec4 &color){
        if(weight <= 0){
            return;
        }
        if(weight == 1.0f){
            vector<glm::vec3> line;
            line.emplace_back(p1);
            line.emplace_back(p2);
            DrawLines3d(line, color);
            return;
        }
        float radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE;
        DrawCylinder(p1, p2, radius,
                     color, glm::vec4(0,0,0,0), getSectorNum(radius));
    }

    void DrawLines(const vector<glm::vec3> &vertices, float weight, const glm::vec4 &color){
        if(weight <= 0){
            return;
        }
        if(weight == 1.0f){
            DrawLines3d(vertices, color);
            return;
        }
        float radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE;
        DrawCylinder(vertices[0], vertices[1], radius,
                     color, glm::vec4(0,0,0,0), getSectorNum(radius));
    }

    void DrawLine(const GOLine& goLine) {
        if(!goLine.IsVisible()){
            return;
        }

        if(goLine.GetWeight() <= 1.0f){
            vector<glm::vec3> vertices; vertices.reserve(2);
            vertices[0] = goLine.GetPStart().GetPosition();
            vertices[1] = goLine.GetPEnd().GetPosition();
            DrawLines3d(vertices, goLine.GetColor());
        } else {
            float radius = goLine.GetWeight() * WEIGHT_TO_CYLINDER_RADIUS_RATE;
            DrawCylinder(goLine.GetPStart().GetPosition(), goLine.GetPEnd().GetPosition(),
                         radius, goLine.GetColor(), glm::vec4(0, 0, 0, 0),
                         getSectorNum(radius));
        }
    }

    void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines) {
        vector<glm::vec3> vertices; vertices.reserve(goLines.size() * 2);
        vector<glm::vec4> colors; colors.reserve(goLines.size());
        for (const auto &goLine: goLines) {
            if(!goLine->IsVisible()){
                continue;
            }
            // if weight is 1.0f, put into the vector and draw altogether at once; else, draw as cylinder immediately
            if(goLine->GetWeight() <= 1.0f){
                vertices.emplace_back(goLine->GetPStart().GetPosition());
                vertices.emplace_back(goLine->GetPEnd().GetPosition());
                colors.emplace_back(goLine->GetColor());
                colors.emplace_back(goLine->GetColor());
            } else {
                float radius = goLine->GetWeight() * WEIGHT_TO_CYLINDER_RADIUS_RATE;
                DrawCylinder(goLine->GetPStart().GetPosition(), goLine->GetPEnd().GetPosition(),
                             radius, goLine->GetColor(), glm::vec4(0, 0, 0, 0),
                             getSectorNum(radius));
            }
        }
        DrawLines3d(vertices, colors);
    }

    void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum) {
        std::vector<glm::vec3> vertices; vertices.reserve(sectorNum + 1);
        std::vector<glm::vec3> edges; edges.reserve(2 * sectorNum);
        std::vector<uint32_t> indices; indices.reserve(3 * sectorNum);
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

        DrawTriangles3d(vertices, indices, color);

        for (int i = 1; i < sectorNum; ++i){
            edges.emplace_back(vertices[i]);
            edges.emplace_back(vertices[i + 1]);
        }
        edges.emplace_back(vertices[sectorNum]);
        edges.emplace_back(vertices[1]);

        DrawLines(edges, edgeWeight, edgeColor);
    }

    void DrawCircle(const GOCircle& goCircle) {
        if(!goCircle.IsVisible()){
            return;
        }
        DrawCircle(goCircle.GetCenter().GetPosition(), goCircle.GetNormal(), goCircle.GetRadius(),
                   goCircle.GetColor(), goCircle.GetEdgeColor(), goCircle.GetWeight(), getSectorNum(goCircle.GetRadius()));
    }

    void DrawCircles(const std::vector<std::shared_ptr<GOCircle>>& goCircles) {
        for (const auto &goCircle: goCircles) {
            if(!goCircle->IsVisible()){
                continue;
            }
            DrawCircle(*goCircle);
        }
    }

    void DrawCylinder(const GOCylinder& goCylinder) {
        if(!goCylinder.IsVisible()){
            return;
        }
        DrawCylinder(goCylinder.GetPStart().GetPosition(), goCylinder.GetPEnd().GetPosition(),
                     goCylinder.GetRadius(), goCylinder.GetColor(), goCylinder.GetEdgeColor());
    }

    void DrawCylinders(const std::vector<std::shared_ptr<GOCylinder>>& goCylinders) {
        for (const auto &goCylinder: goCylinders) {
            if(!goCylinder->IsVisible()){
                continue;
            }
            DrawCylinder(*goCylinder);
        }
    }

    void DrawPolyline(const GOPolyline& goPolyline) {
        if(!goPolyline.IsVisible()){
            return;
        }
        vector<glm::vec3> vertices; vertices.reserve(goPolyline.GetPoints().size() * 2);
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

        DrawLines(vertices, goPolyline.GetWeight(), goPolyline.GetColor());
    }

    void DrawPolylines(const std::vector<std::shared_ptr<GOPolyline>>& goPolylines) {
        for(const auto& goPolyline: goPolylines){
            if(!goPolyline->IsVisible()){
                continue;
            }
            DrawPolyline(*goPolyline);
        }
    }

    void DrawTriangle(const GOTriangle& goTriangle) {
        if(!goTriangle.IsVisible()){
            return;
        }
        vector<glm::vec3> vertices = goTriangle.GetVertices();
        vector<uint32_t> indices{0, 1, 2};
        DrawTriangles3d(vertices, indices, goTriangle.GetColor());
    }

    void DrawTriangles(const std::vector<std::shared_ptr<GOTriangle>>& goTriangles) {
        for (const auto &goTriangle: goTriangles) {
            if(!goTriangle->IsVisible()){
                continue;
            }
            DrawTriangle(*goTriangle);
        }
    }

    void DrawMesh(const GOMesh& goMesh) {
        if(!goMesh.IsVisible()){
            return;
        }
        DrawTriangles3d(goMesh.GetVertices(), goMesh.GetIndices(), goMesh.GetColor());
    }

    void DrawMeshes(const std::vector<std::shared_ptr<GOMesh>> &goMeshes) {
        for (auto &goMesh: goMeshes) {
            if(!goMesh->IsVisible()){
                continue;
            }
            DrawMesh(*goMesh);
        }
    }

    void DrawText(const GOText& goText, const glm::mat4 cameraProjection) {
//        glm::vec4 axis = cameraProjection * glm::vec4(goText.GetAnchor().GetPosition(), 1.0);
//        textRenderer.RenderText(goText.GetText(), goText.GetAnchor(), glm::vec4(0,0,0,1), 0.2, cameraProjection);
    }

    void DrawTexts(const std::vector<std::shared_ptr<GOText>> &goTexts) {
        for (auto &goText: goTexts) {
            if(!goText->IsVisible()){
                continue;
            }
        }
    }

    void DrawTest(bool t, glm::mat4 projection){
//        cout << "DrawTest" << endl;
//        std::vector<std::shared_ptr<GOPrimitive>> gos;
//        AIAC_GOREG->GetAllGOs(gos);
//        DrawGO(gos);

        GOPoint pt1 = GOPoint(glm::vec3(1, 1, 1));
        GOPoint pt2 = GOPoint(glm::vec3(2, 25, 2));
//        GOLine line = GOLine(pt1, pt2);
//        line.SetWeight(5.0);
//        line.SetColor(glm::vec4(1, 0, 0, 1));
//        DrawLine(line);

        std::vector<std::shared_ptr<GOPoint>> points;
        std::vector<std::shared_ptr<GOLine>> lines;
        std::vector<std::shared_ptr<GOCircle>> circles;
        std::vector<std::shared_ptr<GOCylinder>> cylinders;
        std::vector<std::shared_ptr<GOPolyline>> polylines;
        std::vector<std::shared_ptr<GOTriangle>> triangles;
        std::vector<std::shared_ptr<GOMesh>> meshes;
        std::vector<std::shared_ptr<GOText>> texts;
        AIAC_GOREG->GetAllGOs(points, lines, circles, cylinders, polylines, triangles, meshes, texts);

        GOText text1 = GOText("test", pt1, 10);
//        DrawText(text1);
//
//        cout << points.size();
//        DrawPoints(points);
//        DrawLines(lines);
//        DrawPolylines(polylines);
//        DrawTriangles(triangles);
//
//        DrawCylinders(cylinders);
//        DrawCircles(circles);
//        DrawMeshes(meshes);

//        textRenderer.RenderText("Hello World", 0, 0, 40, glm::vec3(1, 0, 0));
//        textRenderer.RenderText("goText.GetText()", 0, 0, 1, glm::vec4(0,0,0,0.5), projection);
//        DrawTexts(texts);
//        if(!textRenderer.IsInitialized()){ textRenderer.Init(); }
//        textRenderer.RenderText("goText.GetText()", 0, 0, 0.1, glm::vec4(0,0,0,0.5), projection);
    }


}
