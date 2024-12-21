// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#pragma once

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC::Utils {
    class HoleToolheadAxisExporter {
    public:
        explicit HoleToolheadAxisExporter(const std::string& basePath);
        ~HoleToolheadAxisExporter() = default;
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
        /// @brief Export and write the hole and toolhead coordinates
        void ExportCoordinates();
        /// @brief Export the toolhead coordinates
        void ExportToolheadAxis();
        /// @brief Export the hole coordinates
        void ExportHoleAxis();
        /**
         * @brief Write the buffer to a file.
         *
         * The data is written in the following format:
         * ItemType,ItemName,PointType,X,Y,Z
         */
        void WriteBufferToFile();
        /** @brief Get the current timestamp
         *
         * @return A string representing the current timestamp
         */
        std::string GetCurrentTimestamp();

    private:
        /// Default path of utils
        std::string m_BasePath;
        /// Default name for .log file
        std::string m_FileName = "coordinates.log";
        /// Buffer to hold the coordinates
        std::ostringstream m_Buffer;
    };
}
