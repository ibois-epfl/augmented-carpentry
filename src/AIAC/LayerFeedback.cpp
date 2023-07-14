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
        // auto toolheadData = this->m_CurrentToolhead->GetData<DrillBitData>();
        // float toolheadRadius = toolheadData.RadiusACIT;
        // std::string toolheadRadiusString = std::to_string(toolheadRadius);
        // AIAC_INFO("Toolhead data: {0}", toolheadRadiusString);
    }
}