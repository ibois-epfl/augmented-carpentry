#pragma once

// #include <TTool/ttool.hh>
#include "AIAC/Layer.h"
#include "ttool.hh"

#include "AIAC/ACInfoToolheadManager.h"

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

    private:
        void UpdateToolheadState();
        void TrackFrame();

    private:
        std::shared_ptr<ttool::TTool> TTool;
        uint trackCounter = 0;
        uint TRACK_EVERY = 600;
        uint TRACK_FOR = 64;

        ttool::EventType ttoolState = ttool::EventType::Tracking;
        cv::Matx44f m_Pose;

    public:
        std::shared_ptr<AIAC::ACInfoToolheadManager> ACInfoToolheadManager;
    };
}