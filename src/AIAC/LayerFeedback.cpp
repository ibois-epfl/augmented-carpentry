#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/LayerFeedback.h"
#include "AIAC/Log.h"


namespace AIAC
{
    LayerFeedback::LayerFeedback() {}

    void LayerFeedback::OnAttach()
    {
        this->m_CurrentToolhead = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead();


    }
    void LayerFeedback::OnFrameStart()
    {
    }
}