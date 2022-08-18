#pragma once

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
        bool LoadCameraParams(const std::string &filePath, int &w, int &h, cv::Mat &cameraMatrix, cv::Mat &distortionCoef);
        inline void UpdateFov();

        const AIAC::Image GetNextFrame();
        inline AIAC::Image &GetCurrentFrame() { return m_CurrentFrame; }

        inline const uint32_t GetWidth() const { return m_Width; }
        inline const uint32_t GetHeight() const { return m_Height; }
        inline const std::pair<float, float> GetFov() const { return std::make_pair(m_FovX, m_FovY); }

        bool IsOpened() const { return m_IsOpened; }

    private:
        Image m_CurrentFrame;

        uint32_t m_Width, m_Height;
        float m_FovX = -1.0f, m_FovY = -1.0f;
        cv::VideoCapture m_VideoCapture;
        cv::Mat m_CameraMatrix, m_DistortionCoef;
        bool m_IsOpened = false;
    };
}