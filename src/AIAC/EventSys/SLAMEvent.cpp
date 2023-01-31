#include "aiacpch.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"


namespace AIAC
{
    void SLAMMapLoadedEvent::OnSLAMMapLoaded()
    {
        AIAC_INFO("SLAM map file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setMap(m_FilePath, true);

        // extract the camera calibration file path from the SLAM map and update for camera and SLAM
        auto paramHeight = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CamSize.height;
        auto paramWidth = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CamSize.width;
        auto cameraMatrix = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CameraMatrix;

        // update the camera parameters for camera
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromSlamMap(paramWidth, paramHeight, cameraMatrix);

        // update the camera parameters for SLAM
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CameraMatrix = cameraMatrix;
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CamSize.height = paramHeight;
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CamSize.width = paramWidth;

        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();

        // enable SLAM
        AIAC_APP.GetLayer<LayerSlam>()->ToProcess = true;

        // TODO: Clean up the loaded mesh
    }

    void SLAMVocabularyLoadedEvent::OnSLAMVocabularyLoaded()
    {
        AIAC_INFO("SLAM vocabulary file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setVocabulary(m_FilePath);
    }
}