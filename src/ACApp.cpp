
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

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";
    appSpec.WinWidth = 1280;
    appSpec.WinHeight = 720;
    appSpec.IsResizable = true;
    appSpec.WindowBackColor = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->PushLayer<AIAC::LayerUI>();

    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}