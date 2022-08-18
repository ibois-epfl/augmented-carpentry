#include "aiacpch.h"
#include "AIAC.h"


int main(int argc, char* argv[]) {
#ifdef __linux__

    // Init Log sys
    AIAC::Log::Init();

    // Init Config
    AIAC::Config config("config.ini", true);

    // // Init MonitorConfig
    // std::unique_ptr<AIAC::MonitorConfig> MonitorConfig = std::unique_ptr<AIAC::MonitorConfig>(new AIAC::MonitorConfig());
    // AIAC_INFO("Is MonitorConfig touch {0}", MonitorConfig->IsTouch());

    // Init Application
    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";  // かくちょう_だいく
    appSpec.WinWidth = 800;
    appSpec.WinHeight = 480;
    appSpec.IsResizable = false;
    appSpec.VSync = true;
    appSpec.WindowBackColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    // Stack layers
    acApp_ptr->PushLayer<AIAC::LayerCamera>();
    acApp_ptr->PushLayer<AIAC::LayerExample>();
    acApp_ptr->PushLayer<AIAC::LayerSlam>();
    acApp_ptr->PushLayer<AIAC::LayerRender>();
    acApp_ptr->PushLayer<AIAC::LayerUI>();

    // RUn AC
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}