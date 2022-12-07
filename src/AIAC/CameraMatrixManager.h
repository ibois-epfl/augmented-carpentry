#pragma once
/*
 * The purpose of this manager is to provide a better way to access the camera matrix
 * and the distortion coefficients.
 *
 * We have two sources of camera parameters: one from the configuration file and one from the
 * SLAM map. To maintain consistency, we need to make sure that the one from SLAM map is being
 * used during tracking.
 *
 * The idea is:
 *  - When the application starts, we load a default camera parameters.
 *  - When the SLAM map is loaded, we load the camera parameters from the SLAM map and override
 *    the camera matrix, but not for distortion coefficients.
 */
namespace AIAC {
    class CameraMatrixManager {

    };
}