//
// Created by zholmaga on 11.09.23.
//

#pragma once
#pragma once

#include "AIAC/Layer.h"
#include "Utils/VideoRecorder.h"
#include "Utils/HoleToolheadExporter.h"

namespace AIAC {

    class LayerUtils : public Layer {
    public:
        LayerUtils();
        ~LayerUtils();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;

        void StartRecording();
        void StopRecording();

    private:
        Utils::VideoRecorder m_VideoRecorder;
        Utils::HoleToolheadExporter m_HoleToolheadExporter;
    };

}

