#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <ctime>
#include <sstream>
#include "AIAC/Log.h"
#include "glm/glm.hpp"


/**
 * @brief Get current date/time, format is YYYY-MM-DD.HH:mm
 */
inline std::string GetCurrentDateTime() {
    std::time_t t = std::time(nullptr);   // get time now
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


/**
 * @brief Get current timestamp in milliseconds
 */
inline long GetCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


/**
 * @brief Check if the given file exists
 *
 * @param name
 */
inline bool IsFileExist (const std::string& name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}


/**
 * @brief Get all sub-folders' paths in the given directory
 *
 * @param folderPath
 */
inline std::vector<std::string> GetFolderPaths(const std::string& dirPath)
{
    // check the dirPath is a directory and it exists
    if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
    {
        AIAC_ERROR("Error: {0} is not a directory or it does not exist!", dirPath);
        return {};
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


/**
 * @brief Get all file paths with the given extension in the given directory
 *
 * @param dirPath
 * @param extension
 */
inline std::vector<std::string> GetFilePaths(const std::string& dirPath, const std::string& extension)
{
    // check the dirPath is a directory and it exists
    if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
    {
        AIAC_ERROR("Error: {0} is not a directory or it does not exist!", dirPath);
        return {};
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


/**
 * @brief Copy the file from source to destination
 *
 * @param source the source file path
 * @param destination the destination file path
 */
inline void CopyFile(const std::string& source, const std::string& destination)
{
    std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
}


/**
 * @brief Parse the config file and get the file paths
 *
 * @param configPath
 * @param entryName
 */
inline std::vector<std::string> ParseConfigFile(const std::string& configPath, const std::string& entryName)
{
    cv::FileStorage fs(configPath, cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        AIAC_ERROR("Error: {0} is not a valid file!", configPath);
        return {};
    }

    cv::FileNode fn = fs[entryName];

    if (fn.empty())
    {
        AIAC_ERROR("Error: {0} is not a valid entry name!", entryName);
        return {};
    }

    std::vector<std::string> filePaths;

    for(auto && it : fn)
    {
        filePaths.push_back((std::string)it);
    }

    return filePaths;
}

/**
* @brief Get the name of the file from the given path
*/
inline std::string GetFileNameFromPath(const std::string& path, bool withExtension = true)
{
    std::filesystem::path p(path);
    if (withExtension)
    {
        return p.filename().string();
    }
    return p.stem().string();
}