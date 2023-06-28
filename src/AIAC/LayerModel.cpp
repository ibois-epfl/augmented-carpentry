#include "aiacpch.h"

#include "AIAC/LayerModel.h"
#include "AIAC/GOSys/GO.h"
#include "AIAC/Application.h"
#include "AIAC/DLoader.h"
#include "GeometryUtils.h"
#include "glm/gtx/string_cast.hpp"

//TODO: add the 3D model importer

namespace AIAC
{
    LayerModel::LayerModel() {}
    
    void LayerModel::OnAttach()
    {
        m_ACInfoModel.Load("assets/ACModel/test.acim");
        m_ScannedModel.Load("assets/ACModel/01_scanned_model.ply");

        vector<glm::vec3> cadBox = {
                {0.0,0.0,7.0},
                {7.0,0.0,7.0},
                {7.0,0.0,0.0},
                {0.0,0.0,0.0},
                {0.0,48.0,7.0},
                {7.0,48.0,7.0},
                {7.0,48.0,0.0},
                {0.0,48.0,0.0}
        };

        vector<glm::vec3> fabBox = {
                {42.5765991211,-16.7697906494,36.6605987549},
                {43.1363983154,-11.2471008301,32.6360015869},
                {45.5475006104,-15.2264785767,27.5181999207},
                {44.9822006226,-20.7733116150,31.5688991547},
                {-50.3394012451,-29.9007606506,2.74846005440},
                {-49.7759017944,-24.3774700165,-1.27487003803},
                {-47.3773002625,-28.3247394562,-6.35024976730},
                {-47.9462013245,-33.8720016479,-2.30100011826}
        };

        auto transMat = GetRigidTransformationMatrix(cadBox, fabBox);
        cout << glm::to_string(transMat) << endl;
//        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>
//        uint32_t idPt1 = GOPoint::Add(1, 1, 1, 5.0f);
//        uint32_t idPt2 = GOPoint::Add(20, 50, 20, 5.0f);
//        uint32_t idPt3 = GOPoint::Add(30, 30, 30, 5.0f);
//        auto pt1 = GOPoint::Get(idPt1);
//        auto pt2 = GOPoint::Get(idPt2);
//        auto pt3 = GOPoint::Get(idPt3);
//
//        uint32_t line = GOLine::Add(*pt1, *pt2, 3.0f);
//        uint32_t line2 = GOLine::Add(*pt1, *pt3, 3.0f);
//        uint32_t circle1 = GOCircle::Add(*pt1, 30.5f);
//        uint32_t circle2 = GOCircle::Add(*pt2, 0.5f);
//        uint32_t circle3 = GOCircle::Add(*pt3, 0.5f);
//        uint32_t cylinder1 = GOCylinder::Add(*pt1, *pt2, 0.5f);
//        uint32_t cylinder2 = GOCylinder::Add(*pt2, *pt3, 0.5f);
//        uint32_t cylinder3 = GOCylinder::Add(*pt3, *pt1, 0.5f);
//        uint32_t polyline1 = GOPolyline::Add(std::vector<GOPoint>{*pt1, *pt2, *pt3});
//        uint32_t polyline2 = GOPolyline::Add(std::vector<GOPoint>{*pt2, *pt3, *pt1});
//        uint32_t polyline3 = GOPolyline::Add(std::vector<GOPoint>{*pt3, *pt1, *pt2});
//        uint32_t triangle1 = GOTriangle::Add(*pt1, *pt2, *pt3);
//        uint32_t triangle2 = GOTriangle::Add(*pt2, *pt3, *pt1);
//        uint32_t triangle3 = GOTriangle::Add(*pt3, *pt1, *pt2);
//        uint32_t mesh1 = GOMesh::Add(std::vector<glm::vec3>{*pt1, *pt2, *pt3}, std::vector<uint32_t>{0,1,2});
//        uint32_t text1 = GOText::Add("Hello World1", *pt1, 1.0f);
//        GOText::Remove(text1);
//        uint32_t text2 = GOText::Add("Hello World2", *pt2, 1.0f);
//        uint32_t text3 = GOText::Add("Hello World3", *pt3, 1.0f);
//        // >>>>>>>>>>>>>> TEST for the Render parsing >>>>>>>>>>>>>>

    }
    void LayerModel::OnFrameStart()
    {


    }

    void LayerModel::AlignModels() {
    }
}