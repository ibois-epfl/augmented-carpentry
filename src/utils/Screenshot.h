
#pragma once


namespace AIAC::Utils{
    class Screenshot {
    public:
        explicit Screenshot(const std::string& basePath);
        void CapturePhoto();
        void CaptureBuffer();
        void GenerateImageName(bool isWindow);

    private:
        /// Base path of utils
        std::string m_BasePath;
        std::string m_ScreenshotPath = "/screenshots";
        std::string m_ImageName;

    };
}

