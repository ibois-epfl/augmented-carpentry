#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Application.h"

// FIXME: bug of reference to instance
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

    void GOPrimitive::Remove(const uint32_t& id)
    {
        AIAC_GOREG->Unregister(id);
    }


    GOPoint::GOPoint(float x, float y, float z)
    {
        m_Position = glm::vec3(x, y, z);
        m_Type = GOTypeFlags::_GOPoint;
    }

    GOPoint::GOPoint(glm::vec3 position)
        : m_Position(position)
    {
        m_Type = GOTypeFlags::_GOPoint;
    }

    uint32_t GOPoint::Add(float x, float y, float z)
    {
        auto ptrGO = std::make_shared<GOPoint>(x, y, z);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    uint32_t GOPoint::Add(glm::vec3 position)
    {
        auto ptrGO = std::make_shared<GOPoint>(position);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOPoint> GOPoint::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOPoint>(AIAC_GOREG->Get(id));
    }


    GOLine::GOLine(GOPoint p1, GOPoint p2, float weight)
        : m_PStart(p1), m_PEnd(p2)
    {
        m_Weight = weight;
        m_Type = GOTypeFlags::_GOLine;
    }

    uint32_t GOLine::Add(GOPoint p1, GOPoint p2, float weight)
    {
        auto ptrGO = std::make_shared<GOLine>(p1, p2, weight);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOLine> GOLine::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOLine>(AIAC_GOREG->Get(id));
    }


    GOCircle::GOCircle(GOPoint center, float radius)
        : m_Center(center), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCircle;
    }

    uint32_t GOCircle::Add(GOPoint center, float radius)
    {
        auto ptrGO = std::make_shared<GOCircle>(center, radius);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOCircle> GOCircle::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOCircle>(AIAC_GOREG->Get(id));
    }


    GOCylinder::GOCylinder(GOPoint p1, GOPoint p2, float radius)
        : m_PStart(p1), m_PEnd(p2), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCylinder;
    }

    uint32_t GOCylinder::Add(GOPoint p1, GOPoint p2, float radius)
    {
        auto ptrGO = std::make_shared<GOCylinder>(p1, p2, radius);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOCylinder> GOCylinder::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOCylinder>(AIAC_GOREG->Get(id));
    }


    GOPolyline::GOPolyline(std::vector<GOPoint> points)
        : m_Points(points)
    {
        m_Type = GOTypeFlags::_GOPolyline;
    }

    uint32_t GOPolyline::Add(std::vector<GOPoint> points)
    {
        auto ptrGO = std::make_shared<GOPolyline>(points);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOPolyline> GOPolyline::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOPolyline>(AIAC_GOREG->Get(id));
    }


    GOTriangle::GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3)
        : m_P1(p1), m_P2(p2), m_P3(p3)
    {
        m_Type = GOTypeFlags::_GOTriangle;
    }

    uint32_t GOTriangle::Add(GOPoint p1, GOPoint p2, GOPoint p3)
    {
        auto ptrGO = std::make_shared<GOTriangle>(p1, p2, p3);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOTriangle> GOTriangle::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOTriangle>(AIAC_GOREG->Get(id));
    }


    GOMesh::GOMesh()
    {
        m_Type = GOTypeFlags::_GOMesh;
    }

    GOMesh::GOMesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
        : m_Vertices(vertices), m_Indices(indices)
    {
        m_Type = GOTypeFlags::_GOMesh;
    }

    uint32_t GOMesh::Add()
    {
        auto ptrGO = std::make_shared<GOMesh>();
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    uint32_t GOMesh::Add(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
    {
        auto ptrGO = std::make_shared<GOMesh>(vertices, indices);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOMesh> GOMesh::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOMesh>(AIAC_GOREG->Get(id));
    }


    GOText::GOText(std::string text, GOPoint anchor, double size)
        : m_Text(text), m_Anchor(anchor), m_Size(size)
    {
        m_Anchor.SetVisibility(false);
        m_Type = GOTypeFlags::_GOText;
    }

    uint32_t GOText::Add(std::string text, GOPoint anchor, double size)
    {
        auto ptrGO = std::make_shared<GOText>(text, anchor, size);
        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOText> GOText::Get(const uint32_t& id)
    {
        return std::dynamic_pointer_cast<GOText>(AIAC_GOREG->Get(id));
    }
}