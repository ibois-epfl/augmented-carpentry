#include "aiacpch.h"
#include "AIAC.h"
#include "AIAC/LayerCameraCalib.h"

#include <QApplication>
#include <QThread>

#include "ttool.hh"
#include "view.hh"

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::Log::Init();

    AIAC::Config config("config.ini", true);

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
    acApp_ptr->GetWindow()->ReleaseCurrent();
    acApp_ptr->PushLayer<AIAC::LayerToolhead>();
    acApp_ptr->GetWindow()->MakeCurrent();
    acApp_ptr->PushLayer<AIAC::LayerInstructor>();
    acApp_ptr->PushLayer<AIAC::LayerFeedback>();
    acApp_ptr->PushLayer<AIAC::LayerUI>();

    // acApp_ptr->GetWindow()->MakeCurrent();
    acApp_ptr->GetRenderer()->Init();

    acApp_ptr->GetEventBus()->Init();

    // acApp_ptr->GetWindow()->ReleaseCurrent();
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}