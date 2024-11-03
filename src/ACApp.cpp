#include "aiacpch.h"
#include "AIAC.h"

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::Log::Init();

    // by default, take the config.ini in the root folder
    std::string configPath = "config.ini";
    if (argc >= 2){
        configPath = argv[1];
    }
    AIAC::Config config(configPath, true);

    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";  // かくちょう_だいく
    appSpec.WinWidth = 800;
    appSpec.WinHeight = 480;
    appSpec.IsResizable = false;
    appSpec.VSync = true;
    appSpec.WindowBackColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->GetWindow()->Init();

    acApp_ptr->GetGORegistry()->Init();

    acApp_ptr->PushLayer<AIAC::LayerCamera>();
    acApp_ptr->PushLayer<AIAC::LayerCameraCalib>();
    acApp_ptr->PushLayer<AIAC::LayerSlam>();
    acApp_ptr->PushLayer<AIAC::LayerModel>();
    acApp_ptr->PushLayer<AIAC::LayerToolhead>();
    acApp_ptr->PushLayer<AIAC::LayerFeedback>();
#ifndef HEADLESS_TEST
    acApp_ptr->PushLayer<AIAC::LayerUI>();
#endif
    acApp_ptr->PushLayer<AIAC::LayerUtils>();
    acApp_ptr->PushLayer<AIAC::LayerLogRecorder>();

    acApp_ptr->GetRenderer()->Init();

    acApp_ptr->GetEventBus()->Init();
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}
