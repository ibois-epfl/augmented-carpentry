#pragma once

#include <opencv2/opencv.hpp>
#include "AIAC/Image.h"

namespace AIAC
{
    class Camera
    {
    public:
        Camera();
        ~Camera() {};

        void Open(int id);

        void SetCalibrationParams(cv::Mat cameraMatrix, cv::Mat distortionCoef);
        const AIAC::Image GetNextFrame();
        inline AIAC::Image GetCurrentFrame() { return m_CurrentFrame; }

        inline const uint32_t GetWidth() { return m_Width; }
        inline const uint32_t GetHeight() { return m_Height; }

        bool IsOpened() { return m_IsOpened; }

    private:
        Image m_CurrentFrame;

        uint32_t m_Width, m_Height;
        float m_FovX, m_FovY;
        cv::VideoCapture m_VideoCapture;
        cv::Mat m_CameraMatrix, m_DistortionCoef;
        bool m_IsOpened = false;
    };
}