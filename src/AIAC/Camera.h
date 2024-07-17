#pragma once

#include <map.h>
#include "AIAC/Image.h"

namespace AIAC
{
    class Camera
    {
    public:
        Camera();
        ~Camera() {};
        /**
         * @brief Open the camera with the specified id.
         *
         * @param id The id of the camera to open.
         */
        void Open(int id);

        /**
         * @brief Initialize camera parameters from a configuration file.
         *
         * @param filePath The path to the camera parameter configuration file.
         */
        void InitCameraParamsFromFile(const std::string &filePath);

        /**
         * @brief Loads camera parameters from a configuration file.
         *
         * @param filePath The path to the camera parameter configuration file.
         * @return True if the camera parameters are loaded successfully, false otherwise.
         */
        bool LoadCameraParams(const std::string &filePath);

        /// @brief Update the field of view (FOV) values based on camera parameters.
        inline void UpdateFov();

        /**
         * @brief Capture and preprocess the next frame from the camera.
         *
         * @return A grayscale image representing the captured and processed frame.
         */
        const AIAC::Image GetNextFrame();

        /**
         * @brief Get the current color (calibrated) frame from the camera.
         *
         * @return A reference to the current color frame image.
         */
        inline AIAC::Image &GetColorCurrentFrame() { return m_CalibratedCurrentFrame; }
        /**
         * @brief Get the current grayscale (calibrated) frame from the camera.
         *
         * @return A reference to the current grayscale frame image.
         */
        inline AIAC::Image &GetCurrentFrame() { return m_GrayCalibratedCurrentFrame; }
        /**
         * @brief Get the current raw (uncalibrated) frame from the camera.
         *
         * @return A reference to the current raw frame image.
         */
        inline AIAC::Image &GetRawCurrentFrame() { return m_RawCurrentFrame; }
        /**
         * @brief Get the raw current frame, but borders are set to black according to the specified ratio.
         *
         * @param ratioX How much of % the width of the image is kept. (default: 0.75, i.e. 75%).
         * @param ratioY How much of % the height of the image is kept. (default: 0.9, i.e. 90%).
         * @return A reference to the center-cropped current frame image.
         */
        AIAC::Image &GetCenterCroppedCurrentFrame(float ratioX = 0.6f, float ratioY = 0.75f);

        /**
         * @brief Get the path to the camera calibration parameters.
         *
         * @return A constant reference to the camera calibration file path.
         */
        inline const std::string GetCalibrationFilePath() const { return m_CalibFilePath; }

        /**
         * @brief Force to update the default camera param.
         *
         * @param filePath The path to the camera param file.
         */
        void UpdateCameraParamFromFile(const std::string &filePath);

        /**
         * @brief Update the camera parameters from the SLAM-generated map.
         *
         * @param paramWidth Image width for camera calibration.
         * @param paramHeight Image height for camera calibration.
         * @param cameraMatrix The camera matrix
         */
        void UpdateCameraParamFromSlamMap(const int paramWidth, const int paramHeight, const cv::Mat &cameraMatrix);

        /**
         * @brief Update the camera parameters from the SLAM-generated map.
         *
         * @param map The SLAM-generated map.
         */
        void UpdateCameraParamFromSlamMap(const std::shared_ptr<tslam::Map>& map);

        /**
         * @brief Get the camera matrix.
         *
         * @return A constant reference to the camera matrix.
         */
        inline const cv::Mat GetCameraMatrix() { return m_CameraMatrix;};
        /**
         * @brief Get the distortion coefficients matrix.
         *
         * @return A constant reference to the distortion coefficient matrix.
         */
        inline const cv::Mat GetDistortionCoef() { return m_DistortionCoef; }

        /**
         * @brief Get the raw (uncalibrated) width of the camera frame.
         *
         * @return The raw width of the camera frame as an unsigned 32-bit integer.
         */
        inline const uint32_t GetRawWidth() const {return m_PhysicalWidth; }

        /**
         * @brief Get the raw (uncalibrated) height of the camera frame.
         *
         * @return The raw height of the camera frame as an unsigned 32-bit integer.
         */
        inline const uint32_t GetRawHeight() const {return m_PhysicalHeight; }

        /**
         * @brief Get the calibrated width of the camera frame.
         *
         * @return The calibrated width of the camera frame as an unsigned 32-bit integer.
         */
        inline const uint32_t GetWidth() const { return m_ParamWidth; }

        /**
         * @brief Get the calibrated height of the camera frame.
         *
         * @return The calibrated height of the camera frame as an unsigned 32-bit integer.
         */
        inline const uint32_t GetHeight() const { return m_ParamHeight; }

        /**
         * @brief Get the field of view (FOV) of the camera.
         *
         * @return A pair of floats representing the horizontal and vertical FOV of the camera.
         */
        inline const std::pair<float, float> GetFov() const { return std::make_pair(m_FovX, m_FovY); }

        /**
         * @brief Check if the camera is opened.
         *
         * @return True if the camera is opened, false otherwise.
         */
        bool IsOpened() const { return m_IsOpened; }

        /**
         * @brief Check if the physical and parameterized width and height match.
         *
         * @return True if the physical and parameterized width and height match, false otherwise.
         */
        bool IsPhysicalAndParamWidthHeightMatched() const { return m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight; }

    public:
        /// Flag indicating if the captured image should be flipped.
        bool FlipHorizontal = false;
        bool FlipVertical = false;

    private:
        ///  Flag indicating if the camera matrix is initialized.
        bool m_IsCamMatrixInit = false;
        ///  Flag indicating if the camera is fisheye.
        bool m_IsFisheye = false;
        /// Path to the camera calibration file.
        std::string m_CalibFilePath;
        /// Camera matrix.
        cv::Mat m_CameraMatrix;
        /// Distortion coefficient matrix.
        cv::Mat m_DistortionCoef;
        /// Undistorted map.
        cv::Mat m_UndistortMap[2];

        /// Physical width and height of the camera frame.
        int m_PhysicalWidth, m_PhysicalHeight;
        /// Width and height of the camera frame.
        int m_ParamWidth, m_ParamHeight;
        /// Field of view (FOV) of the camera.
        float m_FovX = -1.0f, m_FovY = -1.0f;

        /// Current raw (uncalibrated) frame.
        Image m_RawCurrentFrame;
        /// Current center-cropped frame.
        Image m_CenterCroppedCurrentFrame;
        /// Current calibrated frame.
        Image m_CalibratedCurrentFrame;
        /// Current grayscale calibrated frame.
        Image m_GrayCalibratedCurrentFrame;

        /// OpenCV video capture object.
        cv::VideoCapture m_VideoCapture;
        /// Flag indicating if the camera is opened.
        bool m_IsOpened = false;
    };
}