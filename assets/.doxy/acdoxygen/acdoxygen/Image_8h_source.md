

# File Image.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Image.h**](Image_8h.md)

[Go to the documentation of this file](Image_8h.md)


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
#pragma once

#include <utility>

#include "GlHeader.h"
#include "AIAC/Log.h"

namespace AIAC
{
    enum class ImageFormat
    {
        None = 0,
        RGB,
        RGBA,
        GRAYSCALE
    };

    struct ImTexture
    {
        ImTextureID ID; 
        ImVec2 Size;    
    };

    class Image
    {
    public:
        Image();

        Image(cv::Mat cvImg);

        Image(AIAC::Image &img);

        Image(const char *path, int cvImReadFlag = cv::IMREAD_UNCHANGED);

        ~Image();

        void UpdateData(cv::Mat cvImg);

        void Resize(int newWidth, int newHeight) { cv::resize(m_CvMat, m_CvMat, cv::Size(newWidth, newHeight)); }

        // General Getters

        inline bool HasGlTextureObj() { return m_GlTextureObj != 0; }

        inline bool HasImTexture() { return m_ImTexture.Size.x != 0 || m_ImTexture.Size.y != 0; }

        inline std::string_view GetPath() const { return m_Path; }

        inline int GetWidth() const { return m_CvMat.rows ; }

        inline int GetHeight() const { return m_CvMat.cols; }

        inline const cv::Mat GetCvMat() const { cv::cvtColor(m_CvMat, m_CvMat, cv::COLOR_RGB2BGR); return m_CvMat; }

        inline const cv::Mat GetPureCvMat() const { return m_PureCvMat; }

        // Image Getter of different types and corresponding helpers

        ImTexture GetImTexture(ImVec2 size = ImVec2(0, 0));

        GLuint GetGlTextureObj();

        void UpdateImTexture();

        void UpdateGlTextureObj();

        inline void SetImTextureSize(ImVec2 size) { m_ImTexture.Size = size; }

        inline void DeleteGlTexture() { glDeleteTextures(1, &m_GlTextureObj); m_GlTextureObj = 0;}

        inline void ReplaceCvMat(cv::Mat cvMat) { m_CvMat = cvMat; }

        Image& operator=(cv::Mat cvImg){ UpdateData(std::move(cvImg)); return *this; }

    private:
        const char* m_Path; 
        
        cv::Mat m_CvMat = cv::Mat(); 
        cv::Mat m_PureCvMat = cv::Mat(); 
        GLuint m_GlTextureObj = 0; 
        ImTexture m_ImTexture = { 0, ImVec2(0, 0) }; 

        ImageFormat m_Format = ImageFormat::None; 

        bool m_DataUpdatedAfterGenImTexture, m_DataUpdatedAfterGenGlTexture; 

    friend void operator>>(cv::VideoCapture cap, AIAC::Image &img);
    };

    // Utility functions

    void CvtCvMat2GlTextureObj(cv::Mat& cvMat, GLuint& glTextureObj, GLint glInternalFormat = GL_RGB);

    void CvtGlTextureObj2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size = ImVec2(0, 0));

    void CvtCvMat2ImTexture(cv::Mat& cvMat, ImTexture& imTexture, GLuint &glTextureObj, GLint glInternalFormat);

}
```


