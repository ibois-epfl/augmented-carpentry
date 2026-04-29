

# File Image.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Image.cpp**](Image_8cpp.md)

[Go to the documentation of this file](Image_8cpp.md)


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
#include "aiacpch.h"

#include "AIAC/Image.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

namespace AIAC
{
    Image::Image() {}
    Image::Image(cv::Mat cvImg) { UpdateData(cvImg); }
    Image::Image(AIAC::Image &img) { UpdateData(img.m_CvMat); }
    Image::Image(const char *path, int cvImReadFlag) {
        cv::Mat cvImg = cv::imread(path, cvImReadFlag);
        UpdateData(cvImg);
    }

    Image::~Image() { DeleteGlTexture(); }
    
    void Image::UpdateData(cv::Mat cvImg)
    {
        cvImg.copyTo(m_CvMat);
        cvImg.copyTo(m_PureCvMat);

        switch (cvImg.channels())
        {
        case 1:
            m_Format = ImageFormat::GRAYSCALE; break;
        case 3:
            cv::cvtColor(m_CvMat, m_CvMat, cv::COLOR_BGR2RGB);
            m_Format = ImageFormat::RGB; break;
        case 4:
            cv::cvtColor(m_CvMat, m_CvMat, cv::COLOR_BGRA2RGBA);
            m_Format = ImageFormat::RGBA; break;
        default:
            m_Format = ImageFormat::None; break;
        }

        m_DataUpdatedAfterGenImTexture = true;
        m_DataUpdatedAfterGenGlTexture = true;

        DeleteGlTexture();
    }


    GLuint Image::GetGlTextureObj()
    {
        if(!HasGlTextureObj() || m_DataUpdatedAfterGenGlTexture){
            UpdateGlTextureObj();
        }
        return m_GlTextureObj;
    }

    ImTexture Image::GetImTexture(ImVec2 size){
        if(!HasImTexture() || m_DataUpdatedAfterGenImTexture){
            UpdateGlTextureObj();
            UpdateImTexture();
        }
        if(size.x != 0 && size.y != 0)
            SetImTextureSize(size);

        return m_ImTexture;
    }

    void Image::UpdateGlTextureObj(){
        if(m_CvMat.empty()) { AIAC_ERROR("Image's cv::Mat is empty!"); return ; }

        GLint glInternalFormat;
        switch(m_Format){
        case ImageFormat::GRAYSCALE:
            glInternalFormat = GL_LUMINANCE; break;
        case ImageFormat::RGB:
            glInternalFormat = GL_RGB; break;
        case ImageFormat::RGBA:
            glInternalFormat = GL_RGBA; break;
        default:
            glInternalFormat = GL_RGB; break;
        }
        CvtCvMat2GlTextureObj(m_CvMat, m_GlTextureObj, glInternalFormat);
        m_DataUpdatedAfterGenGlTexture = false;
    }

    void Image::UpdateImTexture(){
        if(m_CvMat.empty()) { AIAC_ERROR("Image's cv::Mat is empty!"); return ; }
        UpdateGlTextureObj();
        CvtGlTextureObj2ImTexture(m_GlTextureObj, m_ImTexture);
        m_DataUpdatedAfterGenImTexture = false;
    }

    // >>Operator for cv video reading API
    void operator>>(cv::VideoCapture cap, AIAC::Image &img)
    {
        cv::Mat cvImg;
        cap >> cvImg;
        img.UpdateData(cvImg);
    }

    // Utilities functions
    void CvtGlTextureObj2ImTexture(GLuint glTextureObj, ImTexture& imTexture, ImVec2 size)
    {
        imTexture.ID = (void*)(intptr_t)glTextureObj;
        imTexture.Size = size;
    }

    void CvtCvMat2GlTextureObj(cv::Mat& cvMat, GLuint& glTextureObj, GLint glInternalFormat)
    {
        if(cvMat.empty()) { AIAC_ERROR("cvMat empty"); return; }
        else
        {
            if(glTextureObj != 0) { glDeleteTextures(1, &glTextureObj); }
            cv::Mat flippedCvMat;
            cv::flip(cvMat, flippedCvMat, 0);  // OpenGL flip images by default?
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glGenTextures(1, &glTextureObj);
            glBindTexture(GL_TEXTURE_2D, glTextureObj);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         glInternalFormat,
                         flippedCvMat.cols,
                         flippedCvMat.rows,
                         0,
                         glInternalFormat,
                         GL_UNSIGNED_BYTE,
                         flippedCvMat.ptr());
        }
    }

    void CvtCvMat2ImTexture(cv::Mat& cvMat, ImTexture& imTexture, GLuint &glTextureObj, GLint glInternalFormat)
    {
        CvtCvMat2GlTextureObj(cvMat, glTextureObj, glInternalFormat);
        CvtGlTextureObj2ImTexture(glTextureObj, imTexture);
    }
}
```


