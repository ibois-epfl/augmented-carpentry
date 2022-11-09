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
        virtual ~LayerCameraCalib() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        void Clear();
        void StartCalibration();
        void StopCalibration() { m_IsCalibrating = false;};
        bool IsCalibrating() { return m_IsCalibrating; }
        void StartCapturing() { Clear(); m_IsCapturing = true; }
        bool IsCapturing() { return m_IsCapturing; }
        void SetSaveFilename(const std::string& filename) { SaveFilename = filename; }
        CameraCalibrator &GetCameraCalibrator() { return m_CameraCalibrator; }

    public:
        bool AutoCapture = true;
        int Delay = 2000;
        bool JustCaptured = false;
        int numOfFrame = 20;
        std::string SaveFilename = "calibration.yml";

    private:
        CameraCalibrator m_CameraCalibrator;
        bool m_IsCalibrating = false;
        bool m_IsCapturing = false;
        std::chrono::steady_clock::time_point prevCaptureTimestamp = std::chrono::steady_clock::now();
    };
}