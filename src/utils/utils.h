#ifndef AC_UTILS_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>

#include <sys/stat.h>

#include "AIAC/Log.h"

#include "glm/glm.hpp"

inline bool IsFileExist (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

// inline glm::vec3 GetProjectionPointOnPlane(glm::vec3 planeNormal, glm::vec3 planePoint, glm::vec3 point)
// {
//     glm::vec3 v = point - planePoint;
//     float d = glm::dot(planeNormal, v);
//     return point - d * planeNormal;
// }

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

#define AC_UTILS_H

#endif //AC_UTILS_H
