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
        // Adding dummy arguments to make QApplication
        int argc = 1;
        char* argv[] = { "augmented_carpentry" };
        QApplication app(argc, argv);
        
        ttool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, ":("),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, ":(")
            );
        ttool->ReleaseCurrent();
    }

    void LayerToolhead::OnFrameStart()
    {
        AIAC_APP.GetWindow()->ReleaseCurrent();
        ttool->MakeCurrent();
        ttool->ReleaseCurrent();
        AIAC_APP.GetWindow()->MakeCurrent();
    }
}