#pragma once

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC::Utils {
    class HoleToolheadAxisExporter {
    public:
        HoleToolheadAxisExporter(const std::string& basePath);
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
        void WriteCoordToBuffer(const std::string& itemType,
                              std::string itemName,
                              const std::string& pointType,
                              std::shared_ptr<GOPoint> goPoint);

        void WriteBufferToFile();
        void ExportCoordinates();
        std::string GetCurrentTimestamp();



    private:
        /// Default path to save the hole and toolhead coordinates
        std::string m_BasePath;
        /// Default name for .log file
        std::string m_FileName = "coordinates.log";

        std::ostringstream m_Buffer;

    };
}