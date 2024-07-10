#pragma once

#include "AIAC/Layer.h"
#include "AIAC/Image.h"
#include "AIAC/Camera.h"
#include "CameraCalibrator.h"

namespace AIAC
{
    class LayerCameraCalib : public AIAC::Layer
    {
    public:
        LayerCameraCalib() = default;
        ~LayerCameraCalib() override = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void Clear();
        void StartCalibration();
        void StopCalibration() { m_IsCalibrating = false;};
        bool IsCalibrating() const { return m_IsCalibrating; }
        void StartCapturing() { Clear(); m_IsCapturing = true; }
        bool IsCapturing() const { return m_IsCapturing; }
        void SetSaveFilename(const std::string& filename) { SaveFilename = filename; }
        CameraCalibrator &GetCameraCalibrator() { return m_CameraCalibrator; }

    public:
        bool AutoCapture = true;
        bool JustCaptured = false;
        int Delay = 1500;
        int NumOfFrame = 100;
        std::string SaveFilename = "assets/tslam/calibration.yml";

    private:
        CameraCalibrator m_CameraCalibrator;
        bool m_IsCalibrating = false;
        bool m_IsCapturing = false;
        std::chrono::steady_clock::time_point prevCaptureTimestamp = std::chrono::steady_clock::now();
    };
}