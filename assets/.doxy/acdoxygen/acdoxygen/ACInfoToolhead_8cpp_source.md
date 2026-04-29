

# File ACInfoToolhead.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**ACInfoToolhead.cpp**](ACInfoToolhead_8cpp.md)

[Go to the documentation of this file](ACInfoToolhead_8cpp.md)


```C++
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
#include "ACInfoToolhead.h"
#include "AIAC/Log.h"
#include "GeometryUtils.h"

#include "pugixml.hpp"

namespace AIAC
{
    void ToolHeadData::LoadACIT(std::string acitPath)
    {
        AIAC_INFO("Loading ACIT from {0}", acitPath);
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(acitPath.c_str());
        if (!result) { AIAC_ERROR("Could not load ACIT from {0}", acitPath); return; }

        pugi::xml_node root = doc.child("acit");
        pugi::xml_node toolhead = root.child("toolhead");

        std::string type = toolhead.attribute("type").as_string();
        if (type == "drillbit")
        {
            m_Type = ACToolHeadType::DRILLBIT;
            m_Name = toolhead.attribute("name").as_string();

            m_DrillBitD.ToolbaseACIT = ParseString2GlmVector(toolhead.child("toolbase").child_value()) * this->GetScaleF();
            m_DrillBitD.TooltipACIT = ParseString2GlmVector(toolhead.child("tooltip").child_value()) * this->GetScaleF();
            m_DrillBitD.EattipACIT = ParseString2GlmVector(toolhead.child("eattip").child_value()) * this->GetScaleF();
            m_DrillBitD.ChucktipACIT = ParseString2GlmVector(toolhead.child("chucktip").child_value()) * this->GetScaleF();
            m_DrillBitD.RadiusACIT = toolhead.child("radius").text().as_float() * this->GetScaleF();
        }
        else if (type == "circularsaw")
        {
            m_Type = ACToolHeadType::CIRCULARSAW;
            m_Name = toolhead.attribute("name").as_string();
            m_CircularSawD.CenterACIT = ParseString2GlmVector(toolhead.child("center").child_value()) * this->GetScaleF();

            m_CircularSawD.NormStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_CircularSawD.NormEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_CircularSawD.RadiusACIT = toolhead.child("radius").text().as_float() * this->GetScaleF();
            m_CircularSawD.ThicknessACIT = toolhead.child("bladeThickness").text().as_float() * this->GetScaleF();
            m_CircularSawD.OverhangACIT = toolhead.child("bladeOverhang").text().as_float() * this->GetScaleF();
        }
        else if (type == "chainsaw")
        {
            m_Type = ACToolHeadType::CHAINSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_ChainSawD.ChainBaseACIT = ParseString2GlmVector(toolhead.child("chainbase").child_value()) * this->GetScaleF();
            m_ChainSawD.ChainMidACIT = ParseString2GlmVector(toolhead.child("chainmid").child_value()) * this->GetScaleF();
            m_ChainSawD.ChainNormEndACIT = ParseString2GlmVector(toolhead.child("chainend").child_value()) * this->GetScaleF();
            m_ChainSawD.NormStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_ChainSawD.NormEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_ChainSawD.WidthACIT = toolhead.child("width").text().as_float() * this->GetScaleF();
            m_ChainSawD.ThicknessACIT = toolhead.child("bladeThickness").text().as_float() * this->GetScaleF();
            m_ChainSawD.OverhangACIT = toolhead.child("bladeOverhang").text().as_float() * this->GetScaleF();
        }
        else if (type == "sabersaw")
        {
            m_Type = ACToolHeadType::SABERSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_SaberSawD.ToolbaseACIT = ParseString2GlmVector(toolhead.child("toolbase").child_value()) * this->GetScaleF();
            m_SaberSawD.TooltipACIT = ParseString2GlmVector(toolhead.child("tooltip").child_value()) * this->GetScaleF();
            m_SaberSawD.NormStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_SaberSawD.NormEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
        }
        else { AIAC_ERROR("Toolhead type {0} not supported", type); }
        return;
    }

    glm::vec3 ToolHeadData::ParseString2GlmVector(std::string str)
    {
        glm::vec3 vec;
        auto ss = std::stringstream(str);
        ss >> vec.x >> vec.y >> vec.z;
        return vec;
    }

    ACInfoToolhead::ACInfoToolhead(std::string acitPath, std::string objPath, int id)
        : m_ACITPath(acitPath), m_OBJPath(objPath), m_ID(id)
    {
        this->m_Data.LoadACIT(acitPath);
        this->AddGOsInfo(this->m_Data);
        this->m_GOPrimitivesInfoOriginal.clear();
        this->CopyGOsInfoOriginal();
        this->TransformSync();
        this->SetVisibility(true);
    }

    void ACInfoToolhead::AddGOsInfo(ToolHeadData& data)
    {
        switch (data.m_Type)
        {
            case ACToolHeadType::DRILLBIT:
                this->AddGOsInfoDrillBit(data);
                break;
            case ACToolHeadType::CIRCULARSAW:
                this->AddGOsInfoCircularSaw(data);
                break;
            case ACToolHeadType::CHAINSAW:
                this->AddGOsInfoChainSaw(data);
                break;
            case ACToolHeadType::SABERSAW:
                this->AddGOsInfoSaberSaw(data);
                break;
            default:
                AIAC_ERROR("Toolhead type not supported");
                break;
        }
        return;
    }

    void ACInfoToolhead::AddGOsInfoDrillBit(ToolHeadData& data)
    {
        data.m_DrillBitD.ToolbaseGO = GOPoint::Add(data.m_DrillBitD.ToolbaseACIT.x,
                                       data.m_DrillBitD.ToolbaseACIT.y,
                                       data.m_DrillBitD.ToolbaseACIT.z,
                                       GOWeight::Thick);
        data.m_DrillBitD.ToolbaseGO->SetColor(GOColor::RED);
        data.m_DrillBitD.TooltipGO = GOPoint::Add(data.m_DrillBitD.TooltipACIT.x, 
                                      data.m_DrillBitD.TooltipACIT.y,
                                      data.m_DrillBitD.TooltipACIT.z,
                                      GOWeight::Thick);
        data.m_DrillBitD.TooltipGO->SetColor(GOColor::GREEN);
        data.m_DrillBitD.EattipGO = GOPoint::Add(data.m_DrillBitD.EattipACIT.x,
                                     data.m_DrillBitD.EattipACIT.y,
                                     data.m_DrillBitD.EattipACIT.z,
                                     GOWeight::Thick);
        data.m_DrillBitD.EattipGO->SetColor(GOColor::BLUE);
        data.m_DrillBitD.ChucktipGO = GOPoint::Add(data.m_DrillBitD.ChucktipACIT.x,
                                       data.m_DrillBitD.ChucktipACIT.y,
                                       data.m_DrillBitD.ChucktipACIT.z,
                                       GOWeight::Thick);
        data.m_DrillBitD.ChucktipGO->SetColor(GOColor::YELLOW);

        auto lnAxis = GOLine::Add(*data.m_DrillBitD.ToolbaseGO, *data.m_DrillBitD.TooltipGO);
        lnAxis->SetColor(GOColor::MAGENTA);

        lnAxis->SetVisibility(false);

        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.ToolbaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.TooltipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.EattipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.ChucktipGO);
        this->m_GOPrimitivesInfo.push_back(lnAxis);

        for (auto& go : this->m_GOPrimitivesInfo)
            go->SetVisibility(false);
    }
    void ACInfoToolhead::AddGOsInfoCircularSaw(ToolHeadData& data)
    {
        data.m_CircularSawD.CenterGO = GOPoint::Add(data.m_CircularSawD.CenterACIT.x,
                                         data.m_CircularSawD.CenterACIT.y,
                                         data.m_CircularSawD.CenterACIT.z,
                                         GOWeight::Thick);
        data.m_CircularSawD.CenterGO->SetColor(GOColor::RED);
        data.m_CircularSawD.NormEndGO = GOPoint::Add(data.m_CircularSawD.NormEndACIT.x,
                                                 data.m_CircularSawD.NormEndACIT.y,
                                                 data.m_CircularSawD.NormEndACIT.z,
                                                 GOWeight::Thick);
        data.m_CircularSawD.NormEndGO->SetColor(GOColor::GREEN);
        auto lnNormal = GOLine::Add(*data.m_CircularSawD.CenterGO, *data.m_CircularSawD.NormEndGO);
        lnNormal->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_CircularSawD.CenterGO);
        this->m_GOPrimitivesInfo.push_back(data.m_CircularSawD.NormEndGO);
        this->m_GOPrimitivesInfo.push_back(lnNormal);

        for (auto& go : this->m_GOPrimitivesInfo)
            go->SetVisibility(false);
    }
    void ACInfoToolhead::AddGOsInfoChainSaw(ToolHeadData& data)
    {
        data.m_ChainSawD.ChainBaseGO = GOPoint::Add(data.m_ChainSawD.ChainBaseACIT.x,
                                        data.m_ChainSawD.ChainBaseACIT.y,
                                        data.m_ChainSawD.ChainBaseACIT.z,
                                        GOWeight::Thick);
        data.m_ChainSawD.ChainBaseGO->SetColor(GOColor::RED);
        data.m_ChainSawD.ChainMidGO = GOPoint::Add(data.m_ChainSawD.ChainMidACIT.x,
                                                   data.m_ChainSawD.ChainMidACIT.y,
                                                   data.m_ChainSawD.ChainMidACIT.z,
                                                   GOWeight::Thick);
        data.m_ChainSawD.ChainMidGO->SetColor(GOColor::GREEN);
        data.m_ChainSawD.ChainEndGO = GOPoint::Add(data.m_ChainSawD.ChainNormEndACIT.x,
                                       data.m_ChainSawD.ChainNormEndACIT.y,
                                       data.m_ChainSawD.ChainNormEndACIT.z,
                                       GOWeight::Thick);
        data.m_ChainSawD.ChainEndGO->SetColor(GOColor::BLUE);
        data.m_ChainSawD.NormStartGO = GOPoint::Add(data.m_ChainSawD.NormStartACIT.x,
                                                data.m_ChainSawD.NormStartACIT.y,
                                                data.m_ChainSawD.NormStartACIT.z,
                                                GOWeight::Thick);
        data.m_ChainSawD.NormStartGO->SetColor(GOColor::YELLOW);
        data.m_ChainSawD.NormEndGO = GOPoint::Add(data.m_ChainSawD.NormEndACIT.x,
                                              data.m_ChainSawD.NormEndACIT.y,
                                              data.m_ChainSawD.NormEndACIT.z,
                                              GOWeight::Thick);
        data.m_ChainSawD.NormEndGO->SetColor(GOColor::CYAN);
        auto lnBaseMid = GOLine::Add(*data.m_ChainSawD.ChainBaseGO, *data.m_ChainSawD.ChainMidGO);
        lnBaseMid->SetColor(GOColor::MAGENTA);
        auto lnMidEnd = GOLine::Add(*data.m_ChainSawD.ChainMidGO, *data.m_ChainSawD.ChainEndGO);
        lnMidEnd->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainBaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainMidGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainEndGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.NormStartGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.NormEndGO);
        this->m_GOPrimitivesInfo.push_back(lnBaseMid);
        this->m_GOPrimitivesInfo.push_back(lnMidEnd);

        for (auto& go : this->m_GOPrimitivesInfo)
            go->SetVisibility(false);
    }
    void ACInfoToolhead::AddGOsInfoSaberSaw(ToolHeadData& data)
    {
        data.m_SaberSawD.ToolbaseGO = GOPoint::Add(data.m_SaberSawD.ToolbaseACIT.x,
                                       data.m_SaberSawD.ToolbaseACIT.y,
                                       data.m_SaberSawD.ToolbaseACIT.z,
                                       GOWeight::Thick);
        data.m_SaberSawD.ToolbaseGO->SetColor(GOColor::RED);
        data.m_SaberSawD.TooltipGO = GOPoint::Add(data.m_SaberSawD.TooltipACIT.x,
                                      data.m_SaberSawD.TooltipACIT.y,
                                      data.m_SaberSawD.TooltipACIT.z,
                                      GOWeight::Thick);
        data.m_SaberSawD.TooltipGO->SetColor(GOColor::GREEN);
        data.m_SaberSawD.NormStartGO = GOPoint::Add(data.m_SaberSawD.NormStartACIT.x,
                                                data.m_SaberSawD.NormStartACIT.y,
                                                data.m_SaberSawD.NormStartACIT.z,
                                                GOWeight::Thick);
        data.m_SaberSawD.NormStartGO->SetColor(GOColor::BLUE);
        data.m_SaberSawD.NormEndGO = GOPoint::Add(data.m_SaberSawD.NormEndACIT.x,
                                              data.m_SaberSawD.NormEndACIT.y,
                                              data.m_SaberSawD.NormEndACIT.z,
                                              GOWeight::Thick);
        data.m_SaberSawD.NormEndGO->SetColor(GOColor::YELLOW);
        auto lineAxis = GOLine::Add(*data.m_SaberSawD.ToolbaseGO, *data.m_SaberSawD.TooltipGO);
        lineAxis->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.ToolbaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.TooltipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.NormStartGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.NormEndGO);
        this->m_GOPrimitivesInfo.push_back(lineAxis);

        for (auto& go : this->m_GOPrimitivesInfo)
            go->SetVisibility(false);
    }

    void ACInfoToolhead::SetVisibility(bool visible)
    {
        for (auto& go : m_GOPrimitivesInfo)
            go->SetVisibility(visible);
    }

    void ACInfoToolhead::Transform(glm::mat4 transform)
    {
        for (uint i = 0; i < this->m_GOPrimitivesInfo.size(); i++)
            this->TransformGO(this->m_GOPrimitivesInfo[i], this->m_GOPrimitivesInfoOriginal[i], transform);
    }
    void ACInfoToolhead::TransformGO(std::shared_ptr<GOPrimitive> goPtr,
                                     std::shared_ptr<GOPrimitive> goOriginalPtr,
                                     glm::mat4 transform)
    {
        switch (goPtr->GetType())
        {
            case _GOPoint:
            {
                std::shared_ptr<GOPoint> go = std::dynamic_pointer_cast<GOPoint>(goOriginalPtr);
                std::shared_ptr<GOPoint> goCopied = std::make_shared<GOPoint>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOLine:
            {
                std::shared_ptr<GOLine> go = std::dynamic_pointer_cast<GOLine>(goOriginalPtr);
                std::shared_ptr<GOLine> goCopied = std::make_shared<GOLine>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOCircle:
            {
                std::shared_ptr<GOCircle> go = std::dynamic_pointer_cast<GOCircle>(goOriginalPtr);
                std::shared_ptr<GOCircle> goCopied = std::make_shared<GOCircle>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOCylinder:
            {
                std::shared_ptr<GOCylinder> go = std::dynamic_pointer_cast<GOCylinder>(goOriginalPtr);
                std::shared_ptr<GOCylinder> goCopied = std::make_shared<GOCylinder>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOPolyline:
            {
                std::shared_ptr<GOPolyline> go = std::dynamic_pointer_cast<GOPolyline>(goOriginalPtr);
                std::shared_ptr<GOPolyline> goCopied = std::make_shared<GOPolyline>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOTriangle:
            {
                std::shared_ptr<GOTriangle> go = std::dynamic_pointer_cast<GOTriangle>(goOriginalPtr);
                std::shared_ptr<GOTriangle> goCopied = std::make_shared<GOTriangle>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOMesh:
            {
                std::shared_ptr<GOMesh> go = std::dynamic_pointer_cast<GOMesh>(goOriginalPtr);
                std::shared_ptr<GOMesh> goCopied = std::make_shared<GOMesh>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            case _GOText:
            {
                std::shared_ptr<GOText> go = std::dynamic_pointer_cast<GOText>(goOriginalPtr);
                std::shared_ptr<GOText> goCopied = std::make_shared<GOText>(*go);
                goCopied->Transform(transform);
                goPtr->SetValueFrom(goCopied);
                break;
            }
            default:
                break;
        }
    }

    void ACInfoToolhead::TransformSync()
    {
        // Derive the bounding boxes of the info
        glm::vec3 lbn = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
        glm::vec3 rtf = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

        // Getting the bounding box of the info
        // Here, we filter in only the points
        for (auto& go : this->m_GOPrimitivesInfoOriginal)
        {
            if (go->GetType() != _GOPoint)
                continue;
            std::shared_ptr<GOPoint> goPoint = std::dynamic_pointer_cast<GOPoint>(go);
            glm::vec3 position = goPoint->GetPosition();
            lbn.x = std::min(lbn.x, position.x);
            lbn.y = std::min(lbn.y, position.y);
            lbn.z = std::min(lbn.z, position.z);
            rtf.x = std::max(rtf.x, position.x);
            rtf.y = std::max(rtf.y, position.y);
            rtf.z = std::max(rtf.z, position.z);
        }

        glm::vec3 center = (lbn + rtf) / 2.0f;

        glm::mat4x4 transformToCenter, transformBackFromCenter;
        transformToCenter = GetTranslationMatrix(-center);
        transformBackFromCenter = GetTranslationMatrix(center);

        glm::mat4x4 rotation = glm::mat4x4(GetRotationMatrix(glm::vec3(1, 0, 0), 90.0f * M_PI / 180.0f));

        for (auto& go : this->m_GOPrimitivesInfoOriginal)
            go->Transform(transformBackFromCenter * rotation * transformToCenter);
    }

    void ACInfoToolhead::CopyGOsInfoOriginal()
    {
        for (const auto& go : this->m_GOPrimitivesInfo) 
        {
            switch (go->GetType())
            {
            case _GOPoint:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOPoint>(*std::dynamic_pointer_cast<GOPoint>(go))); 
                break;
            case _GOLine:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOLine>(*std::dynamic_pointer_cast<GOLine>(go))); 
                break;
            case _GOCircle:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOCircle>(*std::dynamic_pointer_cast<GOCircle>(go))); 
                break;
            case _GOCylinder:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOCylinder>(*std::dynamic_pointer_cast<GOCylinder>(go))); 
                break;
            case _GOPolyline:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOPolyline>(*std::dynamic_pointer_cast<GOPolyline>(go))); 
                break;
            case _GOTriangle:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOTriangle>(*std::dynamic_pointer_cast<GOTriangle>(go))); 
                break;
            case _GOMesh:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOMesh>(*std::dynamic_pointer_cast<GOMesh>(go))); 
                break;
            case _GOText:
                this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOText>(*std::dynamic_pointer_cast<GOText>(go)));
                break;
            default:
                break;
            }
        }
    }
}
```


