
#include "AIAC.hpp"


int main(int argc, char* argv[]) {

    AIAC::ApplicationSpecification appSpec;
    appSpec.name = "augmented_carpentry";
    appSpec.winWidth = 1280;
    appSpec.winHeight = 720;
    appSpec.isFullscreen = false;

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));  // TODO: not sure if we need unique_ptr here

    acApp_ptr->Run();

    return 0;
}
