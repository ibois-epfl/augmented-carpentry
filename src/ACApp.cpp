
#include "AIAC.hpp"


int main(int argc, char* argv[]) {

    std::unique_ptr<AIAC::Application> app_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application());  // TODO: not sure if we need unique_ptr here

    app_ptr->Run();

    return 0;
}
