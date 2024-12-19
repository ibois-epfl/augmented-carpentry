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
#include "GeometryUtils.h"

namespace AIAC{
    glm::mat3x3 GetRotationMatrix(glm::vec3 axis, float theta){
        // normalize axis
        axis = glm::normalize(axis);

        float a = cos(theta / 2.0f);
        float b = -axis.x * sin(theta / 2.0f);
        float c = -axis.y * sin(theta / 2.0f);
        float d = -axis.z * sin(theta / 2.0f);
        float aa = a * a;
        float bb = b * b;
        float cc = c * c;
        float dd = d * d;
        float bc = b * c;
        float ad = a * d;
        float ac = a * c;
        float ab = a * b;
        float bd = b * d;
        float cd = c * d;

        glm::mat3x3 mat;
        mat[0][0] = aa + bb - cc - dd;
        mat[0][1] = 2 * (bc + ad);
        mat[0][2] = 2 * (bd - ac);
        mat[1][0] = 2 * (bc - ad);
        mat[1][1] = aa + cc - bb - dd;
        mat[1][2] = 2 * (cd + ab);
        mat[2][0] = 2 * (bd + ac);
        mat[2][1] = 2 * (cd - ab);
        mat[2][2] = aa + dd - bb - cc;

        return mat;
    }

    glm::mat4x4 GetTranslationMatrix(glm::vec3 translationVector)
    {
        return glm::mat4x4(
            1, 0, 0, translationVector.x,
            0, 1, 0, translationVector.y,
            0, 0, 1, translationVector.z,
            0, 0, 0, 1
        );
    }

    glm::mat4x4 GetRigidTransformationMatrix(std::vector<glm::vec3> srcPts, std::vector<glm::vec3> dstPts) {
        glm::mat4x4 rigidTransformMatrix = glm::mat4x4(1.0f);

        // find mean column wise
        glm::vec3 centroidSrc = glm::vec3(0.0f);
        glm::vec3 centroidDst = glm::vec3(0.0f);
        for (int i = 0; i < srcPts.size(); i++) {
            centroidSrc += srcPts[i];
            centroidDst += dstPts[i];
        }
        centroidSrc /= srcPts.size();
        centroidDst /= dstPts.size();

        // subtract mean
        std::vector<glm::vec3> srcPtsM = srcPts;
        std::vector<glm::vec3> dstPtsM = dstPts;
        for (int i = 0; i < srcPts.size(); i++) {
            srcPtsM[i] -= centroidSrc;
            dstPtsM[i] -= centroidDst;
        }

        // find H
        glm::mat3x3 H = glm::mat3x3(0.0f);
        for (int i = 0; i < srcPts.size(); i++) {
            H += glm::outerProduct(srcPtsM[i], dstPtsM[i]);
        }

        // convert H to opencv for SVD
        H = glm::transpose(H);
        cv::Mat cvH = cv::Mat(3, 3, CV_32FC1);
        for (int i = 0; i < 3; i++) {
            cvH.at<float>(i, 0) = H[i][0];
            cvH.at<float>(i, 1) = H[i][1];
            cvH.at<float>(i, 2) = H[i][2];
        }

        // find rotation
        cv::Mat cvU, cvVt, cvS;
        cv::SVD::compute(cvH, cvS, cvU, cvVt);

        // convert back to glm
        glm::mat3x3 U = glm::mat3x3(0.0f);
        glm::mat3x3 Vt = glm::mat3x3(0.0f);
        for (int i = 0; i < 3; i++) {
            U[i][0] = cvU.at<float>(i, 0);
            U[i][1] = cvU.at<float>(i, 1);
            U[i][2] = cvU.at<float>(i, 2);
            Vt[i][0] = cvVt.at<float>(i, 0);
            Vt[i][1] = cvVt.at<float>(i, 1);
            Vt[i][2] = cvVt.at<float>(i, 2);
        }
//        Since we are using opencv, we don't need to transpose
//        U = glm::transpose(U);
//        Vt = glm::transpose(Vt);

        glm::mat3x3 R = Vt * U;

        // special reflection case
        if (glm::determinant(R) < 0) {
            Vt[2] *= -1;
            R = Vt * U;
        }

        glm::vec3 t = -R * centroidSrc + centroidDst;

        rigidTransformMatrix = glm::mat4x4(R);
        rigidTransformMatrix[3] = glm::vec4(t, 1.0f);

        return rigidTransformMatrix;
    }

}