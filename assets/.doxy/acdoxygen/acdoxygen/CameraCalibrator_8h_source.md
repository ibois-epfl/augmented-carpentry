

# File CameraCalibrator.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**CameraCalibrator.h**](CameraCalibrator_8h.md)

[Go to the documentation of this file](CameraCalibrator_8h.md)


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
# pragma once
#include <iostream>

#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

namespace AIAC{
    class CameraCalibrator {
    public:
        enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };

        CameraCalibrator() {};
        ~CameraCalibrator() {};

        void AddImage(const cv::Mat& image);
        bool RunCalibration(cv::Mat *imgForDisplay = nullptr);
        void Save(const std::string& filename);
        int GetImageAmount() const { return imageList.size(); }
        void ClearImages() { imageList.clear(); imagePoints.clear(); }

    private:
        void ValidateAndUpdateFlag();
        void DetectPattern(cv::Mat *imgForDisplay = nullptr);
        void CalcBoardCornerPositions(std::vector<cv::Point3f>& corners) const;

    public:
        cv::Size boardSize = cv::Size(19, 13);  // The size of the board -> Number of items by width and height
        Pattern calibrationPattern = Pattern::CHESSBOARD;   // One of the Chessboard, circles, or asymmetric circle pattern
        float squareSize = 20.0f;                           // The size of a square in your defined unit (point, millimeter,etc).
        float aspectRatio = 0.0f;                           // The aspect ratio, can be 0 if no need
        bool writeExtrinsics = true;                        // Write extrinsic parameters
        bool calibZeroTangentDist = false;                  // Assume zero tangential distortion
        bool calibFixPrincipalPoint = false;                // Fix the principal point at the center
        bool flipVertical = false;                          // Flip the captured images around the horizontal axis
        bool useFisheye = false;                            // use fisheye camera model for calibration
        bool fixDistortion = false;                         // fix K1 distortion coefficient

        bool useFixedPoint = false;                           // Enable this will use different algorithm for calibration
        float gridWidth = squareSize * (boardSize.width - 1); // The width of the board -> number of items in width * squareSize
        int winSize = 11;                                     // The size of the window capturing

        // image Param
        cv::Size imageSize;

        // result
        cv::Mat cameraMatrix;
        cv::Mat distCoeffs;
        cv::Mat rvecs, tvecs;
        double totalAvgErr;
        std::vector<float> reprojErrs;

    private:
        std::vector<cv::Mat> imageList;
        bool goodInput;
        int calibFlag;

        std::vector<std::vector<cv::Point2f> > imagePoints;
    };
}

```


