
#include "AIAC.h"
/*
Layer pattern notes:
The layer aare first stacked to be rendered in order, then the layers are updated in reverse order
Following events (?)

These are different classes: e.g. UILayer.h, SLAMLayer.h, etc.

0. Layer Camera = reading frame from camera
1. Layer SLAM = get camera frame, run SLAM
2. Layer SENSing = image analysis for toolhead pose detection
2. Layer 3DEngine = get camera frame, and SLAM pose and create 3D space
3. Layer Render = render AR frame + 3D visualizer
4. Layer AR overlay = overlay information on top for augmented instruction (feedbacks)
5. Layer UI = render UI
*/

// class ExampleLayer1 : public AIAC::Layer
// {
// public:
//     virtual void OnAttach() override 
//     {
//         AIAC_INFO("ExampleLayer1 attached");
//         AIAC::Application& app = AIAC::Application::GetInstance();
//         AIAC::ApplicationSpecification spec = app.GetSpecification();
//     }

//     virtual void OnFrameAwake() override 
//     {
//         AIAC_INFO("ExampleLayer1 OnFrameAwake");
//     }

//     virtual void OnFrameStart() override 
//     {
//         AIAC_INFO("ExampleLayer1 frame start");
//     }

//     virtual void OnFrameEnd() override 
//     {
//         AIAC_INFO("ExampleLayer1 frame end");
//     }

//     virtual void OnUIRender() override
//     {
//         // draw viewport half screen
//         ImGui::Begin("Hello ExampleLayer1");
//         ImGui::Button("Button ExampleLayer1");
//         ImGui::Text("This is my UI stuff for the ExampleLayer1");
//         ImGui::End();
//     }

//     virtual void OnFrameFall() override 
//     {
//         AIAC_INFO("ExampleLayer1 is fall");
//     }

//     virtual void OnDetach() override
//     {
//         AIAC_INFO("ExampleLayer1 detached");
//     }
// };

class ExampleLayer2 : public AIAC::Layer
{
public:
    virtual void OnAttach() override 
    {
        AIAC_INFO("ExampleLayer2 attached");
    }

    virtual void OnFrameAwake() override 
    {
        AIAC_INFO("ExampleLayer2 OnFrameAwake");
        // AIAC_INFO(m_WindowHeight);
    }

    virtual void OnFrameStart() override 
    {
        AIAC_INFO("ExampleLayer2 frame start");
    }

    virtual void OnFrameEnd() override 
    {
        AIAC_INFO("ExampleLayer2 frame end");
    }

    virtual void OnUIRender() override
    {
        ImGui::Begin("Hello ExampleLayer2");
        ImGui::Button("Button ExampleLayer2");
        ImGui::Text("This is my UI stuff for the ExampleLayer2");
        ImGui::End();
    }

    virtual void OnFrameFall() override 
    {
        AIAC_INFO("ExampleLayer2 is fall");
    }

    virtual void OnDetach() override
    {
        AIAC_INFO("ExampleLayer2 detached");
    }
};




int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::ApplicationSpecification appSpec;
    appSpec.name = "augmented_carpentry";
    appSpec.winWidth = 1280;
    appSpec.winHeight = 720;
    appSpec.isFullscreen = false;

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->PushLayer<AIAC::LayerExample>();
    // acApp_ptr->PushLayer<ExampleLayer2>();

    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}