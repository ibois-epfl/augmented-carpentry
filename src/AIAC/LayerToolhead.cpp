#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/LayerToolhead.h"
#include "AIAC/Config.h"

#include <QApplication>
#include <QThread>

#include "ttool.hh"


namespace AIAC
{
    void LayerToolhead::OnAttach()
    {
        std::cout << "BEGIN Main\n";
        int argc = 1;
        char* argv[] = { "augmented_carpentry" };
        QApplication app(argc, argv);
        
        ttool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, ":("),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, ":(")
            );
        ttool->ReleaseCurrent();
        std::cout << "END Main\n";
    }

    void LayerToolhead::OnFrameStart()
    {
        AIAC_APP.GetWindow()->ReleaseCurrent();
        ttool->MakeCurrent();
        ttool->ReleaseCurrent();
        AIAC_APP.GetWindow()->MakeCurrent();
    }
}