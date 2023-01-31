#include "aiacpch.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void CameraCalibrationLoadedEvent::OnCameraCalibrationFileLoaded()
    {
        AIAC_INFO("Camera calibration file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromFile(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));

        // Since the camera calibration file has changed, making it uncompilable with the previous SLAM map
        // we need to stop the SLAM process, or it will crash
        AIAC_APP.GetLayer<LayerSlam>()->ToProcess = false;

        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();
    }
}