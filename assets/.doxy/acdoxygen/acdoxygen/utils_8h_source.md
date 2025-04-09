

# File utils.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**utils.h**](utils_8h.md)

[Go to the documentation of this file](utils_8h.md)


```C++
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

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <ctime>
#include <sstream>
#include "AIAC/Log.h"
#include "glm/glm.hpp"


inline std::string GetCurrentDateTime() {
    std::time_t t = std::time(nullptr);   // get time now
    std::tm* now = std::localtime(&t);
    
    std::ostringstream ss;
    ss << (now->tm_year + 1900) << '-'
       << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << '-'
       << std::setw(2) << std::setfill('0') <<  now->tm_mday << '-'
       << std::setw(2) << std::setfill('0') <<  now->tm_hour << '-'
       << std::setw(2) << std::setfill('0') <<  now->tm_min << '-'
       << std::setw(2) << std::setfill('0') <<  now->tm_sec;

    return ss.str();
}


inline long GetCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


inline bool IsFileExist (const std::string& name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}


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


inline void CopyFile(const std::string& source, const std::string& destination)
{
    std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
}


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

inline std::string GetFileNameFromPath(const std::string& path, bool withExtension = true)
{
    std::filesystem::path p(path);
    if (withExtension)
    {
        return p.filename().string();
    }
    return p.stem().string();
}
```


