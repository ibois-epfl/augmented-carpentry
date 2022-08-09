#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

#include "AIAC/Camera.h"

namespace AIAC
{
    Camera::Camera(int id)
    {
        m_VideoCapture = cv::VideoCapture(id);
        if(!m_VideoCapture.isOpened())
        {
            throw std::runtime_error("Camera can't be opened");
        }
        else
        {
            m_Width = m_VideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
            m_Height = m_VideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
        }
    }

    void Camera::SetCalibrationParams(cv::Mat cameraMatrix, cv::Mat distortionCoef)
    {
        m_CameraMatrix = cameraMatrix;
        m_DistortionCoef = distortionCoef;

        // Update fov at the same time
        m_FovX = 2 * atan(m_Width / 2 / cameraMatrix.at<float>(0, 0));
        m_FovY = 2 * atan(m_Height / 2 / cameraMatrix.at<float>(1, 1));
    }

    const AIAC::Image Camera::GetNextFrame()
    {
        AIAC::Image nextFrame;
        m_VideoCapture >> nextFrame;
        return nextFrame;
    }
}