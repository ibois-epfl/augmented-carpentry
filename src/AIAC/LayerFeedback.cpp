#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/LayerFeedback.h"
#include "AIAC/Log.h"


namespace AIAC
{
    LayerFeedback::LayerFeedback() {}

    void LayerFeedback::OnAttach()
    {
    }
    void LayerFeedback::OnFrameStart()
    {
        m_CutChainSawFeedback.Update();
        // this->m_FabFeed.Compute();
        // RefereshToolheadAndModel();


        // auto toolheadType = this->m_CurrentToolhead->GetTypeString();
        // auto drillbitData = this->m_CurrentToolhead->GetData<DrillBitData>();
        // auto circularsawData = this->m_CurrentToolhead->GetData<CircularSawData>();
        // auto sabersawData = this->m_CurrentToolhead->GetData<SaberSawData>();
        // auto chainsawData = this->m_CurrentToolhead->GetData<ChainSawData>();

        
    }
}