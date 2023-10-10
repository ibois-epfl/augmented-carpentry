#include "HoleToolheadAxisExporter.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Application.h"
#include "utils/VideoRecorder.h"

namespace AIAC::Utils {

    HoleToolheadAxisExporter::HoleToolheadAxisExporter(){
        VideoRecorder::CreateFolder(this->m_SaveCoordDefaultPath);
    };

    void HoleToolheadAxisExporter::ExportToolheadAxis(){
        ACToolHeadType activeToolheadType = AC_FF_TOOL->GetType();
        if (activeToolheadType == ACToolHeadType::DRILLBIT){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            // Write toolbase and tooltip to a file
            this->WriteCoordToFile("Toolhead", "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile("Toolhead", "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == ACToolHeadType::CHAINSAW){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            // Write chainbase and normstart to a file
            this->WriteCoordToFile("Toolhead", "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile("Toolhead", "NormStartGO", chainSawData.NormStartGO);
        }
        if (activeToolheadType == ACToolHeadType::CIRCULARSAW){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            // Write center and normstart to a file
            this->WriteCoordToFile("Toolhead", "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToFile("Toolhead", "NormEndGO", circularSawData.NormEndGO);
        }
    }

    void HoleToolheadAxisExporter::ExportHoleAxis(){
        // Get the type of the active hole
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        //TimberInfo::Component
        //#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()

        if (activeHoleType == "HOLE"){
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
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