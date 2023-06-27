#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/LayerToolhead.h"

#include <QApplication>
#include <QThread>

#include "ttool.hh"


namespace AIAC
{
    void LayerToolhead::OnAttach()
    {
        AIAC_APP.GetWindow()->ReleaseCurrent();
        std::cout << "BEGIN Main\n";
        int argc = 1;
        char* argv[] = { "augmented_carpentry" };
        QApplication app(argc, argv);
        
        ttool = std::make_shared<ttool::TTool>(
            "/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/config.yml",
            "/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/calibration_orange_B_1280_720_r.yml"
            );
        std::cout << "END Main\n";
        AIAC_APP.GetWindow()->MakeCurrent();
    }

    void LayerToolhead::OnFrameStart()
    {
        AIAC_APP.GetWindow()->ReleaseCurrent();

        AIAC_APP.GetWindow()->MakeCurrent();
    }
}