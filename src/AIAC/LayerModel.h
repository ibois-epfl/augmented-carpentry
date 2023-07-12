#pragma once

#include "AIAC/Layer.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "ACInfoModel.h"
#include "ScannedModel.h"


namespace AIAC
{
    class LayerModel : public AIAC::Layer
    {
    public:
        LayerModel();
        virtual ~LayerModel() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        /**
         * @brief transform the ACInfoModel to the ScannedModel
         */
        void AlignModels();

    private:
        // ModelLoader m_ModelLoader;
        ACInfoModel m_ACInfoModel;
        ScannedModel m_ScannedModel;
    };
}