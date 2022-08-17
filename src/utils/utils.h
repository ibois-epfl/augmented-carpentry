//
// Created by tpp on 15.08.22.
//

#ifndef AC_UTILS_H

#include <opencv2/opencv.hpp>
#include <string>
#include <sys/stat.h>

inline bool IsFileExist (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

#define AC_UTILS_H

#endif //AC_UTILS_H
