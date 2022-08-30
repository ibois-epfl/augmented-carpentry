#include "aiacpch.h"

#include "AIAC/LayerModel.h"
#include "AIAC/GOSys/GO.h"
#include "AIAC/Application.h"
#include "AIAC/DLoader.h"

//TODO: add the 3D model importer

namespace AIAC
{
    LayerModel::LayerModel() {}
    
    void LayerModel::OnAttach()
    {
        // TODO: erase once the render parsing is done
        // there is no need for shared_ptr anymore, because the GO is registered in the registry at construction
        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>
        GOPoint pt1 = GOPoint(glm::vec3(1, 1, 1));
        GOPoint pt2 = GOPoint(glm::vec3(20, 50, 20));
        GOPoint pt3 = GOPoint(glm::vec3(30, 30, 30));
        GOLine line = GOLine(pt1, pt2);
        GOLine line2 = GOLine(pt1, pt3);
        line.SetWeight(4.0);
        line2.SetWeight(16.0);
        GOCircle circle1 = GOCircle(pt1, 0.5f);
        GOCircle circle2 = GOCircle(pt2, 0.5f);
        GOCircle circle3 = GOCircle(pt3, 0.5f);
        GOCylinder cylinder1 = GOCylinder(pt1, pt2, 0.5f);
        GOCylinder cylinder2 = GOCylinder(pt2, pt3, 0.5f);
        GOCylinder cylinder3 = GOCylinder(pt3, pt1, 0.5f);
        GOPolyline polyline1 = GOPolyline(std::vector<GOPoint>{pt1, pt2, pt3});
        GOPolyline polyline2 = GOPolyline(std::vector<GOPoint>{pt2, pt3, pt1});
        GOPolyline polyline3 = GOPolyline(std::vector<GOPoint>{pt3, pt1, pt2});
        GOTriangle triangle1 = GOTriangle(pt1, pt2, pt3);
        GOTriangle triangle2 = GOTriangle(pt2, pt3, pt1);
        GOTriangle triangle3 = GOTriangle(pt3, pt1, pt2);
        GOMesh mesh1 = GOMesh(std::vector<glm::vec3>{pt1, pt2, pt3}, std::vector<uint32_t>{0,1,2});
        GOText text1 = GOText("Hello World1", pt1, 0.5f);
        GOText text2 = GOText("Hello World2", pt2, 0.5f);
        GOText text3 = GOText("Hello World3", pt3, 0.5f);
        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>

        DLoader dloader = DLoader();
        GOMesh meshT = GOMesh();
        dloader.LoadGOMesh("assets/models/drill_scaled_1000.obj", meshT);


    }
    void LayerModel::OnFrameStart()
    {


    }
}