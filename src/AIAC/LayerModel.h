#pragma once

#include "AIAC/Layer.h"


namespace AIAC
{
    //TODO: create model loader class to import .ply but also custom .aiac/.xml
    struct Model
    {
        std::string FilePath;
    };


    class LayerModel : public AIAC::Layer
    {
    public:
        LayerModel();
        virtual ~LayerModel() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    private:
        // ModelLoader m_ModelLoader;
        Model m_CurrentModel;
    };
}