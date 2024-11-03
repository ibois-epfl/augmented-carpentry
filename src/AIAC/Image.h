#pragma once

#include <utility>

#include "GlHeader.h"
#include "AIAC/Log.h"

namespace AIAC
{
    /**
     * @enum ImageFormat
     * @brief Enum representing different image formats.
     */
    enum class ImageFormat
    {
        None = 0,
        RGB,
        RGBA,
        GRAYSCALE
    };

    /**
     * @struct ImTexture
     * @brief Structure representing an ImGui texture.
     */
    struct ImTexture
    {
        ImTextureID ID; ///< Texture ID
        ImVec2 Size;    ///< Size of the texture
    };

    /**
     * @class Image
     * @brief Class representing the main iamge object for AC.
     */
    class Image
    {
    public:
        /**
         * @brief Default constructor.
         */
        Image();

        /**
         * @brief Constructor with OpenCV matrix.
         * @param cvImg OpenCV matrix representing the image.
         */
        Image(cv::Mat cvImg);

        /**
         * @brief Copy constructor.
         * @param img Reference to another AIAC::Image object.
         */
        Image(AIAC::Image &img);

        /**
         * @brief Constructor with file path.
         * @param path Path to the image file.
         * @param cvImReadFlag Flag for OpenCV image reading.
         */
        Image(const char *path, int cvImReadFlag = cv::IMREAD_UNCHANGED);

        /**
         * @brief Destructor.
         */
        ~Image();

        /**
         * @brief Update image data with a new OpenCV matrix.
         * @param cvImg OpenCV matrix representing the new image data.
         */
        void UpdateData(cv::Mat cvImg);

        /**
         * @brief Resize the image.
         * @param newWidth New width of the image.
         * @param newHeight New height of the image.
         */
        void Resize(int newWidth, int newHeight) { cv::resize(m_CvMat, m_CvMat, cv::Size(newWidth, newHeight)); }

        // General Getters

        /**
         * @brief Check if the image has a valid OpenGL texture object.
         * @return True if the image has a valid OpenGL texture object, false otherwise.
         */
        inline bool HasGlTextureObj() { return m_GlTextureObj != 0; }

        /**
         * @brief Check if the image has a valid ImGui texture.
         * @return True if the image has a valid ImGui texture, false otherwise.
         */
        inline bool HasImTexture() { return m_ImTexture.Size.x != 0 || m_ImTexture.Size.y != 0; }

        /**
         * @brief Get the file path of the image.
         * @return File path of the image.
         */
        inline std::string_view GetPath() const { return m_Path; }

        /**
         * @brief Get the width of the image.
         * @return Width of the image.
         */
        inline int GetWidth() const { return m_CvMat.rows ; }

        /**
         * @brief Get the height of the image.
         * @return Height of the image.
         */
        inline int GetHeight() const { return m_CvMat.cols; }

        /**
         * @brief Get the OpenCV matrix of the image.
         * @return OpenCV matrix of the image.
         */
        inline const cv::Mat GetCvMat() const { cv::cvtColor(m_CvMat, m_CvMat, cv::COLOR_RGB2BGR); return m_CvMat; }

        /**
         * @brief Get the pure OpenCV matrix of the image (BGR format).
         * @return Pure OpenCV matrix of the image.
         */
        inline const cv::Mat GetPureCvMat() const { return m_PureCvMat; }

        // Image Getter of different types and corresponding helpers

        /**
         * @brief Get the ImGui texture of the image.
         * @param size Size of the texture.
         * @return ImGui texture of the image.
         */
        ImTexture GetImTexture(ImVec2 size = ImVec2(0, 0));

        /**
         * @brief Get the OpenGL texture object of the image.
         * @return OpenGL texture object of the image.
         */
        GLuint GetGlTextureObj();

        /**
         * @brief Update the ImGui texture of the image.
         */
        void UpdateImTexture();

        /**
         * @brief Update the OpenGL texture object of the image.
         */
        void UpdateGlTextureObj();

        /**
         * @brief Set the size of the ImGui texture.
         * @param size Size of the texture.
         */
        inline void SetImTextureSize(ImVec2 size) { m_ImTexture.Size = size; }

        /**
         * @brief Delete the OpenGL texture object.
         */
        inline void DeleteGlTexture() { glDeleteTextures(1, &m_GlTextureObj); m_GlTextureObj = 0;}

        /**
         * @brief Replace the OpenCV matrix of the image.
         * @param cvMat New OpenCV matrix.
         */
        inline void ReplaceCvMat(cv::Mat cvMat) { m_CvMat = cvMat; }

        /**
         * @brief Assignment operator for OpenCV matrix.
         * @param cvImg OpenCV matrix representing the new image data.
         * @return Reference to the updated image object.
         */
        Image& operator=(cv::Mat cvImg){ UpdateData(std::move(cvImg)); return *this; }

    private:
        const char* m_Path; ///< File path of the image
        
        cv::Mat m_CvMat = cv::Mat(); ///< OpenCV matrix representing the image
        cv::Mat m_PureCvMat = cv::Mat(); ///< Pure OpenCV matrix (BGR format)
        GLuint m_GlTextureObj = 0; ///< OpenGL texture object
        ImTexture m_ImTexture = { 0, ImVec2(0, 0) }; ///< ImGui texture

        ImageFormat m_Format = ImageFormat::None; ///< Format of the image

        bool m_DataUpdatedAfterGenImTexture, m_DataUpdatedAfterGenGlTexture; ///< Flags indicating if data was updated after generating textures

    friend void operator>>(cv::VideoCapture cap, AIAC::Image &img);
    };

    // Utility functions

    /**
     * @brief Convert OpenCV matrix to OpenGL texture object.
     * @param cvMat OpenCV matrix.
     * @param glTextureObj OpenGL texture object.
     * @param glInternalFormat Internal format of the OpenGL texture.
     */
    void CvtCvMat2GlTextureObj(cv::Mat& cvMat, GLuint& glTextureObj, GLint glInternalFormat = GL_RGB);

    /**
     * @brief Convert OpenGL texture object to ImGui texture.
     * @param glTextureID OpenGL texture ID.
     * @param imTexture ImGui texture.
     * @param size Size of the texture.
     */
    void CvtGlTextureObj2ImTexture(GLuint glTextureID, ImTexture& imTexture, ImVec2 size = ImVec2(0, 0));

    /**
     * @brief Convert OpenCV matrix to ImGui texture.
     * @param cvMat OpenCV matrix.
     * @param imTexture ImGui texture.
     * @param glTextureObj OpenGL texture object.
     * @param glInternalFormat Internal format of the OpenGL texture.
     */
    void CvtCvMat2ImTexture(cv::Mat& cvMat, ImTexture& imTexture, GLuint &glTextureObj, GLint glInternalFormat);

}