#include "AIAC/Image.h"

namespace AIAC
{
    Image::Image()
    {

    }

    Image::Image(cv::Mat cvImg)
    {
        UpdateData(cvImg);
    }

    Image::Image(AIAC::Image &img)
    {
        UpdateData(img.m_Data);
    }
    
    Image::Image(const char* path)
    {

    }

    Image::~Image()
    {

    }
    
    void Image::UpdateData(cv::Mat cvImg)
    {
        m_Data = cvImg;
        m_Width = cvImg.rows;
        m_Height = cvImg.cols;

        switch (cvImg.channels())
        {
        case 1:
            m_Format = ImageFormat::GRAYSCALE; break;
        case 3:
            m_Format = ImageFormat::RGB; break;
        case 4:
            m_Format = ImageFormat::RGBA; break;
        default:
            m_Format = ImageFormat::None; break;
        }
    }

    void operator>>(cv::VideoCapture cap, AIAC::Image &img)
    {
        cv::Mat cvImg;
        cap >> cvImg;
        img.UpdateData(cvImg);
    }
}