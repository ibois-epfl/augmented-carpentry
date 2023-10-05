#include <thread>
#include "LayerUtils.h"
#include "Config.h"
#include "Application.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"


namespace AIAC {
    void LayerUtils::OnFrameEnd() {
        // check if the recording flag is set to true
        if(this->m_Recording){
            // capture the frames
            this->m_VideoRecorder->CaptureFrames();
        }
    }

    void LayerUtils::StartRecording(){
        AIAC_INFO("Started Recording");
        // set the recording flag to true
        this->m_Recording = true;
        // get the save path
        std::string savePath = this->GetSaveFolderPath();
        // create the video recorder object
        this->m_VideoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>(savePath);
    };

    void LayerUtils::StopRecording(){
        AIAC_INFO("Stopped Recording");
        // set the recording flag to false
        this->m_Recording = false;
        // create the video from the frames in a separate thread
        std::thread([this]{
            this->m_Processing = true;
            this->m_VideoRecorder->MakeVideoFromFrames();
            // delete the frames folder and video recorder object
            this->m_VideoRecorder.reset();
            this->m_Processing = false;
        }).detach();
    };

    void LayerUtils::SetSaveFolderPath(std::string path){
        // Set the save folder path for the video recorder
        if(path.empty()) {
            AIAC_INFO("Using default path: {}", m_SaveFolderPath);
        } else {
            m_SaveFolderPath = path;
            AIAC_INFO("Using specified path: {}", m_SaveFolderPath);
        }
    };

    void LayerUtils::OnFrameStart(){
        // check if the exporting flag is set to true
        if(this->m_HoleToolheadExporting){
            // export the hole and toolhead coordinates
            this->m_HoleToolheadAxisExporter->ExportToolheadAxis();
            this->m_HoleToolheadAxisExporter->ExportHoleAxis();
        }
    }

    void LayerUtils::StartHoleToolheadAxisExport(){
        // set the exporting flag to true
        this->m_HoleToolheadExporting = true;
        // create the exporter object
        this->m_HoleToolheadAxisExporter = std::make_unique<AIAC::Utils::HoleToolheadAxisExporter>();
    };

    void LayerUtils::StopHoleToolheadAxisExport(){
        AIAC_INFO("Stopped Recording");
        // set the exporting flag to false
        this->m_HoleToolheadExporting = false;
    };
}

