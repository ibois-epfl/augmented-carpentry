#include "HoleToolheadAxisExporter.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Application.h"

namespace AIAC::Utils {
    void HoleToolheadAxisExporter::ExportToolheadAxis(){
        std::cout << "Getting current toolhead" << std::endl;
        // Get the type of the active toolhead
        std::string activeToolheadType = AC_FF_TOOL->GetTypeString();
        if (activeToolheadType == "DRILLBIT"){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            this->WriteCoordToFile(activeToolheadType, "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile(activeToolheadType, "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == "CHAINSAW"){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            this->WriteCoordToFile(activeToolheadType, "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", chainSawData.NormStartGO);
        }

        if (activeToolheadType == "CIRCULARSAW"){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            this->WriteCoordToFile(activeToolheadType, "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", circularSawData.NormStartGO);
        }
    }

    void HoleToolheadAxisExporter::ExportHoleAxis(){
        std::cout << "Getting current hole" << std::endl;
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        TimberInfo::Component* currentComponent = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent();
        if (activeHoleType == "HOLE"){
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(currentComponent);
            if (hole) {
                WriteCoordToFile(activeHoleType, "StartPoint", hole->GetStartPointGO());
                WriteCoordToFile(activeHoleType, "EndPoint", hole->GetEndPointGO());
            }
        }
    }

    void HoleToolheadAxisExporter::WriteCoordToFile(const std::string& objType, const std::string& pointType, std::shared_ptr<GOPoint> goPoint){
        std::cout << "Writing coordinates to file" << std::endl;
        std::ofstream myfile;
        // append mode
        myfile.open(this->m_SaveToolCoordDefaultPath + "/coordinates.log", std::ios_base::app);
        myfile << objType << "," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        myfile.close();
    }
}