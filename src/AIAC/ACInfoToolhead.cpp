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

            m_DrillBitD.Toolbase = ParseString2GlmVector(toolhead.child("toolbase").child_value());
            m_DrillBitD.Tooltip = ParseString2GlmVector(toolhead.child("tooltip").child_value());
            m_DrillBitD.Eattip = ParseString2GlmVector(toolhead.child("eattip").child_value());
            m_DrillBitD.Chucktip = ParseString2GlmVector(toolhead.child("chucktip").child_value());
            m_DrillBitD.Radius = toolhead.child("radius").text().as_float();
        }
        else if (type == "circularsaw")
        {
            m_Type = ACToolHeadType::CIRCULARSAW;
            m_Name = toolhead.attribute("name").as_string();
            m_CircularSawD.Center = ParseString2GlmVector(toolhead.child("center").child_value());

            m_CircularSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value());
            m_CircularSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value());
            m_CircularSawD.Radius = toolhead.child("radius").text().as_float();
        }
        else if (type == "chainsaw")
        {
            m_Type = ACToolHeadType::CHAINSAW;
            m_Name = toolhead.attribute("name").as_string();
            m_ChainSawD.Chainbase = ParseString2GlmVector(toolhead.child("chainbase").child_value());

            m_ChainSawD.Chainmid = ParseString2GlmVector(toolhead.child("chainmid").child_value());
            m_ChainSawD.Chainend = ParseString2GlmVector(toolhead.child("chainend").child_value());
            m_ChainSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value());
            m_ChainSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value());
            m_ChainSawD.Width = toolhead.child("width").text().as_float();
        }
        else if (type == "sabersaw")
        {
            m_Type = ACToolHeadType::SABERSAW;
            m_Name = toolhead.attribute("name").as_string();

            m_SaberSawD.Toolbase = ParseString2GlmVector(toolhead.child("toolbase").child_value());
            m_SaberSawD.Tooltip = ParseString2GlmVector(toolhead.child("tooltip").child_value());
            m_SaberSawD.NormalStart = ParseString2GlmVector(toolhead.child("normalstart").child_value());
            m_SaberSawD.NormalEnd = ParseString2GlmVector(toolhead.child("normalend").child_value());
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
        this->AddGOsWidget();
    }

    void ACInfoToolhead::AddGOsInfo(ToolHeadData& data)
    {
        switch (data.m_Type)
        {
            case ACToolHeadType::DRILLBIT:
                this->AddGOsInfoDrillBit(data);
                break;

            case ACToolHeadType::CIRCULARSAW:
                // uint32_t idPtCenter = GOPoint::Add(data.m_CircularSawD.Center.x,
                //                                    data.m_CircularSawD.Center.y,
                //                                    data.m_CircularSawD.Center.z);
                // uint32_t idPtNormalEnd = GOPoint::Add(data.m_CircularSawD.NormalEnd.x,
                //                                       data.m_CircularSawD.NormalEnd.y,
                //                                       data.m_CircularSawD.NormalEnd.z);
                // auto PtCenter = GOPoint::Get(idPtCenter);
                // auto PtNormalEnd = GOPoint::Get(idPtNormalEnd);
                // // TODO: create GOcircle with radius, center and vector constructor
                break;
            
            case ACToolHeadType::CHAINSAW:
                // uint32_t idPtChainbase = GOPoint::Add(data.m_ChainSawD.Chainbase.x,
                //                                       data.m_ChainSawD.Chainbase.y,
                //                                       data.m_ChainSawD.Chainbase.z);
                // uint32_t idPtChainmid = GOPoint::Add(data.m_ChainSawD.Chainmid.x,
                //                                      data.m_ChainSawD.Chainmid.y,
                //                                      data.m_ChainSawD.Chainmid.z);
                // uint32_t idPtChainend = GOPoint::Add(data.m_ChainSawD.Chainend.x,
                //                                      data.m_ChainSawD.Chainend.y,
                //                                      data.m_ChainSawD.Chainend.z);
                // uint32_t idPtNormalStart = GOPoint::Add(data.m_ChainSawD.NormalStart.x,
                //                                         data.m_ChainSawD.NormalStart.y,
                //                                         data.m_ChainSawD.NormalStart.z);
                // uint32_t idPtNormalEnd = GOPoint::Add(data.m_ChainSawD.NormalEnd.x,
                //                                       data.m_ChainSawD.NormalEnd.y,
                //                                       data.m_ChainSawD.NormalEnd.z);
                // std::vector<GOPoint> polyPts = { GOPoint::Get(idPtChainbase),
                //                                  GOPoint::Get(idPtChainmid),
                //                                  GOPoint::Get(idPtChainend) };
                // uint32_t idPolyChain = GOPolygon::Add(polyPts);
                break;

            case ACToolHeadType::SABERSAW:
                // uint32_t idPtToolbase = GOPoint::Add(data.m_SaberSawD.Toolbase.x,
                //                                       data.m_SaberSawD.Toolbase.y,
                //                                       data.m_SaberSawD.Toolbase.z);
                // uint32_t idPtTooltip = GOPoint::Add(data.m_SaberSawD.Tooltip.x,
                //                                       data.m_SaberSawD.Tooltip.y,
                //                                       data.m_SaberSawD.Tooltip.z);
                // uint32_t idPtNormalStart = GOPoint::Add(data.m_SaberSawD.NormalStart.x,
                //                                           data.m_SaberSawD.NormalStart.y,
                //                                           data.m_SaberSawD.NormalStart.z);
                // uint32_t idPtNormalEnd = GOPoint::Add(data.m_SaberSawD.NormalEnd.x,
                //                                         data.m_SaberSawD.NormalEnd.y,
                //                                         data.m_SaberSawD.NormalEnd.z);
                // auto PtToolbase = GOPoint::Get(idPtToolbase);
                // auto PtTooltip = GOPoint::Get(idPtTooltip);
                // uint32_t idLineAxis = GOLine::Add(PtToolbase*, PtTooltip*);
                break;

            default:
                AIAC_ERROR("Toolhead type not supported");
                break;
        }
        
        return; 
    }

    void ACInfoToolhead::AddGOsInfoDrillBit(ToolHeadData& data)
    {
        // uint32_t idPtToolbase = GOPoint::Add(data.m_DrillBitD.Toolbase.x * this->GetScaleF(), //FIXME: get scale right
        //                                     data.m_DrillBitD.Toolbase.y * this->GetScaleF(),
        //                                     data.m_DrillBitD.Toolbase.z * this->GetScaleF(),
        //                                     5.0f);
        // auto PtToolbase = GOPoint::Get(idPtToolbase);
        // PtToolbase->SetVisibility(false);


        // uint32_t idPtTooltip = GOPoint::Add(data.m_DrillBitD.Tooltip.x * this->GetScaleF(), 
        //                                     data.m_DrillBitD.Tooltip.y * this->GetScaleF(),
        //                                     data.m_DrillBitD.Tooltip.z * this->GetScaleF(),
        //                                     5.0f);
        // auto PtTooltip = GOPoint::Get(idPtTooltip);
        // PtTooltip->SetVisibility(false);

        AIAC_INFO("---------------------------");
        AIAC_INFO(data.m_DrillBitD.Eattip.z);
        AIAC_INFO("---------------------------");

        uint32_t idPtEattip = GOPoint::Add((data.m_DrillBitD.Eattip.x * this->GetScaleF()),
                                           (data.m_DrillBitD.Eattip.y * this->GetScaleF()),
                                           (data.m_DrillBitD.Eattip.z * this->GetScaleF()),
                                           5.0f);
        auto PtEattip = GOPoint::Get(idPtEattip);

        AIAC_INFO("---------------------------");
        AIAC_INFO(PtEattip->Z());
        AIAC_INFO("---------------------------");
        // // PtEattip->SetVisibility(false);

        // uint32_t idPtChucktip = GOPoint::Add(data.m_DrillBitD.Chucktip.x * this->GetScaleF(),
        //                                     data.m_DrillBitD.Chucktip.y * this->GetScaleF(),
        //                                     data.m_DrillBitD.Chucktip.z * this->GetScaleF(),
        //                                     5.0f);
        // auto PtChucktip = GOPoint::Get(idPtChucktip);
        // // PtChucktip->SetVisibility(false);




        // uint32_t idLineAxis = GOLine::Add(*PtToolbase, GOPoint(70.f,70.f,70.f));
        // auto LineAxis = GOLine::Get(idLineAxis);
        // LineAxis->SetVisibility(false);

        //toDO: test
        // uint32_t idPt1 = GOPoint::Add(1, 1, 1, 5.0f);
        uint32_t idPt2 = GOPoint::Add(20, 50, 20, 5.0f);
        // uint32_t idPt3 = GOPoint::Add(30, 30, 30, 5.0f);
        // auto pt1 = GOPoint::Get(idPt1);
        // auto pt2 = GOPoint::Get(idPt2);
        // auto pt3 = GOPoint::Get(idPt3);
        // uint32_t line = GOLine::Add(*pt1, *pt2, 3.0f);
        // uint32_t line2 = GOLine::Add(*pt1, *pt3, 3.0f);

        // TODO: test
        // uint32_t test = GOLine::Add(GOPoint(3,3,3), GOPoint(30,30,30));

        // this->m_GOPrimitivesInfo.push_back(idPtToolbase);
        // this->m_GOPrimitivesInfo.push_back(idPtTooltip);
        // this->m_GOPrimitivesInfo.push_back(idPtEattip);
        // this->m_GOPrimitivesInfo.push_back(idPtChucktip);
        // this->m_GOPrimitivesInfo.push_back(idLineAxis);
    }
    void ACInfoToolhead::AddGOsInfoCircularSaw(ToolHeadData& data) {}  // TODO: implement
    void ACInfoToolhead::AddGOsInfoChainSaw(ToolHeadData& data) {}  // TODO: implement
    void ACInfoToolhead::AddGOsInfoSaberSaw(ToolHeadData& data) {}  // TODO: implement

    void ACInfoToolhead::AddGOsWidget() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetDrillBit() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetCircularSaw() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetChainSaw() {}  // TODO: implement
    void ACInfoToolhead::AddGOsWidgetSaberSaw() {}  // TODO: implement




}