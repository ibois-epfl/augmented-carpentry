#include "aiacpch.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void CameraCalibrationLoadedEvent::OnCameraCalibrationLoaded()
    {
        AIAC_APP.GetLayer<LayerSlam>()->DummyRestart(m_FilePath);
        AIAC_WARN(m_FilePath);
    }
}