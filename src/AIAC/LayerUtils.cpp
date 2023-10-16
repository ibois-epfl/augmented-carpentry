#include <thread>
#include "LayerUtils.h"
#include "Config.h"
#include "Application.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"
#include "AIAC/Camera.h"
#include "LayerCameraCalib.h"


namespace AIAC {
    LayerUtils::LayerUtils() {
        LayerUtils::CreateFolder(m_UtilsPath);
    }
    void LayerUtils::OnFrameEnd() {
        if(this->m_Recording){
            this->m_VideoRecorder->CaptureFrames();
        }
    }

    void LayerUtils::StartRecording(){
        AIAC_INFO("Started Recording");
        this->m_Recording = true;
        std::string savePath = this->GetSaveFolderPath();
        this->m_VideoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>(savePath);
    }

    void LayerUtils::StopRecording(){
        AIAC_INFO("Stopped Recording");
        this->m_Recording = false;
        std::thread([this]{
            this->m_Processing = true;
            this->m_VideoRecorder->MakeVideoFromFrames();
            this->m_VideoRecorder.reset();
            this->m_Processing = false;
        }).detach();
    }

    void LayerUtils::SetSaveFolderPath(const std::string& path){
        if(path.empty()) {
            AIAC_INFO("Using default path: {}", m_UtilsPath);
        } else {
            m_UtilsPath = path;
            AIAC_INFO("Using specified path: {}", m_UtilsPath);
        }
    }

    void LayerUtils::ExportHoleToolheadAxis(){
        AIAC_INFO("Hole and toolhead axis export");
        std::string savePath = this->GetSaveFolderPath();
        this->m_HoleToolheadAxisExporter = std::make_unique<AIAC::Utils::HoleToolheadAxisExporter>(savePath);
        this->m_HoleToolheadAxisExporter->ExportCoordinates();
    }

    bool LayerUtils::CreateFolder(const std::string& path) {
        if(std::filesystem::exists(path)) {
            AIAC_INFO("{0} folder already exists!", path);
            return true;
        }
        if(std::filesystem::create_directories(path)) {
            AIAC_INFO("Created {0} folder", path);
            return true;
        } else {
            AIAC_ERROR("Failed to create {0} folder", path);
            return false;
        }
    }

    void LayerUtils::CapturePhoto(std::string& savePath){
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();

        std::vector<unsigned char> pixels(width * height * 4);

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        if(std::filesystem::exists(savePath)) {
            // Save the image
            cv::imwrite(savePath + "/output.png", image);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", savePath);
        }
    }

    void LayerUtils::CaptureBuffer(std::string &savePath) {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCalibratedCurrentFrame().GetCvMat().copyTo(currentFrame);
        if(std::filesystem::exists(savePath)) {
            // Save the image
            cv::imwrite(savePath + "/output.png", currentFrame);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", savePath);
        }
    }

    void LayerUtils::TakeWindowScreenshot(){
        AIAC_INFO("Screenshot of the current window");
        std::string savePath = this->GetSaveFolderPath();
        this->CapturePhoto(savePath);
    }

    void LayerUtils::TakeBufferScreenshot(){
        AIAC_INFO("Colored buffer of the current window");
        std::string savePath = this->GetSaveFolderPath();
        this->CaptureBuffer(savePath);
    }
}

