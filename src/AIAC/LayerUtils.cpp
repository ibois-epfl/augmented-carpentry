#include <thread>
#include "LayerUtils.h"
#include "Config.h"
#include "Application.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"
#include "utils/Screenshot.h"

namespace AIAC {
    LayerUtils::LayerUtils() {
        LayerUtils::CreateFolder(m_UtilsPath);
    }

    void LayerUtils::OnFrameEnd() {
        if(this->m_Recording){
            this->m_VideoRecorder->CaptureFrames();
        }
        if(this->m_WindowScreenshot){
            std::string savePath = this->GetSaveFolderPath();
            AIAC_INFO("Screenshot of the current window");
            AIAC::Utils::Screenshot recorder(savePath);
            recorder.CaptureWindow();
            this->m_WindowScreenshot = false;
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

    void LayerUtils::TakeWindowScreenshot(){
        this->m_WindowScreenshot = true;
    }

    void LayerUtils::TakeBufferScreenshot(){
        AIAC_INFO("Colored buffer of the current window");
        std::string savePath = this->GetSaveFolderPath();
        AIAC::Utils::Screenshot recorder(savePath);
        recorder.CaptureBuffer();
    }
}

