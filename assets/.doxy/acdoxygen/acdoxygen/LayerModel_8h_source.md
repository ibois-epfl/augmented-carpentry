

# File LayerModel.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerModel.h**](LayerModel_8h.md)

[Go to the documentation of this file](LayerModel_8h.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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

        void AlignModels();

        void LoadACInfoModel(const std::string& path);

        void ReloadACInfoModel();

        void LoadScannedModel(const std::string& path);

        inline const std::string& GetACInfoModelPath() const { return m_ACInfoModelPath; }

        inline const std::string GetACInfoModelName() const { return m_ACInfoModel.GetName(); }

        inline const std::string& GetScannedModelPath() const { return m_ScannedModelPath; }

        inline ACInfoModel& GetACInfoModel() { return m_ACInfoModel; }

        inline ScannedModel& GetScannedModel() { return m_ScannedModel; }

        inline float GetAlignOffset() { return m_AlignOffset; }

        inline int GetAlignRotation() const { return m_AlignRotation; }

        inline bool GetAlignFlip() const { return m_AlignFlip; }

        inline glm::mat4x4 GetTransformMat() const { return m_ACIMTransformMat; }

        inline void AddAlignOffset(float diff) {
            m_AlignOffset += diff;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, m_AlignOffset);
        }

        inline void ResetAlignOffset() {
            m_AlignOffset = 0.0f;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, 0.0f);
        };

        inline void ForceAlignToEnd(bool leftOrRight) {
            m_AlignOffset = (m_ACInfoModel.GetLength() - m_ScannedModel.GetLength());
            if (leftOrRight) m_AlignOffset = -m_AlignOffset;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_OFFSET, m_AlignOffset);
        }

        inline void ChangeAlignRotation(int diff) {
            m_AlignRotation += diff;
            if (m_AlignRotation < 0) m_AlignRotation += 4;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_ROTATION, m_AlignRotation);
        }

        inline void ResetAlignRotation() {
            m_AlignRotation = 0;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_ROTATION, 0);
        }

        inline void FlipAlign() {
            m_AlignFlip = !m_AlignFlip;
            AlignModels();
            Config::UpdateEntry(Config::SEC_AIAC, Config::ALIGN_FLIP, m_AlignFlip);
        }

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

        // Abandon as now everytime when alignment happens it's re-calculated
        // glm::mat4x4 m_CumulativeTransformMat = glm::mat4(1.0f);

        glm::mat4x4 m_ACIMTransformMat;
    };
}
```


