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
#include <vector>
#include <map>
#include <set>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "AIAC/GOSys/GOPrimitive.h"
#include "pugixml.hpp"

namespace AIAC{
class ScannedModel{
public:
    ScannedModel(){};
    ~ScannedModel(){};

    /**
     * @brief Load a .ply model from a file.
     * @param path Path to the model file.
     * @return True if the model is loaded successfully, false otherwise.
     */
    bool Load(std::string path);

    /**
     * @brief Build the bounding box based on the ply model.
     */
    void BuildBoundingBox();

    /**
     * @brief Get the bounding box of the ply model.
     * @return The bounding box of the ply model.
     */
    std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }
    std::vector<std::pair<int, int> > GetBboxEdgesIndices() const { return m_BboxEdgesIndices; }
    /**
     * @brief Update Boundary Box GOLine
     */
    void UpdateBboxGOLine();

    /**
     * @brief Get the length of the scanned model, which is calculated by averaging the four edges of the bounding box.
     * @return The length of the scanned model. (in TSLAM unit)
     */
    float GetLength();

private:
    std::vector<glm::vec3> m_Bbox;
    std::vector<std::pair<int, int> > m_BboxEdgesIndices = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // bottom
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // top
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // vertical
    };

    std::shared_ptr<GOMesh> m_Mesh;
    std::vector<std::shared_ptr<GOLine> > m_BboxGOLines;
};

}
