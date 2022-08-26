#include "aiacpch.h"

#include "AIAC/LayerCamera.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void LayerCamera::OnAttach()
    {
        try
        {
            MainCamera.Open(0);
        }
        catch(const std::runtime_error& e)
        {
            AIAC_ERROR(e.what());
        }
    }

    void LayerCamera::OnFrameStart()
    {
        MainCamera.GetNextFrame();
    }
}