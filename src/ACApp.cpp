
#include "AIAC.h"

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::ApplicationSpecification appSpec;
    appSpec.name = "augmented_carpentry";
    appSpec.winWidth = 1280;
    appSpec.winHeight = 720;
    appSpec.isFullscreen = false;

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}