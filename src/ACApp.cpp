#include "aiacpch.h"
#include "AIAC.h"


int main(int argc, char* argv[]) {
#ifdef __linux__

    // Init Log sys
    AIAC::Log::Init();

    // Init Config
    AIAC::Config config("config.ini", true);

    // Init Monitor
    std::unique_ptr<AIAC::Monitor> monitor = std::unique_ptr<AIAC::Monitor>(new AIAC::Monitor());
    AIAC_INFO("Is monitor touch {0}", monitor->IsTouch());

    // Init Application
    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";
    appSpec.WinWidth = 1280;
    appSpec.WinHeight = 720;
    appSpec.IsResizable = true;
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