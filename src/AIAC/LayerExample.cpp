#include "AIAC/LayerExample.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include <iostream>

namespace AIAC
{
    void LayerExample::OnAttach()
    {
        // To show how to get layers
        AIAC_INFO("LayerExample attached");
        AIAC::Application& app = AIAC::Application::GetInstance();
        AIAC::ApplicationSpecification spec = app.GetSpecification();
    }

    void LayerExample::OnFrameAwake()
    {
    }

    void LayerExample::OnFrameStart()
    {
    }

    void LayerExample::OnFrameEnd()
    {
    }

    void LayerExample::OnUIRender()
    {
    }

    void LayerExample::OnFrameFall()
    {
    }

    void LayerExample::OnDetach()
    {
    }
}