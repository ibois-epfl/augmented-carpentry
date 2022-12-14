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

        void InitCameraParamsFromFile(const std::string &filePath);
        static bool LoadCameraParams(const std::string &filePath, int &w, int &h, cv::Mat &cameraMatrix, cv::Mat &distortionCoef);
        inline void UpdateFov();

        const AIAC::Image GetNextFrame();
        inline AIAC::Image &GetCurrentFrame() { return m_CalibratedCurrentFrame; }
        inline AIAC::Image &GetRawCurrentFrame() { return m_RawCurrentFrame; }

        inline const std::string GetCalibrationFilePath() const { return m_CalibFilePath; }

        /**
         * @brief Force to update the default camera param
         * @param filePath The path to the camera param file
         */
        void UpdateCameraParamFromFile(const std::string &filePath);
        void UpdateCameraParamFromSlamMap(const int paramWidth, const int paramHeight, const cv::Mat &cameraMatrix);
        inline const cv::Mat GetCameraMatrix() { return m_CameraMatrix;};
        inline const cv::Mat GetDistortionCoef() { return m_DistortionCoef; }

        inline const uint32_t GetWidth() const { return m_ParamWidth; }
        inline const uint32_t GetHeight() const { return m_ParamHeight; }
        inline const std::pair<float, float> GetFov() const { return std::make_pair(m_FovX, m_FovY); }

        bool IsOpened() const { return m_IsOpened; }

    private:
        bool m_IsCamMatrixInit = false;
        std::string m_CalibFilePath;
        cv::Mat m_CameraMatrix;
        cv::Mat m_DistortionCoef;
        int m_PhysicalWidth, m_PhysicalHeight;
        int m_ParamWidth, m_ParamHeight;
        float m_FovX = -1.0f, m_FovY = -1.0f;

        Image m_RawCurrentFrame;
        Image m_CalibratedCurrentFrame;

        cv::VideoCapture m_VideoCapture;
        bool m_IsOpened = false;

//        struct CameraParam{
//            int Width, Height;
//            cv::Mat CameraMatrix, DistortionCoef;
//        } m_CameraParam;

        bool m_IsPhysicalAndParamWidthHeightMatched = true;
    };
}