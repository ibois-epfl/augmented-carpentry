#include "aiacpch.h"

#include "AIAC/LayerToolhead.h"

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
            "/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/config.yml",
            "/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/calibration_orange_B_1280_720_r.yml"
            );
        std::cout << "END Main\n";
        ttool->doneCurrent();
    }

    void LayerToolhead::OnFrameStart()
    {
        // ttool->makeCurrent();

        // std::cout << "TTool: using context from ttool\n";

        // ttool->doneCurrent();
    }
}