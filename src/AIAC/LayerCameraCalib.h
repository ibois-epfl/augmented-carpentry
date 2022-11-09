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

        void StartCalibration();
        void StopCalibration() { m_isCalibrating = false;};
        bool IsCalibrating() { return m_isCalibrating; }
        void SetSaveFilename(const std::string& filename) { SaveFilename = filename; }
        CameraCalibrator &GetCameraCalibrator() { return m_CameraCalibrator; }

    public:
        bool AutoCapture = true;
        int Delay = 1200;
        bool JustCaptured = false;
        int numOfFrame = 20;
        std::string SaveFilename = "calibration.yml";

    private:
        CameraCalibrator m_CameraCalibrator;
        bool m_isCalibrating = false;
        clock_t prevCaptureTimestamp = 0;
    };
}