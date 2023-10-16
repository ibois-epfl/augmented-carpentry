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
        bool LoadCameraParams(const std::string &filePath);
        inline void UpdateFov();

        const AIAC::Image GetNextFrame();
        //inline AIAC::Image &GetCurrentFrame() { return m_CalibratedCurrentFrame; }
        inline AIAC::Image &GetCurrentFrame() { return m_GrayCalibratedCurrentFrame; }
        inline AIAC::Image &GetCalibratedCurrentFrame() { return m_CalibratedCurrentFrame; }
        inline AIAC::Image &GetRawCurrentFrame() { return m_RawCurrentFrame; }
        /**
         * @brief Get the raw current frame, but borders are set to black according to the specified ratio.
         * @param ratioX How much of % the width of the image is kept. (default: 0.75, i.e. 75%)
         * @param ratioY How much of % the height of the image is kept. (default: 0.9, i.e. 90%)
         * @return
         */
        AIAC::Image &GetCenterCroppedCurrentFrame(float ratioX = 0.6f, float ratioY = 0.75f);

        inline const std::string GetCalibrationFilePath() const { return m_CalibFilePath; }

        /**
         * @brief Force to update the default camera param
         * @param filePath The path to the camera param file
         */
        void UpdateCameraParamFromFile(const std::string &filePath);
        void UpdateCameraParamFromSlamMap(const int paramWidth, const int paramHeight, const cv::Mat &cameraMatrix);
        inline const cv::Mat GetCameraMatrix() { return m_CameraMatrix;};
        inline const cv::Mat GetDistortionCoef() { return m_DistortionCoef; }

        inline const uint32_t GetRawWidth() const {return m_PhysicalWidth; }
        inline const uint32_t GetRawHeight() const {return m_PhysicalHeight; }
        inline const uint32_t GetWidth() const { return m_ParamWidth; }
        inline const uint32_t GetHeight() const { return m_ParamHeight; }
        inline const std::pair<float, float> GetFov() const { return std::make_pair(m_FovX, m_FovY); }

        bool IsOpened() const { return m_IsOpened; }
        bool IsPhysicalAndParamWidthHeightMatched() const { return m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight; }

    private:
        bool m_IsCamMatrixInit = false;
        bool m_IsFisheye = false;
        std::string m_CalibFilePath;
        cv::Mat m_CameraMatrix;
        cv::Mat m_DistortionCoef;
        cv::Mat m_UndistortMap[2];
        int m_PhysicalWidth, m_PhysicalHeight;
        int m_ParamWidth, m_ParamHeight;
        float m_FovX = -1.0f, m_FovY = -1.0f;

        Image m_RawCurrentFrame;
        Image m_CenterCroppedCurrentFrame;
        Image m_CalibratedCurrentFrame;
        Image m_GrayCalibratedCurrentFrame;

        cv::VideoCapture m_VideoCapture;
        bool m_IsOpened = false;
    };
}