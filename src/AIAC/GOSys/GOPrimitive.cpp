#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Application.h"


// TODO: find a better pattern for adding the object from constructor to the registry 
namespace AIAC
{
    GOPrimitive::GOPrimitive(GOCategory category, bool isVisible, glm::vec4 color)
        : m_Category(category), m_IsVisible(isVisible), m_Color(color), m_State(false), m_Type(GOTypeFlags::_GOPrimitive)
    {
        m_Id = GenerateId();
    }

    uint32_t GOPrimitive::GenerateId()
    {
        uint32_t id = std::hash<std::string>{}(std::to_string(std::rand()));
        if (AIAC_GOREG->CheckIfKeyExists(id))
            return GenerateId();
        else
            return id;
    }


    GOPoint::GOPoint(glm::vec3 position)
        : m_Position(position)
    {
        m_Type = GOTypeFlags::_GOPoint;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOPoint>(*this));
    }

    GOLine::GOLine(GOPoint p1, GOPoint p2)
        : m_PStart(p1), m_PEnd(p2)
    {
        m_Type = GOTypeFlags::_GOLine;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOLine>(*this));
    }


    GOCircle::GOCircle(GOPoint center, float radius)
        : m_Center(center), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCircle;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOCircle>(*this));
    }


    GOCylinder::GOCylinder(GOPoint p1, GOPoint p2, float radius)
        : m_PStart(p1), m_PEnd(p2), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCylinder;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOCylinder>(*this));
    }


    GOPolyline::GOPolyline(std::vector<GOPoint> points)
        : m_Points(points)
    {
        m_Type = GOTypeFlags::_GOPolyline;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOPolyline>(*this));
    }


    GOTriangle::GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3)
        : m_P1(p1), m_P2(p2), m_P3(p3)
    {
        m_Type = GOTypeFlags::_GOTriangle;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOTriangle>(*this));
    }


    GOMesh::GOMesh()
    {
        m_Type = GOTypeFlags::_GOMesh;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOMesh>(*this));
    }

    GOMesh::GOMesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
        : m_Vertices(vertices), m_Indices(indices)
    {
        m_Type = GOTypeFlags::_GOMesh;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOMesh>(*this));
    }


    GOText::GOText(std::string text, GOPoint anchor, double size)
        : m_Text(text), m_Anchor(anchor), m_Size(size)
    {
        m_Anchor.SetVisibility(false);

        m_Type = GOTypeFlags::_GOText;
        AIAC_GOREG->Register(m_Id, std::make_shared<GOText>(*this));

    }
}