#pragma once

#include "AIAC/GlHeader.h"
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
    
    enum class ImageType
    {
        None = 0,
        CV_MAT,
        GL_TEXTURE_ID,
        IM_TEXTURE
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
        Image(const char* path, ImageType imageType);
        Image(const char* path, ImageType imageType, ImVec2 size);
        ~Image();

        inline bool HasCvMat() { return m_CvMat.empty(); }
        inline bool HasGlTextureID() { return m_GlTextureID != 0; }
        inline bool HasImTexture() { return m_ImTexture.Size.x != 0 || m_ImTexture.Size.y != 0; }

        inline std::string_view GetPath() const { return m_Path; }
        inline cv::Mat GetCvMat() { return m_CvMat; }
        inline GLuint GetGlTextureId() { UpdateGlTextureId(); return m_GlTextureID; }
        inline ImTexture GetImTexture() { if(!HasImTexture()) AIAC_ERROR("Image Class has no ImTexture."); return m_ImTexture; }

        inline void SetImTextureSize(ImVec2 size) { m_ImTexture.Size = size; }

        void UpdateData(cv::Mat cvImg);

        void operator=(cv::Mat cvImg){ UpdateData(cvImg); }

        void CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture);
        void CvtGlTextureID2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size);
        void CvtCvMat2GlTextureID(cv::Mat& cvMat, GLuint& glTextureID);
        void CvtCvMat2ImTexture(cv::Mat& cvMat, ImTexture& imTexture);

        void CvtCvMat2ImTexture();
        void UpdateGlTextureId();

        bool LoadImgFromFile2CvMat(const char* path, cv::Mat& cvMat);
        bool LoadImgFromFile2GlTextureID(const char* path, GLuint& glTextureID);
        bool LoadImgFromFile2ImTexture(const char* path, ImTexture& imTexture);
        bool LoadImgFromFile2ImTexture(const char* path, ImTexture& imTexture, ImVec2 size);
        bool LoadImgFromFile2UImage(const char* path, unsigned char*& m_uImage);

    private:
        const char* m_Path;
        
        cv::Mat m_CvMat = cv::Mat();
        GLuint m_GlTextureID = 0;
        ImTexture m_ImTexture = { 0, ImVec2(0, 0) };
        unsigned char* m_uImage = nullptr;

        uint32_t m_Width = 0, m_Height = 0;
        ImageFormat m_Format = ImageFormat::None;
        size_t m_Size = 0;

    friend void operator>>(cv::VideoCapture cap, AIAC::Image &img);
 
    };

}