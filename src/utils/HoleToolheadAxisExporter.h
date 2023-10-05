#pragma once

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC::Utils {
    class HoleToolheadAxisExporter {
    public:
        HoleToolheadAxisExporter();
        ~HoleToolheadAxisExporter();

        void ExportToolheadAxis();
        void ExportHoleAxis();
        void WriteCoordToFile(const std::string& objType, const std::string& pointType, std::shared_ptr<GOPoint> goPoint);

    private:
        std::string m_SaveToolCoordDefaultPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS, AIAC::Config::SAVE_TOOL_COORD_DEFAULT_PATH);
    };
}
