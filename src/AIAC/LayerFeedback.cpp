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