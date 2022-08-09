#pragma once

#include <opencv2/opencv.hpp>
#include "AIAC/Image.h"

namespace AIAC
{
    class Camera
    {
    public:
        Camera(int id=0);
        ~Camera();

        void SetCalibrationParams(cv::Mat cameraMatrix, cv::Mat distortionCoef);
        const AIAC::Image GetNextFrame();

        inline const uint32_t GetWidth() { return m_Width; }
        inline const uint32_t GetHeight() { return m_Height; }

    private:
        uint32_t m_Width, m_Height;
        float m_FovX, m_FovY;
        cv::VideoCapture m_VideoCapture;
        cv::Mat m_CameraMatrix, m_DistortionCoef;
    };
}