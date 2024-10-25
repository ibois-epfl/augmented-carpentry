#include <gtest/gtest.h>
#include "AIAC/Image.h"
#include <opencv2/opencv.hpp>

class ImageTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ImageTest, DefaultConstructor) {
    AIAC::Image img;
    EXPECT_EQ(img.GetWidth(), 0);
    EXPECT_EQ(img.GetHeight(), 0);
    EXPECT_FALSE(img.HasGlTextureObj());
    EXPECT_FALSE(img.HasImTexture());
}

TEST_F(ImageTest, ConstructorWithCvMat) {
    cv::Mat mat(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
    AIAC::Image img(mat);
    EXPECT_EQ(img.GetWidth(), 100);
    EXPECT_EQ(img.GetHeight(), 100);
    EXPECT_TRUE(img.GetCvMat().data != nullptr);
}

TEST_F(ImageTest, ConstructorWithPath) {
    const char* path = "path/to/image.png";
    AIAC::Image img(path);
    EXPECT_EQ(img.GetPath(), path);
}

TEST_F(ImageTest, UpdateData) {
    AIAC::Image img;
    cv::Mat mat(50, 50, CV_8UC3, cv::Scalar(0, 255, 0));
    img.UpdateData(mat);
    EXPECT_EQ(img.GetWidth(), 50);
    EXPECT_EQ(img.GetHeight(), 50);
    EXPECT_TRUE(img.GetCvMat().data != nullptr);
}

TEST_F(ImageTest, Resize) {
    cv::Mat mat(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
    AIAC::Image img(mat);
    img.Resize(50, 50);
    EXPECT_EQ(img.GetWidth(), 50);
    EXPECT_EQ(img.GetHeight(), 50);
}

TEST_F(ImageTest, GetImTexture) {
    cv::Mat mat(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
    AIAC::Image img(mat);
    AIAC::ImTexture texture = img.GetImTexture();
    EXPECT_TRUE(texture.ID != 0);
    EXPECT_EQ(texture.Size.x, 100);
    EXPECT_EQ(texture.Size.y, 100);
}

TEST_F(ImageTest, GetGlTextureObj) {
    cv::Mat mat(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
    AIAC::Image img(mat);
    GLuint textureID = img.GetGlTextureObj();
    EXPECT_TRUE(textureID != 0);
}

TEST_F(ImageTest, ReplaceCvMat) {
    AIAC::Image img;
    cv::Mat mat(50, 50, CV_8UC3, cv::Scalar(0, 255, 0));
    img.ReplaceCvMat(mat);
    EXPECT_EQ(img.GetWidth(), 50);
    EXPECT_EQ(img.GetHeight(), 50);
    EXPECT_TRUE(img.GetCvMat().data != nullptr);
}