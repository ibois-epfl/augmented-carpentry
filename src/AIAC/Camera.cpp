#include "aiacpch.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

#include "AIAC/Config.h"
#include "AIAC/Camera.h"
#include "AIAC/Log.h"
#include "utils/utils.h"
#include "Application.h"

namespace AIAC
{
    Camera::Camera() {}

    void Camera::Open(int id)
    {
        m_VideoCapture = cv::VideoCapture(id);
        if(!m_VideoCapture.isOpened())
        {
            throw std::runtime_error("Camera can't be opened");
        }
        else
        {
            m_IsOpened = true;
            
            m_PhysicalWidth = m_VideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
            m_PhysicalHeight = m_VideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

            AIAC_INFO("Camera Resolution: {0}x{1}.", m_PhysicalWidth, m_PhysicalHeight);
        }

        // load camera params
        m_CalibFilePath = AIAC::Config::Get<std::string>("AIAC", "CamParamsFile", "assets/tslam/calibration_webcam.yml");
        InitCameraParamsFromFile(m_CalibFilePath);
    }

    void Camera::InitCameraParamsFromFile(const std::string &filePath) {
        int w, h;
        cv::Mat cameraMatrix;

        LoadCameraParams(filePath, w, h, cameraMatrix, m_DistortionCoef);

        if(!m_IsCamMatrixInit){
            m_ParamWidth = w;
            m_ParamHeight = h;
            m_CameraMatrix = cameraMatrix;

            m_IsPhysicalAndParamWidthHeightMatched = (m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight);
        }
    }

    inline void Camera::UpdateFov(){
        // Update fov at the same time
        m_FovX = 2 * atan(m_ParamWidth / 2 / GetCameraMatrix().at<float>(0, 0));
        m_FovY = 2 * atan(m_ParamHeight / 2 / GetCameraMatrix().at<float>(1, 1));
    }

    bool Camera::LoadCameraParams(const std::string &filePath, int &w, int &h, cv::Mat &cameraMatrix, cv::Mat &distortionCoef){
        cv::FileStorage fs(filePath, cv::FileStorage::READ);
        if(!fs.isOpened()){
            throw std::runtime_error(std::string(__FILE__)+"LoadCameraParams() could not open file:" + filePath);
        }

        fs["image_width"] >> w;
        fs["image_height"] >> h;
        fs["distortion_coefficients"] >> distortionCoef;
        fs["camera_matrix"] >> cameraMatrix;

//        fs["image_width"] >> m_ParamWidth;
//        fs["image_height"] >> m_ParamHeight;
//        fs["camera_matrix"] >> m_CameraMatrix;
//        fs["distortion_coefficients"] >> m_DistortionCoef;
//
//        if (m_ParamWidth != m_PhysicalWidth || m_ParamHeight != m_PhysicalHeight){
//            m_IsPhysicalAndParamWidthHeightMatched = false;
//            AIAC_ERROR("Mismatched Camera and Camera Parameter.");
//        }
//
//        UpdateFov();

        return true;
    }

    const AIAC::Image Camera::GetNextFrame()
    {
        if (!m_IsOpened) { AIAC_CRITICAL("Camera is not opened"); exit(-1); }

        cv::Mat frame;
        m_VideoCapture >> frame;

        // raw frame
        m_RawCurrentFrame = frame;
        // undistorted frame
        cv::Mat resizedFrame, calibratedFrame;
        if(!m_IsPhysicalAndParamWidthHeightMatched){
            cv::resize(frame, resizedFrame, cv::Size(m_ParamWidth, m_ParamHeight));
        } else {
            frame.copyTo(resizedFrame);
        }
        cv::undistort(resizedFrame, calibratedFrame, GetCameraMatrix(), m_DistortionCoef);

        m_CalibratedCurrentFrame = calibratedFrame;

        return m_CalibratedCurrentFrame;
    }

    void Camera::UpdateCameraParamFromFile(const std::string &filePath)
    {
        m_IsCamMatrixInit = true;
        m_CalibFilePath = filePath;
        LoadCameraParams(m_CalibFilePath, m_ParamWidth, m_ParamHeight, m_CameraMatrix, m_DistortionCoef);
        m_IsPhysicalAndParamWidthHeightMatched = (m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight);

        stringstream ss;
        ss << "Camera Parameter Updated (using config file): \n" << m_CameraMatrix;
        AIAC_INFO(ss.str());
    }

    void Camera::UpdateCameraParamFromSlamMap(const int paramWidth, const int paramHeight, const cv::Mat &cameraMatrix) {
        m_IsCamMatrixInit = true;
        m_ParamWidth = paramWidth;
        m_ParamHeight = paramHeight;
        m_CameraMatrix = cameraMatrix;
        UpdateFov();
        m_IsPhysicalAndParamWidthHeightMatched = (m_PhysicalWidth == m_ParamWidth && m_PhysicalHeight == m_ParamHeight);

        stringstream ss;
        ss << "Camera Parameter Updated (using slam map): \n" << m_CameraMatrix;
        AIAC_INFO(ss.str());
    }
}