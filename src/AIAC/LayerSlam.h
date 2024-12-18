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
#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GOSys/GOPrimitive.h"
#include "tslam.h"
#include "AIAC/Image.h"
#include "AIAC/Layer.h"
#include "AIAC/Config.h"
#include "utils/CircularBuffer.h"


namespace AIAC
{
    class LayerSlam : public AIAC::Layer
    {
    public:
        LayerSlam() = default;
        ~LayerSlam() = default;

        void OnAttach() override;
        virtual void OnFrameStart() override;

        inline const int GetNumLostFrame() { return m_NumLostFrame; }
        inline const bool IsTracked() { return m_IsTracked; }
        inline const bool IsMapping() const { return m_IsMapping; }
        void StartMapping();
        void StopMapping();

        inline const cv::Mat GetCamPoseCv() { return m_CamPose; }
        glm::mat4 GetCamPoseGlm();
        glm::mat4 GetInvCamPoseGlm();
        void GetCamPoseQuaternionAndTvec(cv::Vec4f &quaternion, cv::Vec3f &tvec);

        inline AIAC::Image &GetProcessedFrame() { return m_ProcessedFrame; }

        void GetCamPoseInObjCoord(cv::Mat &rotationMatrix, cv::Mat &tvec);

        void UpdateMap(std::string path);
        void InitSlamMapGOs();

    public:
        tslam::TSlam Slam;
        bool ToShowTag = false;
        bool ToEnhance = false;
        bool ToProcess = true;

    private:
        AIAC::Image m_ProcessedFrame;
        cv::Mat m_CamPose = cv::Mat();
        cv::Mat m_LastTrackedCamPose = cv::Mat::eye(4, 4, CV_32FC1);

        int m_NumLostFrame = 0;
        int m_NumLongDistFrame = 0;
        CircularBuffer<cv::Mat> m_CamPoseBuffer{ size_t(AIAC::Config::Get<int>(AIAC::Config::SEC_AIAC, AIAC::Config::STABILIZATION_FRAME_COUNT, 5)) };
        int m_MaxCamPoseBufferSize = AIAC::Config::Get<int>(AIAC::Config::SEC_AIAC, AIAC::Config::STABILIZATION_FRAME_COUNT, 5);

        bool m_IsTracked = false;
        bool m_IsMapping = false;
        bool m_IsShowingTag = false;
        bool m_ToStartMapping = false;
        std::vector<std::shared_ptr<GOPrimitive>> m_SlamMapGOs;
    };
}