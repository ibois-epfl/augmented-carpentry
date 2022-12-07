#include "aiacpch.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void CameraCalibrationLoadedEvent::OnCameraCalibrationLoaded()
    {
        AIAC_INFO("Camera calibration file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.SetCalibrationFilePathAndLoad(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(m_FilePath);

        float newFovX = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetCameraMatrix().at<float>(0, 0);
        float mapFovX = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.fx();

        if (fabs(mapFovX - newFovX) > 10) {
            AIAC_WARN("Camera params aren't consist between map (" + to_string(mapFovX) +") and camera(" + to_string(newFovX) + ")");
            AIAC_APP.GetLayer<LayerSlam>()->ToProcess = false;
        }

        AIAC_APP.GetRenderer()->InitProjMatrix();
    }
}