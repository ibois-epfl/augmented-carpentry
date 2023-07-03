#pragma once

// #include <TTool/ttool.hh>
#include "AIAC/Layer.h"
#include "ttool.hh"

namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead() = default;
        virtual ~LayerToolhead() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        bool NeedsContextReleased() const { return true; }

    protected:
        void UpdateToolheadState();
        void OnPoseManipulation();

    protected:
        std::shared_ptr<ttool::TTool> TTool;
        uint trackCounter = 0;
        uint TRACK_EVERY = 600;
        uint TRACK_FOR = 64;

        ttool::EventType ttoolState = ttool::EventType::PoseInput;
        cv::Matx44f m_Pose;
    };
}