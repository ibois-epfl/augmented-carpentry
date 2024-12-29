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
#include <ft2build.h>
#include FT_FREETYPE_H

#include "GlUtils.h"
#include "RenderAPI.h"
#include "TextRenderer.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void DrawAllGOs(glm::mat4 projection, float textScale)
    {
        std::vector<std::shared_ptr<GOPrimitive>> gos;
        AIAC_GOREG->GetAllGOs(gos);
        
        std::vector<std::shared_ptr<GOPrimitive>> goTexts;
        for(auto& go: gos){
            if(!go->IsVisible()){
                continue;
            }
            if(go->GetType() == _GOText){
                if (textScale > 0) goTexts.emplace_back(go);
            } else{
                DrawGO(go);
            }
        }

        if (textScale > 0) {
            TextRenderer::SetProjection(projection);
            for(auto& goText: goTexts){
                DrawText(*std::dynamic_pointer_cast<GOText>(goText), textScale);
            }
        }
    }

    void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive)
    {
        switch (goPrimitive->GetType()){
            case _GOPoint:
            case _GOLine:
            case _GOCylinder:
            case _GOCircle:
            case _GOPolyline:
            case _GOTriangle:
            case _GOMesh:
                goPrimitive->Draw(); break;
            case _GOText:
                DrawText(*std::dynamic_pointer_cast<GOText>(goPrimitive)); break;
                break;

            default:
                break;
        }
    }

    void DrawText(const GOText& goText, float scale, const glm::mat4& projection) {
        if(projection != glm::mat4(1.0f)){
            TextRenderer::SetProjection(projection);
        }
        TextRenderer::RenderTextIn3DSpace(
                goText.GetText(),
                goText.GetAnchor(),
                goText.GetColor(),
                goText.GetTextSize() * scale);

    }

    void DrawTexts(const std::vector<std::shared_ptr<GOText>> &goTexts, float scale, const glm::mat4& projection) {
        if(projection != glm::mat4(1.0f)){
            TextRenderer::SetProjection(projection);
        }
        for (auto &goText: goTexts) {
            if(!goText->IsVisible()){
                continue;
            }
            DrawText(*goText, scale, projection);
        }
    }

    void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize)
    {
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
        glDrawLines3d(markerEdges, markerEdgeColors);
    }

    // int getSectorNum(float radius){
    //     return 8;
    // }

    /**
     * The following functions are deprecated since the create/delete
     * OpenGL objects every time they are called, which is not prefered
     * way to do it. However, I keep them here for future reference in case
     * we need it in the future.
     */

    // void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight, const glm::vec4 &color)
    // {
    //     if(weight <= 0){
    //         return;
    //     }
    //     if(weight == 1.0f){
    //         vector<glm::vec3> line;
    //         line.emplace_back(p1);
    //         line.emplace_back(p2);
    //         glDrawLines3d(line, color);
    //         return;
    //     }
    //     float radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE;
    //     DrawCylinder(p1, p2, radius,
    //                  color, glm::vec4(0,0,0,0), getSectorNum(radius));
    // }

    // void DrawLines(const vector<glm::vec3> &vertices, float weight, const glm::vec4 &color)
    // {
    //     if(weight <= 0){
    //         return;
    //     }
    //     if(weight == 1.0f){
    //         glDrawLines3d(vertices, color);
    //         return;
    //     }
    //     float radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE;
    //     DrawCylinder(vertices[0], vertices[1], radius,
    //                  color, glm::vec4(0,0,0,0), getSectorNum(radius));
    // }

    // void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum)
    // {
    //     std::vector<glm::vec3> vertices; vertices.reserve(sectorNum + 1);
    //     std::vector<glm::vec3> edges; edges.reserve(2 * sectorNum);
    //     std::vector<uint32_t> indices; indices.reserve(3 * sectorNum);
    //     vertices.emplace_back(center);

    //     glm::vec3 newX = glm::cross(normal, glm::vec3(0, 1, 0));
    //     glm::vec3 newZ = glm::cross(newX, normal);

    //     glm::mat4 transformMat;

    //     transformMat[0] = glm::vec4(newX, 0);
    //     transformMat[1] = glm::vec4(normal, 0);
    //     transformMat[2] = glm::vec4(newZ, 0);
    //     transformMat[3] = glm::vec4(center, 1);

    //     for (int i = 0; i < sectorNum; ++i){
    //         GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
    //         glm::vec3 vertex = transformMat * glm::vec4(
    //                 static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
    //                 0,
    //                 static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
    //                 1
    //         );
    //         vertices.emplace_back(vertex);
    //     }

    //     for (int i = 1; i < sectorNum; ++i){
    //         indices.emplace_back(0);
    //         indices.emplace_back(i);
    //         indices.emplace_back(i + 1);
    //     }
    //     indices.emplace_back(0);
    //     indices.emplace_back(sectorNum);
    //     indices.emplace_back(1);

    //     glDrawTriangles3d(vertices, indices, color);

    //     for (int i = 1; i < sectorNum; ++i){
    //         edges.emplace_back(vertices[i]);
    //         edges.emplace_back(vertices[i + 1]);
    //     }
    //     edges.emplace_back(vertices[sectorNum]);
    //     edges.emplace_back(vertices[1]);

    //     DrawLines(edges, edgeWeight, edgeColor);
    // }


    // void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum){
    //     std::vector<CylinderPole> cylinderPoles; // vector of structs

    //     glm::vec3 x1 = baseCenter, x2 = topCenter;
    //     glm::vec3 norm = glm::normalize(x2 - x1);
    //     GLfloat h = glm::length(x2 - x1);

    //     glm::vec3 newX = glm::cross(norm, glm::vec3(0, 1, 0));
    //     glm::vec3 newZ = glm::cross(newX, norm);

    //     glm::mat4 transformMat;

    //     transformMat[0] = glm::vec4(newX, 0);
    //     transformMat[1] = glm::vec4(norm, 0);
    //     transformMat[2] = glm::vec4(newZ, 0);
    //     transformMat[3] = glm::vec4(x1, 1);

    //     for (int i = 0; i < sectorNum; ++i){
    //         GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
    //         CylinderPole cp{
    //                 .x = static_cast<GLfloat>(radius * cos(2 * M_PI * u)),
    //                 .z = static_cast<GLfloat>(radius * sin(2 * M_PI * u)),
    //         };
    //         cylinderPoles.push_back(cp);
    //     }

    //     vector<uint32_t> flattenedIndices;
    //     vector<glm::vec3> indices;
    //     vector<glm::vec3> vertices;
    //     vector<glm::vec3> capContourTop, capContourBase;

    //     vertices.emplace_back(x1); // 0
    //     vertices.emplace_back(x2); // 1

    //     vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z)); // 2
    //     vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z)); // 3

    //     capContourBase.push_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
    //     capContourTop.push_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));

    //     int baseCenterIdx = 0;
    //     int topCenterIdx = 1;
    //     int prevBaseVertexIdx = 2;
    //     int prevTopVertexIdx = 3;
    //     int curBaseVertexIdx = 4;
    //     int curTopVertexIdx = 5;

    //     for(int i = 1; i < sectorNum; i++){
    //         capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
    //         capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
    //         capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));
    //         capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

    //         vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, 0, cylinderPoles[i].z));
    //         vertices.emplace_back(GetTransformed(transformMat, cylinderPoles[i].x, h, cylinderPoles[i].z));

    //         indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
    //         indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
    //         indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
    //         indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

    //         prevBaseVertexIdx = curBaseVertexIdx;
    //         prevTopVertexIdx = curTopVertexIdx;
    //         curBaseVertexIdx += 2;
    //         curTopVertexIdx += 2;
    //     }

    //     // Last one
    //     curBaseVertexIdx = 2;
    //     curTopVertexIdx = 3;
    //     indices.emplace_back(curBaseVertexIdx ,baseCenterIdx   , prevBaseVertexIdx);
    //     indices.emplace_back(prevTopVertexIdx ,topCenterIdx    , curTopVertexIdx  );
    //     indices.emplace_back(curBaseVertexIdx ,curTopVertexIdx , prevTopVertexIdx );
    //     indices.emplace_back(prevBaseVertexIdx,curBaseVertexIdx, prevTopVertexIdx );

    //     capContourBase.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, 0, cylinderPoles[0].z));
    //     capContourTop.emplace_back(GetTransformed(transformMat, cylinderPoles[0].x, h, cylinderPoles[0].z));

    //     for(auto vid: indices){
    //         flattenedIndices.push_back((uint)vid.x);
    //         flattenedIndices.push_back((uint)vid.y);
    //         flattenedIndices.push_back((uint)vid.z);
    //     }

    //     glDrawTriangles3d(vertices, flattenedIndices, color);
    //     glDrawLines3d(capContourBase, edgeColor);
    //     glDrawLines3d(capContourTop, edgeColor);
    // }
}
