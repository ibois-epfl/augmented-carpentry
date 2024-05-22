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
        void LoadACInfoModel(const std::string& path);

        /**
         * @brief Load a .ply model from a file.
         */
        void LoadScannedModel(const std::string& path);

        /**
         * @brief Return the filepath to the loaded ACInfoModel.
         */
        inline const std::string& GetACInfoModelPath() const { return m_ACInfoModelPath; }

        /**
         * @brief Return the filepath to the loaded ScannedModel.
         */
        inline const std::string& GetScannedModelPath() const { return m_ScannedModelPath; }

        /**
         * @brief Return the ACInfoModel.
         */
        inline ACInfoModel& GetACInfoModel() { return m_ACInfoModel; }

        /**
         * @brief Get the Scanned Model object
         */
        inline ScannedModel& GetScannedModel() { return m_ScannedModel; }

        /**
         * @brief Get the Align Offset of the model
         */
        inline float GetAlignOffset() { return m_AlignOffset; }

        /**
         * @brief Get the rotation position of the model
         */
        inline int GetAlignRotation() const { return m_AlignRotation; }

        /**
         * @brief Get the flip status of the model
         */
        inline bool GetAlignFlip() const { return m_AlignFlip; }

        /**
         * @brief Get the transform matrix of the model
         */
        inline glm::mat4x4 GetTransformMat() const { return m_CumulativeTransformMat; }

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
         * @brief Set the offset make it align to one end.
         */
        inline void ForceAlignToEnd(bool leftOrRight) {
            m_AlignOffset = (m_ACInfoModel.GetLength() - m_ScannedModel.GetLength());
            if (leftOrRight) m_AlignOffset = -m_AlignOffset;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, m_AlignOffset);
        }

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
        std::string m_ACInfoModelPath;
        std::string m_ScannedModelPath;

        // ModelLoader m_ModelLoader;
        ACInfoModel m_ACInfoModel;
        ScannedModel m_ScannedModel;
        float m_AlignOffset = 0.0f;
        int m_AlignRotation = 0;
        bool m_AlignFlip = false;

        // The cumulative transformation matrix of the model, from ACIM to ScannedModel, regarding the offset, rotation, and flip.
        // Since the model is transformed multiple times relatively during adjusting, we need to recorded it in this way.
        glm::mat4x4 m_CumulativeTransformMat = glm::mat4(1.0f);
    };
}