#include "aiacpch.h"

#include "AIAC/Image.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

namespace AIAC
{
    Image::Image() {}

    Image::Image(cv::Mat cvImg)
    {
        UpdateData(cvImg);
    }

    Image::Image(AIAC::Image &img)
    {
        UpdateData(img.m_CvMat);
    }

    Image::Image(const char* path, ImageType imageType)
        :m_Path(path)
    {
        switch (imageType)
        {
        case ImageType::CV_MAT:
            LoadImgFromFile2CvMat(path, m_CvMat);
            break;
        case ImageType::GL_TEXTURE_ID:
            LoadImgFromFile2GlTextureID(path, m_GlTextureID);
            break;
        case ImageType::IM_TEXTURE:
            LoadImgFromFile2ImTexture(path, m_ImTexture);
            break;
        default:
            break;
        }
    }

    Image::Image(const char* path, ImageType imageType, ImVec2 size)
        :m_Path(path)
    {
        switch (imageType)
        {
        case ImageType::CV_MAT:
            LoadImgFromFile2CvMat(path, m_CvMat);
            break;
        case ImageType::GL_TEXTURE_ID:
            LoadImgFromFile2GlTextureID(path, m_GlTextureID);
            break;
        case ImageType::IM_TEXTURE:
            LoadImgFromFile2ImTexture(path, m_ImTexture, size);
            break;
        default:
            break;
        }
    }

    Image::~Image() {}
    
    void Image::UpdateData(cv::Mat cvImg)
    {
        m_CvMat = cvImg;
        m_Width = cvImg.rows;
        m_Height = cvImg.cols;
        
        // CvtCvMat2GlTextureID(m_CvMat, m_GlTextureID);
        // CvtGlTextureID2ImTexture(m_GlTextureID, m_ImTexture);

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

    void Image::CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture)
    {
        int w, h;
        glBindTexture(GL_TEXTURE_2D, glTextureID);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
        
        imTexture.ID = (void*)(intptr_t)glTextureID;
        imTexture.Size = ImVec2(w, h);
    }

    void Image::CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size)
    {
        imTexture.ID = (void*)(intptr_t)glTextureID;
        imTexture.Size = size;
    }

    void Image::CvtCvMat2GlTextureID(cv::Mat& cvMat, GLuint& glTextureID)
    {
        if(cvMat.empty()) { AIAC_ERROR("cvMat empty"); return; }
        else
        {   
            // cv::flip(cvMat, cvMat, 0);  // OpenGL flip images by default?
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glGenTextures(1, &glTextureID);
            glBindTexture(GL_TEXTURE_2D, glTextureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            cv::cvtColor(cvMat, cvMat, cv::COLOR_BGR2RGB);

            glTexImage2D(GL_TEXTURE_2D,
                        0,
                        GL_RGB,
                        cvMat.cols,
                        cvMat.rows,
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        cvMat.ptr());
        }
    }
    
    void Image::CvtCvMat2ImTexture()
    {
        if(m_CvMat.empty()) { AIAC_ERROR("cvMat empty"); return ; }
        CvtCvMat2GlTextureID(m_CvMat, m_GlTextureID);
        CvtGlTextureID2ImTexture(m_GlTextureID, m_ImTexture);
    }

    void Image::UpdateGlTextureId()
    {
        if(m_CvMat.empty()) { AIAC_ERROR("cvMat empty"); return ; }
        CvtCvMat2GlTextureID(m_CvMat, m_GlTextureID);
    }

    void Image::CvtCvMat2ImTexture(cv::Mat& cvMat, ImTexture& imTexture)
    {
        CvtCvMat2GlTextureID(cvMat, m_GlTextureID);
        CvtGlTextureID2ImTexture(m_GlTextureID, imTexture);
    }

    bool Image::LoadImgFromFile2CvMat(const char* path, cv::Mat& cvMat)
    {
        cvMat = cv::imread(path, cv::IMREAD_COLOR);
        if (cvMat.empty())
        {
            AIAC_ERROR("Failed to load image from file: {0}", path);
            return EXIT_FAILURE;
        }
        m_CvMat = cvMat;
        return true;
    }

    bool Image::LoadImgFromFile2GlTextureID(const char* path, GLuint& glTextureID) 
    {
        if (FILE *file = fopen(path, "r")) {
            fclose(file);
            AIAC_INFO("File exists");
        } else {
            AIAC_CRITICAL("File does not exist");
            return EXIT_FAILURE;
        }

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);  // OpenGL flip images by default
        unsigned char* image = stbi_load(path, &width, &height, &nrChannels, 0);
        if (image)
        {
            glGenTextures(1, &glTextureID);
            glBindTexture(GL_TEXTURE_2D, glTextureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            AIAC_ERROR("Failed to load img from file");
            return false;
        }
        stbi_image_free(image);
        return true;
    }

    bool Image::LoadImgFromFile2ImTexture(const char* path, ImTexture& imTexture)
    {
        if (LoadImgFromFile2GlTextureID(path, m_GlTextureID))
        {
            CvtGlTextureID2ImTexture(m_GlTextureID, imTexture);
            return true;
        }
        AIAC_ERROR("Failed to load img from file as ImTexture");
        return false;
    }

    unsigned char* Image::LoadImgFromFile2UImage(const char* path)
    {
        int width, height, nrChannels;
        unsigned char* image = stbi_load(path, &width, &height, &nrChannels, 0);
        if (!image) AIAC_ERROR("Failed to load img from file"); return nullptr;
    }
}