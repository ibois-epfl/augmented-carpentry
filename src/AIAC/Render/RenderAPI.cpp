#include "RenderAPI.h"
#include "AIAC/Log.h"

namespace AIAC
{
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

    void reshape(int w, int h)
    {
        glViewport(0,0,(GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1,1,-1,1,1.5,20);
        gluLookAt(1,0,8,1,0,-1,0,1,0);

    }

    struct CylinderPole {
        GLfloat x, z, yBase, yTop;
    };

    void DrawTest(bool t){
        std::vector<CylinderPole> cylinderPoles; // vector of structs

        //Cylinder with y axis up
        GLfloat h = 10.0f, radius = 5.0f;
        int sectorNum = 24;
        glm::mat4 quad = glm::mat4(1.0f);
        if(t){
            quad[3][0] = -10.0f;
            quad[3][1] = -10.0f;
            quad[3][2] = -10.0f;
        }


        for (int i = 0; i < sectorNum; ++i)
        {
            GLfloat u = (GLfloat)i / (GLfloat)sectorNum;
            CylinderPole cp;

            //Where the cylinder is in the x and z positions (3D space)
            cp.x = radius * cos(2 * M_PI * u);
            cp.z = radius * sin(2 * M_PI * u);
            cp.yBase = 0.0f;
            cp.yTop = h;

            cylinderPoles.push_back(cp);
        }

        glm::vec3 topCenter(0.0f, h, 0.0f), baseCenter(0.0f, 0.0f, 0.0f);

        vector<uint32_t> flattenedIndices;
        vector<glm::vec3> indices;
        vector<glm::vec3> vertices;
        vector<glm::vec3> capContourTop, capContourBase;

        vertices.push_back(baseCenter); // 0
        vertices.push_back(topCenter);  // 1

        vertices.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yBase, cylinderPoles[0].z); // 2
        vertices.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yTop, cylinderPoles[0].z);  // 3

        capContourBase.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yBase, cylinderPoles[0].z);
        capContourTop.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yTop, cylinderPoles[0].z);

        int baseCenterIdx = 0;
        int topCenterIdx = 1;
        int prevBaseVertexIdx = 2;
        int prevTopVertexIdx = 3;
        int curBaseVertexIdx = 4;
        int curTopVertexIdx = 5;

        for(int i = 1; i < sectorNum; i++){
            capContourBase.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yBase, cylinderPoles[i].z);
            capContourBase.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yBase, cylinderPoles[i].z);
            capContourTop.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yTop, cylinderPoles[i].z);
            capContourTop.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yTop, cylinderPoles[i].z);

            vertices.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yBase, cylinderPoles[i].z);
            vertices.emplace_back(cylinderPoles[i].x, cylinderPoles[i].yTop, cylinderPoles[i].z);

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

        capContourBase.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yBase, cylinderPoles[0].z);
        capContourTop.emplace_back(cylinderPoles[0].x, cylinderPoles[0].yTop, cylinderPoles[0].z);

        for(auto vid: indices){
            flattenedIndices.push_back((uint)vid.x);
            flattenedIndices.push_back((uint)vid.y);
            flattenedIndices.push_back((uint)vid.z);
        }

        for(auto &v: vertices){
            glm::vec4 tv = quad * glm::vec4(v, 1.0f);
            v = glm::vec3(tv.x, tv.y, tv.z);
        }

        DrawTriangles3d(vertices, flattenedIndices, glm::vec4(.6f, .06f, 0.0f, .5f));
        DrawLines3d(capContourBase, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        DrawLines3d(capContourTop, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }
}
