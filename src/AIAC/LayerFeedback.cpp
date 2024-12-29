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
#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/LayerFeedback.h"
#include "AIAC/Log.h"
#include "AIAC/Feedback/FabFeedback.h"

namespace AIAC
{
    LayerFeedback::LayerFeedback() {}

    void LayerFeedback::OnAttach()
    {
    }
    void LayerFeedback::OnFrameStart()
    {
        if(m_CurrentFabFeedbackPtr != nullptr) m_CurrentFabFeedbackPtr->Deactivate();
        if(AC_FF_COMP == nullptr) {
            m_CurrentFabFeedbackPtr = nullptr;
            return;
        }

        if (AC_FF_TOOL->GetTypeString() == "DRILLBIT"){
            if (AC_FF_COMP->GetTypeString() == "HOLE") {
                m_CurrentFabFeedbackPtr = &m_HoleFeedback;
            } else {
                m_CurrentFabFeedbackPtr = nullptr;
            }
        }
        else if (AC_FF_TOOL->GetTypeString() == "CIRCULARSAW"){
            if (AC_FF_COMP->GetTypeString() == "CUT") {
                m_CurrentFabFeedbackPtr = &m_CutCircularSawFeedback;
            } else {
                m_CurrentFabFeedbackPtr = nullptr;
            }
        }
        else if (AC_FF_TOOL->GetTypeString() == "SABERSAW"){
            if (AC_FF_COMP->GetTypeString() == "CUT") {
                // TODO
            } else {
                m_CurrentFabFeedbackPtr = nullptr;
            }
        }
        else if (AC_FF_TOOL->GetTypeString() == "CHAINSAW"){
            if (AC_FF_COMP->GetTypeString() == "CUT") {
                m_CurrentFabFeedbackPtr = &m_CutChainSawFeedback;
            } else {
                m_CurrentFabFeedbackPtr = nullptr;
            }
        }
        else{
            m_CurrentFabFeedbackPtr = nullptr;
            AIAC_WARN("no matching tool and component found");
        }

        if(m_CurrentFabFeedbackPtr != nullptr)
        {
            if (m_IsCurrentFabFeedbackVisible)
            {
                m_CurrentFabFeedbackPtr->Activate();
                m_CurrentFabFeedbackPtr->Update();
            }
            else
                m_CurrentFabFeedbackPtr->Deactivate();
        }
    }
}