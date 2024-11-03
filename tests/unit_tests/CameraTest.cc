// #include <gtest/gtest.h>

// #include <cstdlib>
// #include <filesystem>
// #include <iostream>
// #include <fstream>

// #include <gtest/gtest.h>
// #include "AIAC/Camera.h"
// #include "AIAC/Config.h"

// class CameraTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         // Set up any necessary configurations or initializations
//     }

//     void TearDown() override {
//         // Clean up any resources used in the test
//     }
// };

// TEST_F(CameraTest, OpenCameraFromVideo) {
//     AIAC::Camera camera;

//     // Path to the test video in the assets folder
//     std::string videoPath = "../../assets/test_video.mp4";

//     // Mock the configuration to use the test video path
//     AIAC::Config::Set<std::string>(AIAC::Config::SEC_TEST, AIAC::Config::VIDEO_PATH, videoPath);

//     // Open the camera (which will use the video path in HEADLESS_TEST mode)
//     EXPECT_NO_THROW(camera.Open(0));

//     // Check if the camera is opened
//     EXPECT_TRUE(camera.IsOpened());

//     // Capture a frame and check if it is valid
//     AIAC::Image frame = camera.GetNextFrame();
//     EXPECT_FALSE(frame.GetCvMat().empty());
// }
