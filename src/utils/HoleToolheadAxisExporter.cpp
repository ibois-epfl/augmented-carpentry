// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == ACToolHeadType::CHAINSAW){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "NormStartGO", chainSawData.NormStartGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "NormEndGO", chainSawData.NormEndGO);
        }
        if (activeToolheadType == ACToolHeadType::CIRCULARSAW){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToBuffer("Toolhead", AC_FF_TOOL->GetName(), "NormEndGO", circularSawData.NormEndGO);
        }
    }

    void HoleToolheadAxisExporter::ExportHoleAxis(){
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        if (activeHoleType == "HOLE"){
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
            if (hole) {
                std::string currentComponentID = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
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
        AIAC_INFO("[{0},{1},{2},(X:{3},Y:{4},Z:{5})]",itemType, itemName, pointType, goPoint->X(), goPoint->Y(), goPoint->Z());
    }

    void HoleToolheadAxisExporter::WriteBufferToFile(){
        std::string filePath = this->m_BasePath + "/" + this->m_FileName;
        std::ofstream myFile;

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