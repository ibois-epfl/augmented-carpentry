
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

    void Screenshot::CapturePhoto(){
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();

        std::vector<unsigned char> pixels(width * height * 4);

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        this->GenerateImageName(true);

        if(std::filesystem::exists(this->m_BasePath + this->m_ScreenshotPath)) {
            // Save the image
            cv::imwrite(m_ImageName, image);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_BasePath + this->m_ScreenshotPath);
        }
    }

    void Screenshot::CaptureBuffer() {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetColorCurrentFrame().GetCvMat().copyTo(currentFrame);
        this->GenerateImageName(false);
        if (std::filesystem::exists(this->m_BasePath + this->m_ScreenshotPath)) {
            // Save the image
            cv::imwrite(m_ImageName, currentFrame);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_BasePath + this->m_ScreenshotPath);
        }
    }

    void Screenshot::GenerateImageName(bool isWindow){
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::stringstream imagename;
        if (isWindow) {
            imagename << "window_";
        } else {
            imagename << "color_";
        }
        imagename << std::setfill('0') << std::setw(13) << timestamp << ".png";

        const std::string imagePath = this->m_BasePath + this->m_ScreenshotPath + "/" + imagename.str();
        this->m_ImageName = imagePath;
    }
}
