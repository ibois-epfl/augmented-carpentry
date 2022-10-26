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
        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>
        uint32_t idPt1 = GOPoint::Add(1, 1, 1, 5.0f);
        uint32_t idPt2 = GOPoint::Add(20, 50, 20, 5.0f);
        uint32_t idPt3 = GOPoint::Add(30, 30, 30, 5.0f);
        auto pt1 = GOPoint::Get(idPt1);
        auto pt2 = GOPoint::Get(idPt2);
        auto pt3 = GOPoint::Get(idPt3);

        uint32_t line = GOLine::Add(*pt1, *pt2, 3.0f);
        uint32_t line2 = GOLine::Add(*pt1, *pt3, 3.0f);
        uint32_t circle1 = GOCircle::Add(*pt1, 30.5f);
        uint32_t circle2 = GOCircle::Add(*pt2, 0.5f);
        uint32_t circle3 = GOCircle::Add(*pt3, 0.5f);
        uint32_t cylinder1 = GOCylinder::Add(*pt1, *pt2, 0.5f);
        uint32_t cylinder2 = GOCylinder::Add(*pt2, *pt3, 0.5f);
        uint32_t cylinder3 = GOCylinder::Add(*pt3, *pt1, 0.5f);
        uint32_t polyline1 = GOPolyline::Add(std::vector<GOPoint>{*pt1, *pt2, *pt3});
        uint32_t polyline2 = GOPolyline::Add(std::vector<GOPoint>{*pt2, *pt3, *pt1});
        uint32_t polyline3 = GOPolyline::Add(std::vector<GOPoint>{*pt3, *pt1, *pt2});
        uint32_t triangle1 = GOTriangle::Add(*pt1, *pt2, *pt3);
        uint32_t triangle2 = GOTriangle::Add(*pt2, *pt3, *pt1);
        uint32_t triangle3 = GOTriangle::Add(*pt3, *pt1, *pt2);
        uint32_t mesh1 = GOMesh::Add(std::vector<glm::vec3>{*pt1, *pt2, *pt3}, std::vector<uint32_t>{0,1,2});
        uint32_t text1 = GOText::Add("Hello World1", *pt1, 1.0f);
        uint32_t text2 = GOText::Add("Hello World2", *pt2, 1.0f);
        uint32_t text3 = GOText::Add("Hello World3", *pt3, 1.0f);
        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>

    }
    void LayerModel::OnFrameStart()
    {


    }
}