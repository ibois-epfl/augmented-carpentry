#include "aiacpch.h"

#include "AIAC/Config.h"

#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/LayerToolhead.h"

#include <QApplication>
#include <QThread>

#include "ttool.hh"


namespace AIAC
{
    void LayerToolhead::OnAttach()
    {
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Aie Aie aie, y a rien de configurer"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Oh la la la, tu dois metre un fichier de parametre de camera")
            );
        
        // TODO: ObjectTracker needs modelID2Pose to be set, but it is not done during the initialization of object tracker
        TTool->ManipulateModel('e');
        TTool->ManipulateModel('q');
    }

    void LayerToolhead::OnFrameStart()
    {
        UpdateToolheadState();
        if (ttoolState == ttool::EventType::PoseInput)
        {
            OnPoseManipulation();
        }

        if (!(ttoolState == ttool::EventType::Tracking))
            return;

        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        TTool->RunOnAFrame(currentFrame);
        m_Pose = TTool->GetPose();
        std::stringstream ss;
        ss << "Pose: " << m_Pose;
        AIAC_INFO(ss.str());
    }

    /**
     * @brief Reload the camera calibration file
    */
    void LayerToolhead::ReloadCameraCalibration()
    {
        TTool->DestrolView();
        OnAttach();
        ttoolState = ttool::EventType::PoseInput;
    }

    void LayerToolhead::OnPoseManipulation()
    {
        char key = cv::waitKey(1);
        while (key != 'q')
        {
            cv::Mat currentFrame;
            AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
            TTool->ShowSilhouette(currentFrame, -1);
            TTool->ManipulateModel(key);
            key = cv::waitKey(1);
            AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetNextFrame();
        }
        cv::destroyAllWindows();
        AIAC_INFO("Pose manipulation done");
        ttoolState = ttool::EventType::Tracking;
    }

    /**
     * @brief Update the toolhead state on every frame
     * This will be called from OnFrameStart()
     * It will check if the toolhead is tracking, and count the number of frames it has been tracking for
     * If it has been tracking for TRACK_FOR frames, it will stop tracking
     * If it has not been tracking for TRACK_EVERY frames, it will start tracking
     * 
     */
    void LayerToolhead::UpdateToolheadState()
    {
        if (ttoolState == ttool::EventType::Tracking)
        {
            trackCounter++;
            if (trackCounter >= TRACK_FOR)
            {
                ttoolState = ttool::EventType::None;
                trackCounter = 0;
            }
        }
        else if (ttoolState == ttool::EventType::None)
        {
            trackCounter++;
            if (trackCounter >= TRACK_EVERY)
            {
                ttoolState = ttool::EventType::Tracking;
                trackCounter = 0;
            }
        }
    }
}