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

    void HoleToolheadAxisExporter::ExportCoordinates(){
        this->ExportToolheadAxis();
        this->ExportHoleAxis();
        this->WriteBufferToFile();
    }

    void HoleToolheadAxisExporter::ExportToolheadAxis(){
        ACToolHeadType activeToolheadType = AC_FF_TOOL->GetType();
        if (activeToolheadType == ACToolHeadType::DRILLBIT){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            // Write toolbase and tooltip to a file
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == ACToolHeadType::CHAINSAW){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            // Write chainbase and normstart to a file
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "NormStartGO", chainSawData.NormStartGO);
        }
        if (activeToolheadType == ACToolHeadType::CIRCULARSAW){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            // Write center and normstart to a file
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "NormEndGO", circularSawData.NormEndGO);
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
                this->WriteCoordToBuffer(activeHoleType, currentComponentID, "StartPoint", hole->GetStartPointGO());
                this->WriteCoordToBuffer(activeHoleType, currentComponentID, "EndPoint", hole->GetEndPointGO());
            }
        }
    }


    void HoleToolheadAxisExporter::WriteCoordToBuffer(const std::string& itemType,
                                                    std::string itemName,
                                                    const std::string& pointType,
                                                    std::shared_ptr<GOPoint> goPoint){
        m_Buffer << itemType << "," << itemName <<"," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        AIAC_INFO("[{0},{1},(X:{2},Y:{3},Z:{4})]",itemType, itemName, pointType, goPoint->X(), goPoint->Y(), goPoint->Z());
    }

    void HoleToolheadAxisExporter::WriteBufferToFile(){
        std::string filePath = this->m_BasePath + "/" + this->m_FileName;
        std::ofstream myFile;
        // Check if file doesn't exist or is empty, and if so, write the header.
        if (!std::filesystem::exists(filePath) || std::filesystem::file_size(filePath) == 0) {
            myFile.open(filePath, std::ios_base::out); // Open in out mode to create/truncate the file.
            myFile << "ItemType,PointType,X,Y,Z\n";
            myFile.close(); // Close and reopen in append mode.
        }

        myFile.open(filePath, std::ios_base::app);
        if (myFile.is_open()) {
            myFile << this->GetCurrentTimestamp() << "\n";
            myFile << m_Buffer.str();
            myFile << "\n";
            myFile.close();
        }

        m_Buffer.str("");
        m_Buffer.clear();
    }

    std::string HoleToolheadAxisExporter::GetCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        char buf[100];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
        return buf;
    }
}