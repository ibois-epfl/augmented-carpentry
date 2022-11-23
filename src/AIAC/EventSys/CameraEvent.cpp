#include "aiacpch.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void CameraCalibrationLoadedEvent::OnCameraCalibrationLoaded()
    {
        AIAC_INFO("Camera calibration file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.SetCalibrationFilePath(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(m_FilePath);
        AIAC_APP.GetRenderer()->InitProjMatrix();
    }
}