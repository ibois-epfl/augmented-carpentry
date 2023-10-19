#include "Screenshot.h"
#include "AIAC/Config.h"
#include "../AIAC/Application.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerUtils.h"

namespace AIAC::Utils{
    Screenshot::Screenshot(const std::string& basePath)
            : m_BasePath(basePath)
    {
        LayerUtils::CreateFolder(this->m_BasePath + this->m_ScreenshotPath);
    }

    void Screenshot::CaptureWindow(){
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();

        std::vector<unsigned char> pixels(width * height * 4);

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        this->GenerateImageName(true);
        this->SaveScreenshot(image);
    }

    void Screenshot::CaptureBuffer() {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetColorCurrentFrame().GetCvMat().copyTo(currentFrame);

        this->GenerateImageName(false);
        this->SaveScreenshot(currentFrame);
    }

    void Screenshot::GenerateImageName(bool isWindow){
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::system_clock::to_time_t(now);

        std::stringstream imagename;
        if (isWindow) {
            imagename << "window-";
        } else {
            imagename << "buffer-";
        }
        struct std::tm* tm;
        tm = std::localtime(&timestamp);

        imagename << std::put_time(tm, "%Y-%m-%d-%H-%M-%S") << ".png";

        const std::string imagePath = this->m_BasePath + this->m_ScreenshotPath + "/" + imagename.str();
        this->m_ImageName = imagePath;
    }

    void Screenshot::SaveScreenshot(cv::Mat image){
        if(std::filesystem::exists(this->m_BasePath + this->m_ScreenshotPath)) {
            cv::imwrite(m_ImageName, image);
            AIAC_INFO("The window screenshot is saved to : {0}", m_ImageName);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_BasePath + this->m_ScreenshotPath);
        }
    }
}
