#pragma once

#include <string_view>
#include <stdint.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

namespace AIAC
{
    enum class ImageFormat
    {
        None = 0,
        RGB,
        RGBA,
        GRAYSCALE
    };

    class Image
    {
    public:
        Image();
        Image(cv::Mat cvImg);
        Image(AIAC::Image &img);
        Image(const char* path);
        ~Image();

        cv::Mat GetCvMat() const { return m_Data; }

        void UpdateData(cv::Mat cvImg);

        void operator=(cv::Mat cvImg){ UpdateData(cvImg); }

    private:
        const char* m_Path;
        
        cv::Mat m_Data = cv::Mat();

        uint32_t m_Width = 0, m_Height = 0;
        ImageFormat m_Format = ImageFormat::None;
        size_t m_Size = 0;

    friend void operator>>(cv::VideoCapture cap, AIAC::Image &img);
 
    };
}