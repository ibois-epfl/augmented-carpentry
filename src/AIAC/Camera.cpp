// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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
#ifdef HEADLESS_TEST
        AIAC_INFO("Running in headless mode, load video from " + AIAC::Config::VIDEO_PATH);
        std::string videoPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TEST, AIAC::Config::VIDEO_PATH, "");
        if (videoPath.empty()) {
            throw std::invalid_argument("Video path for test is empty!");
        }
        if(!std::filesystem::exists(videoPath)){
            throw std::invalid_argument("No video file found at " + videoPath);
        }
        m_VideoCapture = cv::VideoCapture(videoPath);
#else
        m_VideoCapture = cv::VideoCapture(id);
#endif
        if(!m_VideoCapture.isOpened())
        {
            throw std::runtime_error("Camera " + std::to_string(id) + " can't be opened.");
        }
        else
        {
            m_IsOpened = true;
            
            m_PhysicalWidth = m_VideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
            m_PhysicalHeight = m_VideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

            AIAC_INFO("Camera Resolution: {0}x{1}.", m_PhysicalWidth, m_PhysicalHeight);
        }

        m_CalibFilePath = AIAC::Config::Get<std::string>(Config::SEC_AIAC,
                                                         Config::CAM_PARAMS_FILE,
                                                         "assets/tslam/calibration_orange_A_1280_720_000B.yml");
        LoadCameraParams(m_CalibFilePath);

        FlipHorizontal = AIAC::Config::Get<bool>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_FLIP_HORIZONTAL, false);
        FlipVertical = AIAC::Config::Get<bool>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_FLIP_VERTICAL, false);
    }

    inline void Camera::UpdateFov(){
        // Update fov at the same time
        m_FovX = 2 * atan(m_ParamWidth / 2 / GetCameraMatrix().at<float>(0, 0));
        m_FovY = 2 * atan(m_ParamHeight / 2 / GetCameraMatrix().at<float>(1, 1));
    }

    bool Camera::LoadCameraParams(const std::string &filePath){
        m_CalibFilePath = filePath;
        cv::FileStorage fs(filePath, cv::FileStorage::READ);
        if(!fs.isOpened()){
            throw std::runtime_error(std::string(__FILE__)+"LoadCameraParams() could not open file:" + filePath);
        }

        fs["image_width"] >> m_ParamWidth;
        fs["image_height"] >> m_ParamHeight;
        fs["distortion_coefficients"] >> m_DistortionCoef;
        fs["camera_matrix"] >> m_CameraMatrix;

        m_DistortionCoef.convertTo(m_DistortionCoef, CV_32F);
        m_CameraMatrix.convertTo(m_CameraMatrix, CV_32F);

        if(m_DistortionCoef.rows == 4) {
            m_IsFisheye = true;
            cv::fisheye::initUndistortRectifyMap(m_CameraMatrix, m_DistortionCoef, cv::Mat(),
                                                 m_CameraMatrix, cv::Size(m_PhysicalWidth, m_PhysicalHeight),
                                                 CV_32FC1, m_UndistortMap[0], m_UndistortMap[1]);
        } else {
            cv::initUndistortRectifyMap(m_CameraMatrix, m_DistortionCoef, cv::Mat(),
                                        m_CameraMatrix, cv::Size(m_PhysicalWidth, m_PhysicalHeight),
                                        CV_32FC1, m_UndistortMap[0], m_UndistortMap[1]);
        }

        return true;
    }
    
    const AIAC::Image Camera::GetNextFrame()
    {
        if (!m_IsOpened) { AIAC_CRITICAL("Camera is not opened"); exit(-1); }

        cv::Mat frame;
        m_VideoCapture >> frame;

        if (frame.empty()) {
            AIAC_APP.Close();
        }

        if (FlipHorizontal) cv::flip(frame, frame, 1);
        if (FlipVertical) cv::flip(frame, frame, 0);

        m_RawCurrentFrame = frame;

        cv::Mat resizedFrame, calibratedFrame;
        cv::remap(frame, calibratedFrame, m_UndistortMap[0], m_UndistortMap[1], cv::INTER_LINEAR);

        if(!IsPhysicalAndParamWidthHeightMatched()){
            cv::resize(calibratedFrame, resizedFrame, cv::Size(m_ParamWidth, m_ParamHeight));
        } else {
            calibratedFrame.copyTo(resizedFrame);
        }

        cv::Mat tempGrayMat;
        cv::cvtColor(calibratedFrame, tempGrayMat, cv::COLOR_BGR2GRAY);
        cv::cvtColor(tempGrayMat, tempGrayMat, cv::COLOR_GRAY2BGR);
        m_GrayCalibratedCurrentFrame = tempGrayMat;
        m_CalibratedCurrentFrame = calibratedFrame;
        return m_GrayCalibratedCurrentFrame;
    }


    AIAC::Image &Camera::GetCenterCroppedCurrentFrame(float ratioX, float ratioY){
        cv::Mat centerCroppedFrame(m_PhysicalHeight, m_PhysicalWidth,
                                   CV_8UC3, cv::Scalar(0, 0, 0));

        int xLeft = m_PhysicalWidth * (1 - ratioX) / 2;
        int xRight = m_PhysicalWidth - xLeft;
        int yTop = m_PhysicalHeight * (1 - ratioY) / 2;
        int yBottom = m_PhysicalHeight - yTop;

        for (int x = 0 ; x < m_PhysicalWidth ; x++) {
            for (int y = 0 ; y < m_PhysicalHeight ; y++) {
                if (x >= xLeft && x < xRight && y >= yTop && y < yBottom) {
                    centerCroppedFrame.at<cv::Vec3b>(y, x) = m_RawCurrentFrame.GetCvMat().at<cv::Vec3b>(y, x);
                }
            }
        }

        m_CenterCroppedCurrentFrame = centerCroppedFrame;
        return m_CenterCroppedCurrentFrame;
    }

    void Camera::UpdateCameraParamFromFile(const std::string &filePath)
    {
        m_IsCamMatrixInit = true;
        LoadCameraParams(filePath);

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

        stringstream ss;
        ss << "Camera Parameter Updated (using slam map): \n" << m_CameraMatrix;
        AIAC_INFO(ss.str());
    }
}