#ifndef AC_UTILS_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <time.h>
#include <sstream>
#include "AIAC/Log.h"
#include "glm/glm.hpp"

inline bool IsFileExist (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}


/**
 * @brief Get current date/time, format is YYYY-MM-DD.HH:mm
*/
inline const std::string GetCurrentDateTime() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    
    std::ostringstream ss;
    ss << (now->tm_year + 1900) << '-' 
       << (now->tm_mon + 1) << '-'
       <<  now->tm_mday << '-'
       <<  now->tm_hour << '-'
       <<  now->tm_min << '-'
       <<  now->tm_sec;
    
    return ss.str();
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

inline std::vector<std::string> GetFolderPaths(const std::string& dirPath)
{
    // check the dirPath is a directory and it exists
    if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
    {
        AIAC_ERROR("Error: {0} is not a directory or it does not exist!", dirPath);
        return std::vector<std::string>();
    }

    std::vector<std::string> folderPaths;

    for (const auto & entry : std::filesystem::directory_iterator(dirPath))
    {
        if (entry.is_directory())
        {
            folderPaths.push_back(entry.path());
        }
    }

    return folderPaths;
}

inline std::vector<std::string> GetFilePaths(const std::string& dirPath, const std::string& extension)
{
    // check the dirPath is a directory and it exists
    if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
    {
        AIAC_ERROR("Error: {0} is not a directory or it does not exist!", dirPath);
        return std::vector<std::string>();
    }

    std::vector<std::string> filePaths;

    for (const auto & entry : std::filesystem::directory_iterator(dirPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == extension)
        {
            filePaths.push_back(entry.path());
        }
    }

    return filePaths;
}

inline std::vector<std::string> ParseConfigFile(const std::string& configPath, std::string entryName)
{
    cv::FileStorage fs(configPath, cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        AIAC_ERROR("Error: {0} is not a valid file!", configPath);
        return std::vector<std::string>();
    }

    cv::FileNode fn = fs[entryName];

    if (fn.empty())
    {
        AIAC_ERROR("Error: {0} is not a valid entry name!", entryName);
        return std::vector<std::string>();
    }

    std::vector<std::string> filePaths;

    for (auto it = fn.begin(); it != fn.end(); ++it)
    {
        filePaths.push_back((std::string)*it);
    }

    return filePaths;
}

inline long GetCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

#define AC_UTILS_H

#endif //AC_UTILS_H
