//
// Created by zholmaga on 11.09.23.
//

#include "LayerUtils.h"
#include "Application.h"
#include "Config.h"
#include <GL/glew.h>
#include "imgui.h"

namespace AIAC {

    LayerUtils::LayerUtils(){

    }
    LayerUtils::~LayerUtils() {
    }

    void LayerUtils::OnAttach() {
    }

    void LayerUtils::OnDetach() {
        // Cleanup if needed
    }


    void LayerUtils::OnImGuiRender() {
        // UI integration for both functionalities

        ImGui::Begin("Utils", NULL);

        m_VideoRecorder.RenderUI();         // VideoRecorder's ImGui UI

        ImGui::End();
    }

    void LayerUtils::StartRecording() {
        m_VideoRecorder.Start();
    }

    void LayerUtils::StopRecording() {
        m_VideoRecorder.Stop();
    }

}