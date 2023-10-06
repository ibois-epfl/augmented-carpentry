#pragma once

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC::Utils {
    class HoleToolheadAxisExporter {
    public:
        HoleToolheadAxisExporter();
        ~HoleToolheadAxisExporter() = default;

        /// @brief Export the toolhead coordinates
        void ExportToolheadAxis();
        /// @brief Export the hole coordinates
        void ExportHoleAxis();
        /**
         * @brief Write the coordinates to a .log file
         *
         * @param itemType Type of the item (toolhead or hole)
         * @param pointType Type of the point (start or end)
         * @param goPoint Pointer to the GOPoint object to get the coordinates from
         */
        void WriteCoordToFile(const std::string& itemType,
                              const std::string& pointType,
                              std::shared_ptr<GOPoint> goPoint);

    private:
        /// Default path to save the hole and toolhead coordinates
        std::string m_SaveCoordDefaultPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS,
                                                                            AIAC::Config::SAVE_COORD_DEFAULT_PATH);
    };
}
