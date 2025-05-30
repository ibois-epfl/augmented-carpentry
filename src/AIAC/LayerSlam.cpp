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

#include "AIAC/Config.h"

#include "AIAC/LayerSlam.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "utils/MatrixUtils.h"

//for test
#include "glm/gtx/string_cast.hpp"

namespace AIAC
{
    void LayerSlam::OnAttach()
    {
        // load camera calibration file (mainly for distortion matrix)
        auto calibFilePath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "assets/tslam/calibration_webcam.yml");
        Slam.setCamParams(calibFilePath);
        Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));
        Slam.systemParams.enableLoopClosure = false;
        Slam.systemParams.aruco_minerrratio_valid = 15;
        Slam.systemParams.KPNonMaximaSuppresion=true;
        Slam.systemParams.markersOptWeight=1.0; // maximum importance of markers in the final error. Value in range [0,1]. The rest if assigned to points
        Slam.systemParams.minMarkersForMaxWeight=3;
        Slam.systemParams.detectKeyPoints=false;

        // load map, the camera matrix will be replaced by the one in the map
        auto pathToMapFile = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::MAP_FILE, "assets/tslam/example.map");
        if(std::filesystem::exists(pathToMapFile)){
            AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMMapLoadedEvent>(pathToMapFile));
        } else {
            AIAC_WARN("SLAM map file doesn't exist: \"{}\". Init empty map.", pathToMapFile);
            Slam.clearMap();
        }

        // load vocabulary
        Slam.setVocabulary(AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::VocFile, "assets/tslam/orb.fbow"));
        Slam.setInstancing(true);
    }

    void LayerSlam::OnFrameStart()
    {
        if(m_ToStartMapping){
            Slam.systemParams.detectKeyPoints=true;
            Slam.clearMap();
            Slam.setInstancing(false);
            ToProcess = true;
            m_IsMapping = true;
            m_ToStartMapping = false;
        }
        
        // Update the Tag visibility setting
        if(ToShowTag != m_IsShowingTag){
            if(ToShowTag){
                for(auto &go : m_SlamMapGOs){
                    go->SetVisibility(true);
                }
            } else {
                for(auto &go : m_SlamMapGOs){
                    go->SetVisibility(false);
                }
            }
            m_IsShowingTag = ToShowTag;
        }

        if(!ToProcess){
            return;
        }

        cv::Mat currentFrame;
        cv::Mat resizedFrame;

        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        auto targetSize = Slam.imageParams.CamSize;
        cv::resize(currentFrame, resizedFrame, targetSize);
        currentFrame = resizedFrame;

        if(ToEnhance){
            //Get Intensity image
            cv::Mat Lab_image;
            cvtColor(currentFrame, Lab_image, cv::COLOR_BGR2Lab);
            std::vector<cv::Mat> Lab_planes(3);
            cv::split(Lab_image, Lab_planes);  // now we have the L image in lab_planes[0]

            // apply the CLAHE algorithm to the L channel
            cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
            clahe->setClipLimit(4);
            // clahe->setTilesGridSize(cv::Size(10, 10));
            cv::Mat clahe_L;
            clahe->apply(Lab_planes[0], clahe_L);

            // Merge the color planes back into a Lab image
            clahe_L.copyTo(Lab_planes[0]);
            cv::merge(Lab_planes, Lab_image);

            // convert back to RGB
            cv::cvtColor(Lab_image, currentFrame, cv::COLOR_Lab2BGR);
        }

        m_IsTracked = Slam.process(currentFrame, m_CamPose);
        m_ProcessedFrame = currentFrame.clone();

        if(m_IsTracked) {
            m_NumLostFrame = 0;

            // perform stabilization
            if (m_CamPoseBuffer.empty()) {
                // if no pose in the buffer, take the current one
                m_CamPoseBuffer.push_back(m_CamPose.clone());
                m_LastTrackedCamPose = m_CamPose.clone();
            } else {
                // calculate the average of the pose in the buffer
                cv::Mat avg_pose = cv::Mat::zeros(4, 4, CV_32FC1);
                for(auto &pose: m_CamPoseBuffer){
                    avg_pose += pose;
                }
                avg_pose = avg_pose / double(m_CamPoseBuffer.size());

                auto poseDifference = cv::norm(m_CamPose - avg_pose);
                if (poseDifference < 3.0f) {
                    m_NumLongDistFrame = 0;
                    m_CamPoseBuffer.push_back(m_CamPose.clone());
                } else {
                    m_NumLongDistFrame++;
                }

                if (m_CamPoseBuffer.size() > m_MaxCamPoseBufferSize) {
                    m_CamPoseBuffer.pop_front();
                }

                // perform a linear interpolation to get the stabilized pose
                m_LastTrackedCamPose = cv::Mat::zeros(4, 4, CV_32FC1);

                // OPTION 1: calculate the weighted average
                int divider = 0;
                for(int i = 0 ; i < m_CamPoseBuffer.size() ; i++){
                    m_LastTrackedCamPose += m_CamPoseBuffer[i] * (i + 1);
                    divider += (i + 1);
                }
                m_LastTrackedCamPose = m_LastTrackedCamPose / divider;

                // OPTION 2: just calculate the average
//                cout << "CamPoseBuffer: " << endl;
//                for(auto &pose : m_CamPoseBuffer){
//                    cout << pose << endl;
//                    m_LastTrackedCamPose += pose / double(m_CamPoseBuffer.size());
//                }
            }
        } else {
            m_NumLostFrame ++;
        }

        if((m_NumLongDistFrame > 1 || m_NumLostFrame > m_MaxCamPoseBufferSize)
                && !m_CamPoseBuffer.empty()){
            m_CamPoseBuffer.clear();
            m_NumLostFrame = 0;
            m_NumLongDistFrame = 0;
        }
    }

    glm::mat4 LayerSlam::GetCamPoseGlm()
    {
        glm::mat4 glmMat;
        if (m_LastTrackedCamPose.cols != 4 ||m_LastTrackedCamPose.rows != 4 ||m_LastTrackedCamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetCamPose() error.");
        }
        memcpy(glm::value_ptr(glmMat), m_LastTrackedCamPose.data, 16 * sizeof(float));
        glmMat = glm::transpose(glmMat);
        return glmMat;
    }

    void LayerSlam::GetCamPoseInObjCoord(cv::Mat &rotMat, cv::Mat &tvec){
        rotMat(cv::Rect(0, 0, 3, 3)) = m_LastTrackedCamPose(cv::Rect(0, 0, 3, 3)).t();
        tvec(cv::Rect(0, 0, 3, 1)) = m_LastTrackedCamPose(cv::Rect(3, 0, 3, 1));
        tvec = -rotMat * tvec;
    }

    glm::mat4 LayerSlam::GetInvCamPoseGlm()
    {
        glm::mat4 glmMat;
        if (m_LastTrackedCamPose.cols != 4 ||m_LastTrackedCamPose.rows != 4 ||m_LastTrackedCamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetCamPose() error.");
        }
        memcpy(glm::value_ptr(glmMat), m_LastTrackedCamPose.data, 16 * sizeof(float));
        glmMat = glm::transpose(glmMat);

        glm::mat3 RT; // rotation matrix
        glm::vec3 tvec; // transpose vector
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                RT[i][j] = glmMat[j][i]; // Transpose is inverse(R) because R is rotation matrix
            }
            tvec[i] = glmMat[3][i];
        }

        tvec = -RT * tvec;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                glmMat[i][j] = RT[i][j];
            }
            glmMat[3][i] = tvec[i];
        }
        glmMat[3][3] = 1.0f;

        return glmMat;
    }

    void LayerSlam::StartMapping() {
        m_ToStartMapping = true;
        // The rest of the process is done in OnFrameStart()
    }

    void LayerSlam::StopMapping() {
        Slam.systemParams.detectKeyPoints=false;
        Slam.setInstancing(true);
        m_IsMapping = false;
    }

    void LayerSlam::UpdateMap(std::string path){
        Slam.setMap(path, true);
        InitSlamMapGOs();
    }

    void LayerSlam::InitSlamMapGOs(){
        // reset GLObjects
        for(auto &go: m_SlamMapGOs){
            GOPrimitive::Remove(go);
        }
        m_SlamMapGOs.clear();

        // add new GLObjects
        // std::vector<glm::vec3> markerEdges; markerEdges.reserve(map->map_markers.size() * 4 * 2);
        // std::vector<glm::vec4> markerEdgeColors; markerEdgeColors.reserve(map->map_markers.size() * 4 * 2);
        for(const auto& mapMarker: Slam.getMap()->map_markers){
            auto points = mapMarker.second.get3DPoints();
            std::vector<glm::vec3> markerEdges;
            for(int i = 0 ; i < 4; i++){
                markerEdges.emplace_back(points[i].x, points[i].y, points[i].z);
            }
            auto tag = GOPolyline::Add(markerEdges, true, 1.0f);
            tag->SetColor(glm::vec4(1.0f, .0f, .0f, 1.0f));
            tag->SetVisibility(false);
            m_SlamMapGOs.push_back(tag);
        }
    }

    void LayerSlam::GetCamPoseQuaternionAndTvec(cv::Vec4f &quaternion, cv::Vec3f &tvec) {
        cv::Mat R = m_LastTrackedCamPose(cv::Rect(0, 0, 3, 3));
        quaternion = ConvertRotationMatrixToQuaternion(R);
        tvec[0] = m_LastTrackedCamPose.at<float>(0, 3);
        tvec[1] = m_LastTrackedCamPose.at<float>(1, 3);
        tvec[2] = m_LastTrackedCamPose.at<float>(2, 3);
    }
}