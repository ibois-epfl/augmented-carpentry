#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tslam.h"
#include "AIAC/Layer.h"


namespace AIAC
{
    class LayerSlam : public AIAC::Layer
    {
    public:
        LayerSlam() = default;
        ~LayerSlam() = default;

        void OnAttach() override;
        virtual void OnFrameStart() override;

        inline const bool IsTracked() { return m_IsTracked; }
        inline const bool IsMapping() const { return m_IsMapping; }
        void StartMapping();
        void StopMapping() { m_IsMapping = false; }

        inline const cv::Mat GetCamPoseCv() { return m_CamPose; }
        glm::mat4 GetCamPoseGlm();
        glm::mat4 GetInvCamPoseGlm();

        void GetCamPoseInObjCoord(cv::Mat &rotationMatrix, cv::Mat &tvec);

        void UpdateMap();

    public:
        tslam::TSlam Slam;
        bool ToEnhance = true;
        bool ToProcess = true;
        // std::vector<shared_ptr<GOPrimitive>> SlamMapGOs;

    private:
        cv::Mat m_CamPose = cv::Mat();
        cv::Mat m_LastTrackedCamPose = cv::Mat::eye(4, 4, CV_32FC1);
        bool m_IsTracked = false;
        bool m_IsMapping = false;
    };
}