#include "CameraCalibrator.h"

namespace AIAC {
//! [board_corners]
void CameraCalibrator::CalcBoardCornerPositions(
    std::vector<cv::Point3f> & corners) const {
  corners.clear();

  switch (calibrationPattern) {
  case CameraCalibrator::CHESSBOARD:
  case CameraCalibrator::CIRCLES_GRID:
    for (int i = 0; i < boardSize.height; ++i)
      for (int j = 0; j < boardSize.width; ++j)
        corners.push_back(cv::Point3f(j * squareSize, i * squareSize, 0));
    break;

  case CameraCalibrator::ASYMMETRIC_CIRCLES_GRID:
    for (int i = 0; i < boardSize.height; i++)
      for (int j = 0; j < boardSize.width; j++)
        corners.push_back(
            cv::Point3f((2 * j + i % 2) * squareSize, i * squareSize, 0));
    break;
  default:
    break;
  }
}

//! [board_corners]
bool CameraCalibrator::RunCalibration(cv::Mat * imgForDisplay) {
  ValidateAndUpdateFlag();
  DetectPattern(imgForDisplay);

  if (imagePoints.size() < 2) {
    throw std::runtime_error("Not enough points to run calibration");
    return false; // Return after exception is useless !!
  }

  //! [fixed_aspect]
  cameraMatrix = cv::Mat::eye(3, 3, CV_32F);
  if (!useFisheye && calibFlag & cv::CALIB_FIX_ASPECT_RATIO)
    cameraMatrix.at<double>(0, 0) = aspectRatio;
  //! [fixed_aspect]
  if (useFisheye) {
    distCoeffs = cv::Mat::zeros(4, 1, CV_32F);
  } else {
    distCoeffs = cv::Mat::zeros(8, 1, CV_32F);
  }

  std::vector<std::vector<cv::Point3f>> objectPoints(1);
  CalcBoardCornerPositions(objectPoints[0]);
  objectPoints[0][boardSize.width - 1].x = objectPoints[0][0].x + gridWidth;
  auto newObjPoints = objectPoints[0];

  objectPoints.resize(imagePoints.size(), objectPoints[0]);

  // Reprojection error
  double rms;

  if (useFisheye) {
    cv::fisheye::calibrate(objectPoints, imagePoints, imageSize, cameraMatrix,
                           distCoeffs, rvecs, tvecs, calibFlag);
  } else {
    int iFixedPoint = -1;
    if (useFixedPoint)
      iFixedPoint = boardSize.width - 1;
    calibrateCameraRO(objectPoints, imagePoints, imageSize, iFixedPoint,
                      cameraMatrix, distCoeffs, rvecs, tvecs, newObjPoints,
                      calibFlag | cv::CALIB_USE_LU);
  }
  return true;
}

void CameraCalibrator::ValidateAndUpdateFlag() {
  goodInput = true;
  if (boardSize.width <= 0 || boardSize.height <= 0) {
    std::cerr << "Invalid Board size: " << boardSize.width << " "
              << boardSize.height << std::endl;
    goodInput = false;
  }
  if (squareSize <= 10e-6) {
    std::cerr << "Invalid square size " << squareSize << std::endl;
    goodInput = false;
  }

  calibFlag = 0;

  if (calibFixPrincipalPoint)
    calibFlag |= cv::CALIB_FIX_PRINCIPAL_POINT;
  if (calibZeroTangentDist)
    calibFlag |= cv::CALIB_ZERO_TANGENT_DIST;
  if (aspectRatio)
    calibFlag |= cv::CALIB_FIX_ASPECT_RATIO;
  if (fixDistortion)
    calibFlag |= cv::CALIB_FIX_K1 | cv::CALIB_FIX_K2 | cv::CALIB_FIX_K3 |
                 cv::CALIB_FIX_K4 | cv::CALIB_FIX_K5;

  if (useFisheye) {
    // the cv::fisheye model has its own enum, so overwrite the flags
    calibFlag =
        cv::fisheye::CALIB_FIX_SKEW | cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
    if (fixDistortion)
      calibFlag |= cv::fisheye::CALIB_FIX_K1;
    if (fixDistortion)
      calibFlag |= cv::fisheye::CALIB_FIX_K2;
    if (fixDistortion)
      calibFlag |= cv::fisheye::CALIB_FIX_K3;
    if (fixDistortion)
      calibFlag |= cv::fisheye::CALIB_FIX_K4;
    if (calibFixPrincipalPoint)
      calibFlag |= cv::fisheye::CALIB_FIX_PRINCIPAL_POINT;
  }
}

void CameraCalibrator::AddImage(const cv::Mat & image) {
  imageList.push_back(cv::Mat());
  image.copyTo(imageList.back());
}

void CameraCalibrator::DetectPattern(cv::Mat * imgForDisplay) {
  //------------------------- Camera Calibration ------------------------
  int chessBoardFlags =
      cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE;

  if (!useFisheye) {
    // fast check erroneously fails with high distortions like cv::fisheye
    chessBoardFlags |= cv::CALIB_CB_FAST_CHECK;
  }

  for (const auto & img : imageList) {
    imageSize = img.size(); // Format input image.
    if (flipVertical)
      flip(img, img, 0);

    //! [find_pattern]
    std::vector<cv::Point2f> pointBuf;

    bool found;

    switch (calibrationPattern) // Find feature points on the input format
    {
    case Pattern::CHESSBOARD:
      found = findChessboardCorners(img, boardSize, pointBuf, chessBoardFlags);
      break;
    case Pattern::CIRCLES_GRID:
      found = findCirclesGrid(img, boardSize, pointBuf);
      break;
    case Pattern::ASYMMETRIC_CIRCLES_GRID:
      found = findCirclesGrid(img, boardSize, pointBuf,
                              cv::CALIB_CB_ASYMMETRIC_GRID);
      break;
    default:
      found = false;
      break;
    }

    //! [find_pattern]
    //! [pattern_found]
    if (found) // If done with success,
    {
      // improve the found corners' coordinate accuracy for chessboard
      if (calibrationPattern == Pattern::CHESSBOARD) {
        cv::Mat viewGray;
        cvtColor(img, viewGray, cv::COLOR_BGR2GRAY);
        cornerSubPix(
            viewGray, pointBuf, cv::Size(winSize, winSize), cv::Size(-1, -1),
            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT,
                             30, 0.0001));
      }

      imagePoints.push_back(pointBuf);

      // Draw the corners.
      drawChessboardCorners(img, boardSize, cv::Mat(pointBuf), found);
    }

    if (imgForDisplay) {
      img.copyTo(*imgForDisplay);
    }
  }
}

void CameraCalibrator::Save(const std::string & filename) {
  cv::FileStorage fs(filename, cv::FileStorage::WRITE);
  fs << "image_width" << imageSize.width;
  fs << "image_height" << imageSize.height;
  cameraMatrix.convertTo(cameraMatrix, CV_32F);
  distCoeffs.convertTo(distCoeffs, CV_32F);
  fs << "camera_matrix" << cameraMatrix;
  fs << "distortion_coefficients" << distCoeffs;
  fs.release();
}
} // namespace AIAC
