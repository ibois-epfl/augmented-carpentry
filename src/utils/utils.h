//
// Created by tpp on 15.08.22.
//

#ifndef AC_UTILS_H

#include <opencv2/opencv.hpp>
#include <string>
#include <sys/stat.h>

#include "glm/glm.hpp"

inline bool IsFileExist (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

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

#define AC_UTILS_H

#endif //AC_UTILS_H
