---
tags:
  - layer-stack
  - backend
---

# Layer stack

/// html | div[style='float: left; width: 50%;']

![Illustration of the layer-stack design and the main loop for the AR engine. ><](../../assets/images/AR_engine/fig_layer-stack.svg){align=center width=90% style='fill-color: #000000; filter: invert(100%);'}

///

/// html | div[style='float: right;width: 50%;']

At the core of every AR engine there is a main loop where *1)* you get your sensor data, *2)* you process it, *3)* you render it, and *4)* you display it, *5)* you start over or stop. 

And Augmented Carpentry makes no difference. Now, the way you decide to structure your code and the way you decide to manage the flow of this main loop makes the difference. We went for a light weight and expandable architecture called *layer-stack* flow.

Here on the left you can find its illustration of the layer-stack design and the main loop for our AR engine. In the this page we will delve into the details of this architecture.

///

/// html | div[style='clear: both;']
///

## Layer stack flow

The layer stack is primarily responsible for managing the flow control of the AR engine. Designed as a modular system, each layer encapsulates the code for a specific domain of the AR application, such as camera processing, object tracking, UI, rendering, etc. The general order and expansion of these layers can be configured in the top-level main file [`ACApp.cpp`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/ACApp.cpp), which is also our main entry point for the application:

``` cpp title="src/ACApp.cpp" hl_lines="17-25" linenums="1"
#include "aiacpch.h"
#include "AIAC.h"

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::Log::Init();

    [...]

    std::unique_ptr<AIAC::Application> acApp_ptr =
        std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->GetWindow()->Init();

    acApp_ptr->GetGORegistry()->Init();

    acApp_ptr->PushLayer<AIAC::LayerCamera>();       // sensor input
    acApp_ptr->PushLayer<AIAC::LayerCameraCalib>();  // calibration
    acApp_ptr->PushLayer<AIAC::LayerSlam>();         // self-localization
    acApp_ptr->PushLayer<AIAC::LayerModel>();        // execution model
    acApp_ptr->PushLayer<AIAC::LayerToolhead>();     // tools attachement
    acApp_ptr->PushLayer<AIAC::LayerFeedback>();     // instructions
    acApp_ptr->PushLayer<AIAC::LayerUI>();           // UI
    acApp_ptr->PushLayer<AIAC::LayerUtils>();        // extra
    acApp_ptr->PushLayer<AIAC::LayerLogRecorder>();  // trajectory recorder

    acApp_ptr->GetRenderer()->Init();

    acApp_ptr->GetEventBus()->Init();
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}
```

## Layer structure

Each layer in the stack inherits from a superclass interface defined in [`Layer.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Layer.h), which includes event-like methods triggered at various points during frame processing (e.g., `OnFrameAwake()`, `OnFrameStart()`, etc.). These methods are invoked by the main `Run()` function in the singleton application loop from [`Application.h`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/AIAC/Application.h). This design allows application tasks to be containerized and executed sequentially and in a temporal fashion.

``` cpp title="src/AIAC/Layer.h" linenums="1"
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
```

So, if you were to add a new layer to the stack, you would need to create a new class that inherits from the `Layer` class and implement the necessary methods. Then, you would push this new layer to the stack in the main file [`ACApp.cpp`](https://github.com/ibois-epfl/augmented-carpentry/tree/main/src/ACApp.cpp).

## Sequential execution

The `Run()` function in the `Application` class is the main loop of the application. It is responsible for executing the layers in the order they were pushed to the stack. This design allows for a sequential execution of the layers, which is crucial for the correct functioning of the AR engine.

``` cpp title="src/AIAC/Application.cpp" hl_lines="9-10 12-13 20-21 25-26" linenums="1"
void Application::Run() {
    m_IsRunning = true;

    while (m_Window->IsOpen())
    {
        if(!m_EventBus->IsEventQueueEmpty())
            m_EventBus->ProcessQueue();

        for (auto& layer : m_LayerStack)
            layer->OnFrameAwake();

        for (auto& layer : m_LayerStack)
            layer->OnFrameStart(); 

        m_Window->OnUpdate();
        m_Renderer->OnRender();

        GetLayer<AIAC::LayerUI>()->OnUIRender();

        for (auto& layer : m_LayerStack)
            layer->OnFrameEnd();

        m_Window->OnBufferSwap();

        for (auto& layer : m_LayerStack)
            layer->OnFrameFall();
    }
}
```

## Layers communication

Data exchange between specific layers is possible through the use of the `AIAC_APP` macro, enabling the retrieval of any particular layer member or function. It can be called from any layer at any moment after the `Run()` is called. For example, the `LayerCamera` can access the `LayerSlam` data by calling:

``` cpp
AIAC_APP->GetLayer<LayerSlam>()->GetCameraPose();
```
!!! Info
    The `AIAC_APP` macro is defined in `Application.h` and is a singleton instance of the `Application` class. It returns a copy to the reference of the application instance.

    ```cpp
    inline static Application& GetInstance() { return *s_Instance; }
    ```

!!! tip
    Exchange between layers can also take place in a more structured way with the integrated event system (`ApplicationEvent.h`), which is capable of queuing events from layers and trigger them in the next main loop. Have a look at the developer [guide for event system](../CONTRIBUTING.md/#event-system).