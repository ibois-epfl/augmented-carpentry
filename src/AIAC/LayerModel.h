#pragma once

#include "Config.h"
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

        inline ACInfoModel& GetACInfoModel() { return m_ACInfoModel; }
        inline ScannedModel& GetScannedModel() { return m_ScannedModel; }
        /**
         * @brief Change the align offset. The value is in TSLAM unit.
         */
        inline void AddAlignOffset(float diff) {
            m_AlignOffset += diff;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, m_AlignOffset);
        }

        /**
         * @brief Reset the align offset to 0 (Center).
         */
        inline void ResetAlignOffset() {
            m_AlignOffset = 0.0f;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, 0.0f);
        };

        /**
         * @brief Change the align rotation. The value is in degree.
         * @param diff +1 or -1 to rotate 90 degree (counter-)clock wise.
         */
        inline void ChangeAlignRotation(int diff) {
            m_AlignRotation += diff;
            if (m_AlignRotation < 0) m_AlignRotation += 4;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_ROTATION, m_AlignRotation);
        }

        /**
         * @brief Reset the align rotation to 0 (No rotation).
         */
        inline void ResetAlignRotation() {
            m_AlignRotation = 0;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_ROTATION, 0);
        }

        /**
         * @brief Change the align flip.
         */
        inline void FlipAlign() {
            m_AlignFlip = !m_AlignFlip;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_FLIP, m_AlignFlip);
        }

        /**
         * @brief Reset the align flip to false (No flip).
         */
        inline void ResetAlignFlip() {
            m_AlignFlip = false;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_FLIP, false);
        }

    private:
        // ModelLoader m_ModelLoader;
        ACInfoModel m_ACInfoModel;
        ScannedModel m_ScannedModel;
        float m_AlignOffset = 0.0f;
        int m_AlignRotation = 0;
        bool m_AlignFlip = false;
    };
}