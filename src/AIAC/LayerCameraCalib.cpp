#include "LayerCameraCalib.h"
#include "Application.h"

void AIAC::LayerCameraCalib::OnAttach() {
    // nothing to do here
}

void AIAC::LayerCameraCalib::OnFrameStart() {
    if (!m_isCalibrating) {
        return;
    }

    JustCaptured = false;
    if (AutoCapture && m_isCalibrating && clock() - prevCaptureTimestamp > Delay * 1e-3 * CLOCKS_PER_SEC) {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawCurrentFrame().GetCvMat().copyTo(currentFrame);
        m_CameraCalibrator.AddImage(currentFrame);
        prevCaptureTimestamp = clock();
        JustCaptured = true;
        AIAC_INFO("Captured frame: {0} / {1}", m_CameraCalibrator.GetImageAmount(), numOfFrame);
    }

    if(m_CameraCalibrator.GetImageAmount() > numOfFrame) {
        m_CameraCalibrator.RunCalibration();
        m_CameraCalibrator.Save(SaveFilename);
        AIAC_INFO("Calibration finished");
        m_isCalibrating = false;
    }
}

void AIAC::LayerCameraCalib::StartCalibration() {
        AIAC_INFO("Starting calibration");
        m_isCalibrating = true;
        m_CameraCalibrator.ClearImages();
        prevCaptureTimestamp = 0;
}
