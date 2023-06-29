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

        std::vector<std::string> GetACInfoTimberIDs() const { return m_ACInfoModel.GetTimberIDs(); };
        void SetActiveACInfoTimber(const std::string& id) { m_ACInfoModel.SetActiveTimberInfo(id); };
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