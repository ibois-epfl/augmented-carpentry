#include "HoleToolheadAxisExporter.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Application.h"
#include "utils/VideoRecorder.h"

namespace AIAC::Utils {

    HoleToolheadAxisExporter::HoleToolheadAxisExporter(){
        VideoRecorder::CreateFolder(this->m_SaveCoordDefaultPath);
    };

    void HoleToolheadAxisExporter::ExportToolheadAxis(){
        // Get the type of the active toolhead
        std::string activeToolheadType = AC_FF_TOOL->GetTypeString();
        if (activeToolheadType == "DRILLBIT"){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            // Write toolbase and tooltip to a file
            this->WriteCoordToFile(activeToolheadType, "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile(activeToolheadType, "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == "CHAINSAW"){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            // Write chainbase and normstart to a file
            this->WriteCoordToFile(activeToolheadType, "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", chainSawData.NormStartGO);
        }
        if (activeToolheadType == "CIRCULARSAW"){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            // Write center and normstart to a file
            this->WriteCoordToFile(activeToolheadType, "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", circularSawData.NormStartGO);
        }
    }

    void HoleToolheadAxisExporter::ExportHoleAxis(){
        // Get the type of the active hole
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        TimberInfo::Component* currentComponent = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent();
        if (activeHoleType == "HOLE"){
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(currentComponent);
            if (hole) {
                // Write start and end point to a file
                this->WriteCoordToFile(activeHoleType, "StartPoint", hole->GetStartPointGO());
                this->WriteCoordToFile(activeHoleType, "EndPoint", hole->GetEndPointGO());
            }
        }
    }

    void HoleToolheadAxisExporter::WriteCoordToFile(const std::string& itemType, const std::string& pointType, std::shared_ptr<GOPoint> goPoint){
        std::string filePath = this->m_SaveCoordDefaultPath + "/coordinates.log";
        std::ofstream myFile;
        // Check if file doesn't exist or is empty, and if so, write the header.
        if (!std::filesystem::exists(filePath) || std::filesystem::file_size(filePath) == 0) {
            myFile.open(filePath, std::ios_base::out); // Open in out mode to create/truncate the file.
            myFile << "ItemType,PointType,X,Y,Z\n";
            myFile.close(); // Close and reopen in append mode.
        }
        myFile.open(filePath, std::ios_base::app);
        myFile << itemType << "," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        myFile.close();
    }
}