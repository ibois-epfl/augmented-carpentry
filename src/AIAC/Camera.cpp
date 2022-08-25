#include "aiacpch.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

#include "AIAC/Config.h"
#include "AIAC/Camera.h"
#include "AIAC/Log.h"
#include "utils/utils.h"

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
            
            m_Width = m_VideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
            m_Height = m_VideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

            AIAC_INFO("Camera Resolution: {0}x{1}.", m_Width, m_Height);
        }

        // load camera params
        auto filePath = AIAC::Config::Get<std::string>("AIAC", "CamParamsFile", "assets/tslam/calibration_webcam.yml");
        int tmp;
        LoadCameraParams(filePath, tmp, tmp, m_CameraMatrix, m_DistortionCoef);
    }

    void Camera::SetCalibrationParams(cv::Mat cameraMatrix, cv::Mat distortionCoef)
    {
        m_CameraMatrix = cameraMatrix;
        m_DistortionCoef = distortionCoef;
        UpdateFov();
    }

    inline void Camera::UpdateFov(){
        // Update fov at the same time
        m_FovX = 2 * atan(m_Width / 2 / m_CameraMatrix.at<float>(0, 0));
        m_FovY = 2 * atan(m_Height / 2 / m_CameraMatrix.at<float>(1, 1));
    }

    bool Camera::LoadCameraParams(const std::string &filePath, int &w, int &h, cv::Mat &cameraMatrix, cv::Mat &distortionCoef){
        cv::FileStorage fs(filePath, cv::FileStorage::READ);
        if(!fs.isOpened()){
            throw std::runtime_error(std::string(__FILE__)+"LoadCameraParams() could not open file:" + filePath);
        }

        fs["image_width"] >> m_CameraParam.Width;
        fs["image_height"] >> m_CameraParam.Height;
        fs["distortion_coefficients"] >> m_CameraParam.CameraMatrix;
        fs["camera_matrix"] >> m_CameraParam.DistortionCoef;

        m_Width = m_CameraParam.Width;
        m_Height = m_CameraParam.Height;

        fs["image_width"] >> w;
        fs["image_height"] >> h;
        fs["distortion_coefficients"] >> distortionCoef;
        fs["camera_matrix"] >> cameraMatrix;

        if (w != m_Width || h != m_Height){
            m_IsCameraParamMatched = false;
            AIAC_ERROR("Mismatched Camera and Camera Parameter.");
        }

        UpdateFov();

        return true;
    }

    const AIAC::Image Camera::GetNextFrame()
    {
        if (!m_IsOpened) { AIAC_CRITICAL("Camera is not opened"); exit(-1); }
        // AIAC::Image nextFrame;
        // m_VideoCapture >> nextFrame;
        m_VideoCapture >> m_CurrentFrame;
        if(!m_IsCameraParamMatched){
            cv::Mat tmp;
            cv::resize(m_CurrentFrame.GetCvMat(), tmp, cv::Size(m_CameraParam.Width, m_CameraParam.Height));
            m_CurrentFrame = tmp;
        }
        return m_CurrentFrame;
    }
}