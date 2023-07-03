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

        this->CreateGOsInfo();
        this->CreateGOsWidget();
    }

    ACInfoToolhead::CreateGOsInfo()
    {
        ToolHeadData& data = this->m_Data;
        if (data.m_Type == ACToolHeadType::DRILLBIT)
        {
            uint32_t idPtToolbase = GOPoint::Add(data.m_DrillBitD.Toolbase.x, 
                                                 data.m_DrillBitD.Toolbase.y,
                                                 data.m_DrillBitD.Toolbase.z);

    }

    ACInfoToolhead::CreateGOsWidget()
    {

    }
}