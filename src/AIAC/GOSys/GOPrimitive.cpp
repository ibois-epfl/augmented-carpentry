#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Application.h"

namespace AIAC
{
    GOPrimitive::GOPrimitive(GOCategory category = GOCategoryNone, bool isVisible = true, glm::vec4 color = glm::vec4(1, 1, 1, 1))
        : m_Category(category), m_IsVisible(isVisible), m_Color(color), m_State(false)
    {
        m_Id = GenerateId();
        // TODO: possible to add automatically an object to register like this
        // add a reference to the registry
        // AIAC_GOREG->Register(m_Id, GetSharedPtr());
    }

    // GOPrimitive::~GOPrimitive()
    // {
    //     // AIAC_GOREG->Unregister(m_Id);
    // }

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
    {}


    GOLine::GOLine(glm::vec3 p1, glm::vec3 p2)
        : m_PStart(p1), m_PEnd(p2)
    {}


    GOCircle::GOCircle(GOPoint center, float radius)
        : m_Center(center), m_Radius(radius)
    {}


    GOCylinder::GOCylinder(GOPoint p1, GOPoint p2, float radius)
        : m_PStart(p1), m_PEnd(p2), m_Radius(radius)
    {}


    GOPolyline::GOPolyline(std::vector<GOPoint> points)
        : m_Points(points)
    {}


    GOTriangle::GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3)
        : m_P1(p1), m_P2(p2), m_P3(p3)
    {}


    GOMesh::GOMesh(std::vector<GOPoint> points, std::vector<uint32_t> indices)
        : m_Points(points), m_Indices(indices)
    {}


    GOText::GOText(std::string text, GOPoint anchor, double size)
        : m_Text(text), m_Anchor(anchor), m_Size(size)
    {
        m_Anchor.SetVisibility(false);
    }
}