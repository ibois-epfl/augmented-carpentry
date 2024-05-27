#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GOSys/GOPrimitive.h"
#include "tslam.h"
#include "AIAC/Image.h"
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
        bool m_IsTracked = false;
        bool m_IsMapping = false;
        bool m_IsShowingTag = false;
        bool m_ToStartMapping = false;
        std::vector<std::shared_ptr<GOPrimitive>> m_SlamMapGOs;
    };
}