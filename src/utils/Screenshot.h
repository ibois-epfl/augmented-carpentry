
#pragma once

namespace AIAC::Utils{
    class Screenshot {
    public:
        explicit Screenshot(const std::string& basePath);
        /// @brief Capture pixels of the current window
        void CapturePhoto();
        /// @brief Capture current buffer (color)
        void CaptureBuffer();
        /// @brief Generate the name of the image
        void GenerateImageName(bool isWindow);

    private:
        /// Base path of utils
        std::string m_BasePath;
        /// Save path for screenshots
        std::string m_ScreenshotPath = "/screenshots";
        /// Name of the image
        std::string m_ImageName;
    };
}

