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
# pragma once
# include <glm/glm.hpp>

namespace AIAC{
    /**
     * @brief Get the rotation matrix associated with counterclockwise rotation about
     * the given axis by theta radians.
     *
     * @param axis The axis of rotation.
     * @param theta The angle of rotation in radians.
     *
     * @return The rotation matrix.
     */
    glm::mat3x3 GetRotationMatrix(glm::vec3 axis, float theta);

    /**
     * @brief Get the translation matrix associated with the given translation vector
     * 
     * @param translationVector The translation vector
     * 
     * @return The translation matrix
    */
    glm::mat4x4 GetTranslationMatrix(glm::vec3 translationVector);

    /**
     * @brief Get the rigid transformation matrix from two correlated set of 3D points
     * @praam srcPts The source points
     * @param dstPts The destination points
     */
    glm::mat4x4 GetRigidTransformationMatrix(std::vector<glm::vec3> srcPts, std::vector<glm::vec3> dstPts);
}