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
        void RunCalibration(cv::Mat *imgForDisplay = nullptr);
        void Save(const std::string& filename);
        int GetImageAmount() const { return imageList.size(); }
        void ClearImages() { imageList.clear(); }

    private:
        void ValidateAndUpdateFlag();
        void DetectPattern(cv::Mat *imgForDisplay = nullptr);
        void CalcBoardCornerPositions(std::vector<cv::Point3f>& corners) const;

    public:
        cv::Size boardSize = cv::Size(13, 9);  // The size of the board -> Number of items by width and height
        Pattern calibrationPattern = Pattern::CHESSBOARD;   // One of the Chessboard, circles, or asymmetric circle pattern
        float squareSize = 20.0f;                           // The size of a square in your defined unit (point, millimeter,etc).
        float aspectRatio = 0.0f;                           // The aspect ratio, can be 0 if no need
        bool writeExtrinsics = true;                        // Write extrinsic parameters
        bool calibZeroTangentDist = true;                   // Assume zero tangential distortion
        bool calibFixPrincipalPoint = true;                 // Fix the principal point at the center
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

