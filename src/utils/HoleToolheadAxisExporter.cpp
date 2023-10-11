#include "HoleToolheadAxisExporter.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Application.h"
#include "utils/VideoRecorder.h"
#include "AIAC/LayerUtils.h"

namespace AIAC::Utils {

    HoleToolheadAxisExporter::HoleToolheadAxisExporter(const std::string& basePath)
    : m_BasePath(basePath)
    {
        LayerUtils::CreateFolder(this->m_BasePath);
    };

    void HoleToolheadAxisExporter::ExportToolheadAxis(){
        ACToolHeadType activeToolheadType = AC_FF_TOOL->GetType();
        if (activeToolheadType == ACToolHeadType::DRILLBIT){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            // Write toolbase and tooltip to a file
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == ACToolHeadType::CHAINSAW){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            // Write chainbase and normstart to a file
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "NormStartGO", chainSawData.NormStartGO);
        }
        if (activeToolheadType == ACToolHeadType::CIRCULARSAW){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            // Write center and normstart to a file
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToFile("Toolhead", AC_FF_TOOL->GetName(), "NormEndGO", circularSawData.NormEndGO);
        }
    }

    void HoleToolheadAxisExporter::ExportHoleAxis(){
        // Get the type of the active hole
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        if (activeHoleType == "HOLE"){
            // checking if the component is a hole
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
            if (hole) {
                std::string currentComponentID = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
                // Write start and end point to a file
                this->WriteCoordToFile(activeHoleType, currentComponentID, "StartPoint", hole->GetStartPointGO());
                this->WriteCoordToFile(activeHoleType, currentComponentID, "EndPoint", hole->GetEndPointGO());
            }
        }
    }

    void HoleToolheadAxisExporter::WriteCoordToFile(const std::string& itemType,
                                                    std::string itemName,
                                                    const std::string& pointType,
                                                    std::shared_ptr<GOPoint> goPoint){
        std::string filePath = this->m_BasePath + "/coordinates.log";
        std::ofstream myFile;
        // Check if file doesn't exist or is empty, and if so, write the header.
        if (!std::filesystem::exists(filePath) || std::filesystem::file_size(filePath) == 0) {
            myFile.open(filePath, std::ios_base::out); // Open in out mode to create/truncate the file.
            myFile << "ItemType,PointType,X,Y,Z\n";
            myFile.close(); // Close and reopen in append mode.
        }
        myFile.open(filePath, std::ios_base::app);
        myFile << itemType << "," << itemName <<" ," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        myFile.close();

        AIAC_INFO("[{0},{1},(X:{2},Y:{3},Z:{4})]",itemType, itemName, pointType, goPoint->X(), goPoint->Y(), goPoint->Z());

    }
}