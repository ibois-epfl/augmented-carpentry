#include "LayerCameraCalib.h"
#include "Application.h"

void AIAC::LayerCameraCalib::OnAttach() {
    // nothing to do here
}

void AIAC::LayerCameraCalib::OnFrameStart() {
    if (!m_IsCalibrating) {
        return;
    }

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    JustCaptured = false;
    if (AutoCapture && m_IsCapturing && std::chrono::duration_cast<std::chrono::milliseconds>(now - prevCaptureTimestamp).count() > Delay) {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawCurrentFrame().GetCvMat().copyTo(currentFrame);
        m_CameraCalibrator.AddImage(currentFrame);

        prevCaptureTimestamp = now;
        JustCaptured = true;
        AIAC_INFO("Captured frame: {0} / {1}", m_CameraCalibrator.GetImageAmount(), NumOfFrame);
    }

    if(m_CameraCalibrator.GetImageAmount() >= NumOfFrame) {
        try {
            if(m_CameraCalibrator.RunCalibration()){
                m_CameraCalibrator.Save(SaveFilename);
                AIAC_INFO("Calibration finished, file is saved to {0}", SaveFilename);
            }
        } catch (std::exception const& err){
            AIAC_ERROR(err.what());
        }
        m_IsCapturing = false;
        m_CameraCalibrator.ClearImages();
    }
}

void AIAC::LayerCameraCalib::StartCalibration() {
    AIAC_INFO("Starting calibration");
    m_IsCalibrating = true;
    Clear();
}

void AIAC::LayerCameraCalib::Clear() {
    m_CameraCalibrator.ClearImages();
    prevCaptureTimestamp = std::chrono::steady_clock::now();
}
