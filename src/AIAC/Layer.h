#pragma once

#include "AIAC/Log.h"

namespace AIAC
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        /// Is called when the layer is attached to the application.
        virtual void OnAttach() {}

        /// Is calle before GLFW poll events, GL frame and Imgui Frame
        virtual void OnFrameAwake() {}

        /// Is called when frame starts
        virtual void OnFrameStart() {}

        /// Is called when frame ends
        virtual void OnFrameEnd() {}

        /// Is called when the GLFW, GL and Imgui frame is updated and rendered
        virtual void OnFrameFall() {}

        /// Is called when the layer is detached from the application (~app).
        virtual void OnDetach() {}

    };
}