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

            m_CircularSawD.NormalStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_CircularSawD.NormalEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_CircularSawD.RadiusACIT = toolhead.child("radius").text().as_float() * this->GetScaleF();
        }
        else if (type == "chainsaw")
        {
            m_Type = ACToolHeadType::CHAINSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_ChainSawD.ChainbaseACIT = ParseString2GlmVector(toolhead.child("chainbase").child_value()) * this->GetScaleF();
            m_ChainSawD.ChainmidACIT = ParseString2GlmVector(toolhead.child("chainmid").child_value()) * this->GetScaleF();
            m_ChainSawD.ChainendACIT = ParseString2GlmVector(toolhead.child("chainend").child_value()) * this->GetScaleF();
            m_ChainSawD.NormalStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_ChainSawD.NormalEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_ChainSawD.WidthACIT = toolhead.child("width").text().as_float() * this->GetScaleF();
        }
        else if (type == "sabersaw")
        {
            m_Type = ACToolHeadType::SABERSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_SaberSawD.ToolbaseACIT = ParseString2GlmVector(toolhead.child("toolbase").child_value()) * this->GetScaleF();
            m_SaberSawD.TooltipACIT = ParseString2GlmVector(toolhead.child("tooltip").child_value()) * this->GetScaleF();
            m_SaberSawD.NormalStartACIT = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_SaberSawD.NormalEndACIT = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
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

        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.ToolbaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.TooltipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.EattipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_DrillBitD.ChucktipGO);
        this->m_GOPrimitivesInfo.push_back(lnAxis);
    }
    void ACInfoToolhead::AddGOsInfoCircularSaw(ToolHeadData& data)
    {
        data.m_CircularSawD.CenterGO = GOPoint::Add(data.m_CircularSawD.CenterACIT.x,
                                         data.m_CircularSawD.CenterACIT.y,
                                         data.m_CircularSawD.CenterACIT.z,
                                         GOWeight::Thick);
        data.m_CircularSawD.CenterGO->SetColor(GOColor::RED);
        data.m_CircularSawD.NormalEndGO = GOPoint::Add(data.m_CircularSawD.NormalEndACIT.x,
                                        data.m_CircularSawD.NormalEndACIT.y,
                                        data.m_CircularSawD.NormalEndACIT.z,
                                        GOWeight::Thick);
        data.m_CircularSawD.NormalEndGO->SetColor(GOColor::GREEN);
        auto lnNormal = GOLine::Add(*data.m_CircularSawD.CenterGO, *data.m_CircularSawD.NormalEndGO);
        lnNormal->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_CircularSawD.CenterGO);
        this->m_GOPrimitivesInfo.push_back(data.m_CircularSawD.NormalEndGO);
        this->m_GOPrimitivesInfo.push_back(lnNormal);
    }
    void ACInfoToolhead::AddGOsInfoChainSaw(ToolHeadData& data)
    {
        data.m_ChainSawD.ChainbaseGO = GOPoint::Add(data.m_ChainSawD.ChainbaseACIT.x,
                                        data.m_ChainSawD.ChainbaseACIT.y,
                                        data.m_ChainSawD.ChainbaseACIT.z,
                                        GOWeight::Thick);
        data.m_ChainSawD.ChainbaseGO->SetColor(GOColor::RED);
        data.m_ChainSawD.ChainmidGO = GOPoint::Add(data.m_ChainSawD.ChainmidACIT.x,
                                       data.m_ChainSawD.ChainmidACIT.y,
                                       data.m_ChainSawD.ChainmidACIT.z,
                                       GOWeight::Thick);
        data.m_ChainSawD.ChainmidGO->SetColor(GOColor::GREEN);
        data.m_ChainSawD.ChainendGO = GOPoint::Add(data.m_ChainSawD.ChainendACIT.x,
                                       data.m_ChainSawD.ChainendACIT.y,
                                       data.m_ChainSawD.ChainendACIT.z,
                                       GOWeight::Thick);
        data.m_ChainSawD.ChainendGO->SetColor(GOColor::BLUE);
        data.m_ChainSawD.NormalStartGO = GOPoint::Add(data.m_ChainSawD.NormalStartACIT.x,
                                          data.m_ChainSawD.NormalStartACIT.y,
                                          data.m_ChainSawD.NormalStartACIT.z,
                                          GOWeight::Thick);
        data.m_ChainSawD.NormalStartGO->SetColor(GOColor::YELLOW);
        data.m_ChainSawD.NormalEndGO = GOPoint::Add(data.m_ChainSawD.NormalEndACIT.x,
                                        data.m_ChainSawD.NormalEndACIT.y,
                                        data.m_ChainSawD.NormalEndACIT.z,
                                        GOWeight::Thick);
        data.m_ChainSawD.NormalEndGO->SetColor(GOColor::CYAN);
        auto lnBaseMid = GOLine::Add(*data.m_ChainSawD.ChainbaseGO, *data.m_ChainSawD.ChainmidGO);
        lnBaseMid->SetColor(GOColor::MAGENTA);
        auto lnMidEnd = GOLine::Add(*data.m_ChainSawD.ChainmidGO, *data.m_ChainSawD.ChainendGO);
        lnMidEnd->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainbaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainmidGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.ChainendGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.NormalStartGO);
        this->m_GOPrimitivesInfo.push_back(data.m_ChainSawD.NormalEndGO);
        this->m_GOPrimitivesInfo.push_back(lnBaseMid);
        this->m_GOPrimitivesInfo.push_back(lnMidEnd);
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
        data.m_SaberSawD.NormalStartGO = GOPoint::Add(data.m_SaberSawD.NormalStartACIT.x,
                                          data.m_SaberSawD.NormalStartACIT.y,
                                          data.m_SaberSawD.NormalStartACIT.z,
                                          GOWeight::Thick);
        data.m_SaberSawD.NormalStartGO->SetColor(GOColor::BLUE);
        data.m_SaberSawD.NormalEndGO = GOPoint::Add(data.m_SaberSawD.NormalEndACIT.x,
                                        data.m_SaberSawD.NormalEndACIT.y,
                                        data.m_SaberSawD.NormalEndACIT.z,
                                        GOWeight::Thick);
        data.m_SaberSawD.NormalEndGO->SetColor(GOColor::YELLOW);
        auto lineAxis = GOLine::Add(*data.m_SaberSawD.ToolbaseGO, *data.m_SaberSawD.TooltipGO);
        lineAxis->SetColor(GOColor::MAGENTA);

        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.ToolbaseGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.TooltipGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.NormalStartGO);
        this->m_GOPrimitivesInfo.push_back(data.m_SaberSawD.NormalEndGO);
        this->m_GOPrimitivesInfo.push_back(lineAxis);
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