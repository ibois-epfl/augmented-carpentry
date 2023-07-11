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

        /**
         * @brief Load a .acim model from a file.
         */
        void LoadACInfoModel(std::string path);

        /**
         * @brief Load a .ply model from a file.
         */
        void LoadScannedModel(std::string path);

        /**
         * @brief Change the align offset. The value is in TSLAM unit.
         */
        inline void AddAlignOffset(float diff) { m_AlignOffset += diff; AlignModels(); }

        /**
         * @brief Reset the align offset to 0 (Center).
         */
        inline void ResetAlignOffset() { m_AlignOffset = 0.0f; AlignModels(); };

    private:
        // ModelLoader m_ModelLoader;
        ACInfoModel m_ACInfoModel;
        ScannedModel m_ScannedModel;
        float m_AlignOffset = 0.0f;
    };
}