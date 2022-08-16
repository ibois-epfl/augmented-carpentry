#include "aiacpch.h"
#include "AIAC.h"


int main(int argc, char* argv[]) {
#ifdef __linux__

    // Init Log sys
    AIAC::Log::Init();

    // Init Config
    AIAC::Config config("config.ini", true);



#if 0
    /*
    - set flag for monitor or debug
    - detect the monitor if it s correct
    - configure the monitor HDMI if not done before??

    - init the glfw in full screen(borderless) directly on the monitor monitor
    */


    // general params from config
    std::string monitor_name_s = config.Get<std::string>("MonitorSpecs", "monitor_name", "WaveShare WS170120");
    const char* monitor_name = monitor_name_s.c_str();
    AIAC_INFO("Monitor name from config: {0}", monitor_name);

    std::string monitor_link_t_s = config.Get<std::string>("MonitorSpecs", "monitor_link_t", "HDMI");
    const char* monitor_lin_t = monitor_link_t_s.c_str();
    AIAC_INFO("Monitor link type from config: {0}", monitor_lin_t);

    std::string resolution_s = config.Get<std::string>("MonitorSpecs", "monitor_resolution", "800x480");
    const char* resolution = resolution_s.c_str();
    AIAC_INFO("Monitor resolution from config: {0}", resolution);


    int32_t monitor_id = -1;



    FILE* fpipe;



    // get the monitor id
    const char* command = "xinput";

    if ( !(fpipe = (FILE*)popen(command, "r")) ) {
        AIAC_ERROR("popen() failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fpipe)) {
        if (strstr(buffer, monitor_name))
        {
            AIAC_INFO("Found monitor: {0}", buffer);

            char* monitor_id_ptr = strstr(buffer, "id=");
            monitor_id_ptr = strchr(monitor_id_ptr, '=') + 1;
            monitor_id_ptr[3] = '\0';
            monitor_id = atoi(monitor_id_ptr);

            break;
        }
    }
    pclose(fpipe);

    if (monitor_id == -1) {
        AIAC_ERROR("monitor not found");
        exit(EXIT_FAILURE);
    }
    AIAC_INFO("monitor id: {0}", monitor_id);


     // check if there are more than two monitors of the same link type and the res corresponds to config
    command = "xrandr";

    if ( fpipe = (FILE*)popen(command, "r") )
    {
        int monitor_linked_count_of_type = 0;

        while (fgets(buffer, sizeof(buffer), fpipe)) {
            
            if (strstr(buffer, monitor_lin_t))
            {
                // CHECK DOUBLE MONITORS
                monitor_linked_count_of_type++;
                if (monitor_linked_count_of_type > 1) {
                    AIAC_ERROR("There are more than one monitor of the same link type");
                    exit(EXIT_FAILURE);
                }

                // CHECK MONITOR RESOLUTION
                if (strstr(buffer, resolution))
                {
                    if (strstr(buffer, resolution))
                    {
                        AIAC_INFO("Found monitor resolution: {0}", resolution);
                    }
                    else
                    {
                        AIAC_ERROR("Monitor resolution not found");
                        exit(EXIT_FAILURE);
                    }
                }

            }
        }
        pclose(fpipe);
    }
    else
    {
        AIAC_ERROR("popen() failed");
        exit(EXIT_FAILURE);
    }


    // configure the monitor
    std::string command_mto = "xinput map-to-output ";
    command_mto += std::to_string(monitor_id);
    command_mto += " ";
    command_mto += monitor_lin_t;
    command_mto += "-0";

    int command_mto_result = system(command_mto.c_str());
    if (command_mto_result != 0) { AIAC_CRITICAL("Monitor failed to map to {0}", monitor_lin_t); exit(EXIT_FAILURE); }
    else {AIAC_INFO("Monitor successfully mapped to {0}", monitor_lin_t);}





    return 0;

#endif





    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";
    appSpec.WinWidth = 1280;
    appSpec.WinHeight = 720;
    appSpec.IsResizable = true;
    appSpec.WindowBackColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->PushLayer<AIAC::LayerCamera>();
    acApp_ptr->PushLayer<AIAC::LayerExample>();
    acApp_ptr->PushLayer<AIAC::LayerSlam>();
    acApp_ptr->PushLayer<AIAC::LayerRender>();
    acApp_ptr->PushLayer<AIAC::LayerUI>();

    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}