#include "aiacpch.h"

#include "AIAC/LayerToolhead.h"

#include <QApplication>
#include <QThread>

namespace AIAC
{
    LayerToolhead::LayerToolhead() {
        int argc = 1;
        char* argv[] = { "augmented_carpentry" };
        QApplication app(argc, argv);

        std::shared_ptr<ttool::TTool> ttool = std::make_shared<ttool::TTool>("/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/config.yml", "/home/tpp/IBOIS/augmented-carpentry/deps/TTool/assets/calibration_orange_B_1280_720_r.yml");
    }

    void LayerToolhead::OnAttach() {}
    void LayerToolhead::OnFrameStart() {}
}