#pragma once

#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

inline void CvtGlmMat2CvMat(const glm::mat4 &glmMat, cv::Mat &cvMat)
{
    cvMat = cv::Mat(4, 4, CV_32FC1);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cvMat.at<float>(i, j) = glmMat[j][i];
        }
    }
}

inline void CvtCvMat2GlmMat(const cv::Mat &cvMat, glm::mat4 &glmMat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glmMat[j][i] = cvMat.at<float>(i, j);
        }
    }
}

inline void CvtCvMat2GlmMat(const cv::Mat &cvMat, glm::mat3 &glmMat)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            glmMat[j][i] = cvMat.at<float>(i, j);
        }
    }
}

/**
 * @brief Convert a rotation matrix to a quaternion
 *
 * @param R The rotation matrix
 * @return cv::Vec4f The quaternion
 */
inline cv::Vec4f ConvertRotationMatrixToQuaternion(cv::Mat R) {
    cv::Vec4f q;
    q[3] = sqrt(1.0 + R.at<float>(0,0) + R.at<float>(1,1) + R.at<float>(2,2)) / 2.0;
    q[0] = (R.at<float>(2,1) - R.at<float>(1,2)) / (4.0 * q[3]);
    q[1] = (R.at<float>(0,2) - R.at<float>(2,0)) / (4.0 * q[3]);
    q[2] = (R.at<float>(1,0) - R.at<float>(0,1)) / (4.0 * q[3]);
    return q;
}

/**
 * @brief Convert a Transformation matrix to a translation vector and a quaternion vector
 *
 * @param transMat cv::Mat4x4 The transformation matrix
 * @param tvec cv::Vec3f The output of the translation vector
 * @param qvec cv::Vec4f The output of the quaternion vector
 *
 * @return empty
 */
inline void ConvertTransMatToTvecAndQvec(cv::Matx44f transMat, cv::Vec3f &tvec, cv::Vec4f &qvec) {
    auto tTransMat = cv::Mat(transMat);

    tvec[0] = tTransMat.at<float>(0, 3);
    tvec[1] = tTransMat.at<float>(1, 3);
    tvec[2] = tTransMat.at<float>(2, 3);

    cv::Mat R = tTransMat(cv::Rect(0, 0, 3, 3));
    qvec = ConvertRotationMatrixToQuaternion(R);
}