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

#include "AIAC/Layer.h"
#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Feedback/CutChainSawFeedback.h"
#include "AIAC/Feedback/CutCircularSawFeedback.h"
#include "AIAC/Feedback/HoleFeedback.h"

namespace AIAC
{
    class LayerFeedback : public AIAC::Layer
    {
    public:
        LayerFeedback();
        virtual ~LayerFeedback() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    public:
        bool ToShowCutPlane = false;
        void EnableCutPlane(bool enable)
        {
            ToShowCutPlane = enable;
            m_CutChainSawFeedback.EnableCutPlane(enable);
            m_CutCircularSawFeedback.EnableCutPlane(enable);
        };

        inline void DeactivateCurrentFeedbackVisibility() { m_IsCurrentFabFeedbackVisible = false; }
        inline void ActivateCurrentFeedbackVisibility() { m_IsCurrentFabFeedbackVisible = true; }

        FabFeedback* GetCurrentFabFeedback() { return m_CurrentFabFeedbackPtr; };

    private:
        HoleFeedback m_HoleFeedback;
        CutChainSawFeedback m_CutChainSawFeedback;
        CutCircularSawFeedback m_CutCircularSawFeedback;

        FabFeedback* m_CurrentFabFeedbackPtr = nullptr;
        bool m_IsCurrentFabFeedbackVisible = true;
    };
}