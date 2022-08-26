#include "aiacpch.h"

#include "AIAC/LayerModel.h"
#include "AIAC/GOSys/GO.h"
#include "AIAC/Application.h"

namespace AIAC
{
    LayerModel::LayerModel() {}
    
    void LayerModel::OnAttach()
    {
        // TEST
        std::shared_ptr<GOPoint> pt1 = std::make_shared<GOPoint>(GOPoint(glm::vec3(1, 1, 1)));
        std::shared_ptr<GOPoint> pt2 = std::make_shared<GOPoint>(GOPoint(glm::vec3(2, 2, 2)));
        std::shared_ptr<GOPoint> pt3 = std::make_shared<GOPoint>(GOPoint(glm::vec3(3, 3, 3)));

        const uint32_t id = pt1->GetId();
        cout << "id: " << id << endl;
        // // GOPoint pt1(glm::vec3(1, 1, 1));

        // // AIAC_GOREG->Register(pt1.GetSharedPtr());

        AIAC_GOREG->Register(pt1);
        // AIAC_GOREG->Register(pt2);
        // AIAC_GOREG->Register(pt3);

        // // // print the content of the registry
        // // cout << AIAC_GOREG->Count() << endl;
        // auto aa = AIAC_GOREG->GetGO<GOPoint>(id);
        auto aa = AIAC_GOREG->GetGO(id);

        // use std::visit to get the GO from the registry


        // get GOPoint from variant
        std::visit([](auto&& arg) {
            cout << "type: " << arg->GetGOType() << endl;
        }, aa);


        cout << typeid(aa).name() << endl;
        // cout << aa->X() << endl;


        // cout << AIAC_GOREG->Count() << endl;


        // m_ModelLoader = ModelLoader();
    }
    void LayerModel::OnFrameStart()
    {
    }
}