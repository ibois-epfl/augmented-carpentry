#include "aiacpch.h"

#include "AIAC/LayerModel.h"
#include "AIAC/GOSys/GO.h"
#include "AIAC/Application.h"


//TODO: add the 3D model importer

namespace AIAC
{
    LayerModel::LayerModel() {}
    
    void LayerModel::OnAttach()
    {
        // TODO: erase once the render parsing is done
        // there is no need for shared_ptr anymore, because the GO is registered in the registry at construction
        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>
        std::shared_ptr<GOPoint> pt1 = std::make_shared<GOPoint>(GOPoint(glm::vec3(1, 1, 1)));
        std::shared_ptr<GOPoint> pt2 = std::make_shared<GOPoint>(GOPoint(glm::vec3(2, 5, 2)));
        std::shared_ptr<GOPoint> pt3 = std::make_shared<GOPoint>(GOPoint(glm::vec3(3, 3, 3)));
        std::shared_ptr<GOLine> line1 = std::make_shared<GOLine>(GOLine(*pt1, *pt2));
        std::shared_ptr<GOLine> line2 = std::make_shared<GOLine>(GOLine(*pt2, *pt3));
        std::shared_ptr<GOLine> line3 = std::make_shared<GOLine>(GOLine(*pt3, *pt1));
        std::shared_ptr<GOCircle> circle1 = std::make_shared<GOCircle>(GOCircle(*pt1, 10.5f));
        std::shared_ptr<GOCircle> circle2 = std::make_shared<GOCircle>(GOCircle(*pt2, 5.5f));
        std::shared_ptr<GOCircle> circle3 = std::make_shared<GOCircle>(GOCircle(*pt3, 5.5f));
        std::shared_ptr<GOCylinder> cylinder1 = std::make_shared<GOCylinder>(GOCylinder(*pt1, *pt2, 0.5f));
        std::shared_ptr<GOCylinder> cylinder2 = std::make_shared<GOCylinder>(GOCylinder(*pt2, *pt3, 0.5f));
        std::shared_ptr<GOCylinder> cylinder3 = std::make_shared<GOCylinder>(GOCylinder(*pt3, *pt1, 0.5f));
        std::shared_ptr<GOPolyline> polyline1 = std::make_shared<GOPolyline>(std::vector<GOPoint>{*pt1, *pt2, *pt3});
//        std::shared_ptr<GOPolyline> polyline2 = std::make_shared<GOPolyline>(std::vector<GOPoint>{*pt2, *pt3, *pt1});
//        std::shared_ptr<GOPolyline> polyline3 = std::make_shared<GOPolyline>(std::vector<GOPoint>{*pt3, *pt1, *pt2});
        std::shared_ptr<GOTriangle> triangle1 = std::make_shared<GOTriangle>(GOTriangle(*pt1, *pt2, *pt3));
        std::shared_ptr<GOTriangle> triangle2 = std::make_shared<GOTriangle>(GOTriangle(*pt2, *pt3, *pt1));
        std::shared_ptr<GOTriangle> triangle3 = std::make_shared<GOTriangle>(GOTriangle(*pt3, *pt1, *pt2));
        std::shared_ptr<GOMesh> mesh1 = std::make_shared<GOMesh>(std::vector<glm::vec3>{*pt1, *pt2, *pt3}, std::vector<uint32_t>{0,1,2});
        std::shared_ptr<GOText> text1 = std::make_shared<GOText>(GOText("Hello World1", *pt1, 0.5f));
        std::shared_ptr<GOText> text2 = std::make_shared<GOText>(GOText("Hello World2", *pt2, 0.5f));
        std::shared_ptr<GOText> text3 = std::make_shared<GOText>(GOText("Hello World3", *pt3, 0.5f));


        // // EXAMPLE how to get the GO from the registry in render
        // std::vector<std::shared_ptr<GOPoint>> points;
        // std::vector<std::shared_ptr<GOLine>> lines;
        // std::vector<std::shared_ptr<GOCircle>> circles;
        // std::vector<std::shared_ptr<GOCylinder>> cylinders;
        // std::vector<std::shared_ptr<GOPolyline>> polylines;
        // std::vector<std::shared_ptr<GOTriangle>> triangles;
        // std::vector<std::shared_ptr<GOText>> texts;
        // AIAC_GOREG->GetAllGOs(points, lines, circles, cylinders, polylines, triangles, texts);



    }
    void LayerModel::OnFrameStart()
    {

    }
}