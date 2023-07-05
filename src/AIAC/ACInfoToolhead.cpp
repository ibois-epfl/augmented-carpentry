#include "ACInfoToolhead.h"
#include "AIAC/Log.h"

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

            m_DrillBitD.Toolbase = ParseString2GlmVector(toolhead.child("toolbase").child_value()) * this->GetScaleF();
            m_DrillBitD.Tooltip = ParseString2GlmVector(toolhead.child("tooltip").child_value()) * this->GetScaleF();
            m_DrillBitD.Eattip = ParseString2GlmVector(toolhead.child("eattip").child_value()) * this->GetScaleF();
            m_DrillBitD.Chucktip = ParseString2GlmVector(toolhead.child("chucktip").child_value()) * this->GetScaleF();
            m_DrillBitD.Radius = toolhead.child("radius").text().as_float() * this->GetScaleF();
        }
        else if (type == "circularsaw")
        {
            m_Type = ACToolHeadType::CIRCULARSAW;
            m_Name = toolhead.attribute("name").as_string();
            m_CircularSawD.Center = ParseString2GlmVector(toolhead.child("center").child_value()) * this->GetScaleF();

            m_CircularSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_CircularSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_CircularSawD.Radius = toolhead.child("radius").text().as_float() * this->GetScaleF();
        }
        else if (type == "chainsaw")
        {
            m_Type = ACToolHeadType::CHAINSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_ChainSawD.Chainbase = ParseString2GlmVector(toolhead.child("chainbase").child_value()) * this->GetScaleF();
            m_ChainSawD.Chainmid = ParseString2GlmVector(toolhead.child("chainmid").child_value()) * this->GetScaleF();
            m_ChainSawD.Chainend = ParseString2GlmVector(toolhead.child("chainend").child_value()) * this->GetScaleF();
            m_ChainSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_ChainSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
            m_ChainSawD.Width = toolhead.child("width").text().as_float() * this->GetScaleF();
        }
        else if (type == "sabersaw")
        {
            m_Type = ACToolHeadType::SABERSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_SaberSawD.Toolbase = ParseString2GlmVector(toolhead.child("toolbase").child_value()) * this->GetScaleF();
            m_SaberSawD.Tooltip = ParseString2GlmVector(toolhead.child("tooltip").child_value()) * this->GetScaleF();
            m_SaberSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value()) * this->GetScaleF();
            m_SaberSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value()) * this->GetScaleF();
        }
        else if (type == "axis")
        {
            m_Type = ACToolHeadType::AXIS;
            m_Name = toolhead.attribute("name").as_string();

            m_AxisD.Origin = ParseString2GlmVector(toolhead.child("origin").child_value()) * this->GetScaleF();
            m_AxisD.XAxis = ParseString2GlmVector(toolhead.child("xaxis").child_value()) * this->GetScaleF();
            m_AxisD.YAxis = ParseString2GlmVector(toolhead.child("yaxis").child_value()) * this->GetScaleF();
            m_AxisD.YPoint1 = ParseString2GlmVector(toolhead.child("ypoint1").child_value()) * this->GetScaleF();
            m_AxisD.ZAxis = ParseString2GlmVector(toolhead.child("zaxis").child_value()) * this->GetScaleF();
            m_AxisD.ZPoint1 = ParseString2GlmVector(toolhead.child("zpoint1").child_value()) * this->GetScaleF();
            m_AxisD.ZPoint2 = ParseString2GlmVector(toolhead.child("zpoint2").child_value()) * this->GetScaleF();

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

    ACInfoToolhead::ACInfoToolhead(std::string acitPath, std::string objPath)
        : m_ACITPath(acitPath), m_OBJPath(objPath) 
    {
        this->m_Data.LoadACIT(acitPath);

        this->AddGOsInfo(this->m_Data);
        this->m_GOPrimitivesInfoOriginal.clear();
        for (auto& go : this->m_GOPrimitivesInfo) 
        {
            this->m_GOPrimitivesInfoOriginal.push_back(std::make_shared<GOPoint>(*go)); 
        }

        this->AddGOsWidget();
        this->m_GOPrimitivesWidgetOriginal = this->m_GOPrimitivesWidget;
        // FIXME: do the same as above for copying folders

        this->SetVisibility(true);  // TODO: set back to false
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
            case ACToolHeadType::AXIS:
                this->AddGOsInfoAxis(data);
                break;
            default:
                AIAC_ERROR("Toolhead type not supported");
                break;
        }
        return;
    }

    void ACInfoToolhead::AddGOsInfoDrillBit(ToolHeadData& data)
    {
        auto ptToolbase = GOPoint::Add(data.m_DrillBitD.Toolbase.x,
                                       data.m_DrillBitD.Toolbase.y,
                                       data.m_DrillBitD.Toolbase.z,
                                       GOWeight::Thick);
        auto ptTooltip = GOPoint::Add(data.m_DrillBitD.Tooltip.x, 
                                      data.m_DrillBitD.Tooltip.y,
                                      data.m_DrillBitD.Tooltip.z,
                                      GOWeight::Thick);
        auto ptEattip = GOPoint::Add(data.m_DrillBitD.Eattip.x,
                                     data.m_DrillBitD.Eattip.y,
                                     data.m_DrillBitD.Eattip.z,
                                     GOWeight::Thick);
        auto ptChucktip = GOPoint::Add(data.m_DrillBitD.Chucktip.x,
                                       data.m_DrillBitD.Chucktip.y,
                                       data.m_DrillBitD.Chucktip.z,
                                       GOWeight::Thick);
        // auto lineAxis = GOLine::Add(*ptToolbase, *ptTooltip);
        // lineAxis->SetVisibility(false);

        this->m_GOPrimitivesInfo.push_back(ptToolbase);
        this->m_GOPrimitivesInfo.push_back(ptTooltip);
        this->m_GOPrimitivesInfo.push_back(ptEattip);
        this->m_GOPrimitivesInfo.push_back(ptChucktip);
        // this->m_GOPrimitivesInfo.push_back(lineAxis);
    }
    void ACInfoToolhead::AddGOsInfoCircularSaw(ToolHeadData& data)
    {
        auto ptCenter = GOPoint::Add(data.m_CircularSawD.Center.x,
                                     data.m_CircularSawD.Center.y,
                                     data.m_CircularSawD.Center.z,
                                     GOWeight::Thick);
        auto ptNormalEnd = GOPoint::Add(data.m_CircularSawD.NormalEnd.x,
                                        data.m_CircularSawD.NormalEnd.y,
                                        data.m_CircularSawD.NormalEnd.z,
                                        GOWeight::Thick);
        // glm::vec3 norm = glm::normalize(ptNormalEnd->GetPosition() - ptCenter->GetPosition());
        // auto circle = GOCircle::Add(*ptCenter, norm, data.m_CircularSawD.Radius);

        this->m_GOPrimitivesInfo.push_back(ptCenter);
        this->m_GOPrimitivesInfo.push_back(ptNormalEnd);
        // this->m_GOPrimitivesInfo.push_back(circle);
    }
    void ACInfoToolhead::AddGOsInfoChainSaw(ToolHeadData& data)
    {
        auto ptChainbase = GOPoint::Add(data.m_ChainSawD.Chainbase.x,
                                        data.m_ChainSawD.Chainbase.y,
                                        data.m_ChainSawD.Chainbase.z,
                                        GOWeight::Thick);
        auto ptChainmid = GOPoint::Add(data.m_ChainSawD.Chainmid.x,
                                       data.m_ChainSawD.Chainmid.y,
                                       data.m_ChainSawD.Chainmid.z,
                                       GOWeight::Thick);
        auto ptChainend = GOPoint::Add(data.m_ChainSawD.Chainend.x,
                                       data.m_ChainSawD.Chainend.y,
                                       data.m_ChainSawD.Chainend.z,
                                       GOWeight::Thick);
        auto ptNormalStart = GOPoint::Add(data.m_ChainSawD.NormalStart.x,
                                          data.m_ChainSawD.NormalStart.y,
                                          data.m_ChainSawD.NormalStart.z,
                                          GOWeight::Thick);
        auto ptNormalEnd = GOPoint::Add(data.m_ChainSawD.NormalEnd.x,
                                        data.m_ChainSawD.NormalEnd.y,
                                        data.m_ChainSawD.NormalEnd.z,
                                        GOWeight::Thick);
        // auto lnBaseMid = GOLine::Add(*ptChainbase, *ptChainmid);
        // auto lnMidEnd = GOLine::Add(*ptChainmid, *ptChainend);

        this->m_GOPrimitivesInfo.push_back(ptChainbase);
        this->m_GOPrimitivesInfo.push_back(ptChainmid);
        this->m_GOPrimitivesInfo.push_back(ptChainend);
        this->m_GOPrimitivesInfo.push_back(ptNormalStart);
        this->m_GOPrimitivesInfo.push_back(ptNormalEnd);
        // this->m_GOPrimitivesInfo.push_back(lnBaseMid);
        // this->m_GOPrimitivesInfo.push_back(lnMidEnd);
    }
    void ACInfoToolhead::AddGOsInfoSaberSaw(ToolHeadData& data)
    {
        auto ptToolbase = GOPoint::Add(data.m_SaberSawD.Toolbase.x,
                                       data.m_SaberSawD.Toolbase.y,
                                       data.m_SaberSawD.Toolbase.z,
                                       GOWeight::Thick);
        auto ptTooltip = GOPoint::Add(data.m_SaberSawD.Tooltip.x,
                                      data.m_SaberSawD.Tooltip.y,
                                      data.m_SaberSawD.Tooltip.z,
                                      GOWeight::Thick);
        auto ptNormalStart = GOPoint::Add(data.m_SaberSawD.NormalStart.x,
                                          data.m_SaberSawD.NormalStart.y,
                                          data.m_SaberSawD.NormalStart.z,
                                          GOWeight::Thick);
        auto ptNormalEnd = GOPoint::Add(data.m_SaberSawD.NormalEnd.x,
                                        data.m_SaberSawD.NormalEnd.y,
                                        data.m_SaberSawD.NormalEnd.z,
                                        GOWeight::Thick);
        // auto lineAxis = GOLine::Add(*ptToolbase, *ptTooltip);
        // lineAxis->SetWeight(GOWeight::Thick);

        this->m_GOPrimitivesInfo.push_back(ptToolbase);
        this->m_GOPrimitivesInfo.push_back(ptTooltip);
        this->m_GOPrimitivesInfo.push_back(ptNormalStart);
        this->m_GOPrimitivesInfo.push_back(ptNormalEnd);
        // this->m_GOPrimitivesInfo.push_back(lineAxis);
    }
    void ACInfoToolhead::AddGOsInfoAxis(ToolHeadData& data)
    {
        auto ptOrigin = GOPoint::Add(data.m_AxisD.Origin.x,
                                     data.m_AxisD.Origin.y,
                                     data.m_AxisD.Origin.z,
                                     GOWeight::Thick);

        auto ptX = GOPoint::Add(data.m_AxisD.XAxis.x,
                                data.m_AxisD.XAxis.y,
                                data.m_AxisD.XAxis.z,
                                GOWeight::Thick);
        auto ptY = GOPoint::Add(data.m_AxisD.YAxis.x,
                                data.m_AxisD.YAxis.y,
                                data.m_AxisD.YAxis.z,
                                GOWeight::Thick);
        auto ptY1 = GOPoint::Add(data.m_AxisD.YPoint1.x,
                                 data.m_AxisD.YPoint1.y,
                                 data.m_AxisD.YPoint1.z,
                                 GOWeight::Thick);
        auto ptZ = GOPoint::Add(data.m_AxisD.ZAxis.x,
                                data.m_AxisD.ZAxis.y,
                                data.m_AxisD.ZAxis.z,
                                GOWeight::Thick);
        auto ptZ1 = GOPoint::Add(data.m_AxisD.ZPoint1.x,
                                 data.m_AxisD.ZPoint1.y,
                                 data.m_AxisD.ZPoint1.z,
                                 GOWeight::Thick);
        auto ptZ2 = GOPoint::Add(data.m_AxisD.ZPoint2.x,
                                 data.m_AxisD.ZPoint2.y,
                                 data.m_AxisD.ZPoint2.z,
                                 GOWeight::Thick);

        this->m_GOPrimitivesInfo.push_back(ptOrigin);
        this->m_GOPrimitivesInfo.push_back(ptX);
        this->m_GOPrimitivesInfo.push_back(ptY);
        this->m_GOPrimitivesInfo.push_back(ptY1);
        this->m_GOPrimitivesInfo.push_back(ptZ);
        this->m_GOPrimitivesInfo.push_back(ptZ1);
        this->m_GOPrimitivesInfo.push_back(ptZ2);

        
    }

    void ACInfoToolhead::AddGOsWidget() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetDrillBit() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetCircularSaw() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetChainSaw() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetSaberSaw() {}  // TODO: implement

    void ACInfoToolhead::SetVisibility(bool visible)
    {
        AIAC_INFO("SetVisibility: {} {}", visible, m_GOPrimitivesInfo.size());

        for (auto& go : m_GOPrimitivesInfo)  // FIXME: this should be a seperate function
            go->SetVisibility(visible);
        for (auto& go : m_GOPrimitivesWidget)
            go->SetVisibility(visible);
    }

    void ACInfoToolhead::Transform(glm::mat4 transform)
    {
        // TODO: use original to update current GOs (info + widgets)
        // TODO: add in-place transform + npormal transform in go primitive
        for (uint i = 0; i < m_GOPrimitivesInfo.size(); i++)
        {
            // std::shared_ptr<GOPoint> go = std::make_shared<GOPoint>(*(m_GOPrimitivesInfoOriginal[i]));
            glm::vec3 position = m_GOPrimitivesInfoOriginal[i]->GetPosition();
            std::stringstream ss;
            ss << "position: " << position.x << " " << position.y << " " << position.z;
            ss << "\n";
            glm::vec4 position4 = glm::vec4(position, 1.0f);
            glm::vec4 position4_transformed = transform * position4;
            ss << "position_transformed: " << position4_transformed.x << " " << position4_transformed.y << " " << position4_transformed.z;
            AIAC_INFO(ss.str());
            m_GOPrimitivesInfo[i]->SetPosition(position4_transformed);
        }

        // for (uint i = 0; i < m_GOPrimitivesWidget.size(); i++)
        // {
        //     std::shared_ptr<GOPrimitive> go = std::make_shared<GOPrimitive>(*(m_GOPrimitivesWidgetOriginal[i]));
        //     go->Transform(transform);
        //     m_GOPrimitivesWidget[i]->SetValueFrom(go);
        // }
    }
}