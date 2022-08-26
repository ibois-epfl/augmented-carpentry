#pragma once

#include "AIAC/Base.h"
#include "glm/glm.hpp"


namespace AIAC
{
    // enum GOFlags
    // {
    //     GO_Flag_None = 0,
    //     GO_Flag_Highlighted,
    //     GO_Flag_Selected,
    //     GO_Flag_Visible,
    //     GO_Flag_Enabled,
    // }

    enum GOType
    {
        GOTypeNone = 0,
        GOTypePoint,
        GOTypeLine,
        GOTypeCircle,
        GOTypeCylinder,
        GOTypePolyline,
        GOTypeTriangle,
        GOTypeMesh,
        GOTypeText
    };

    enum GOCategory
    {
        GOCategoryNone            = BIT(0),
        GOCategoryHole            = BIT(1),
        GOCategoryCut             = BIT(2),
        GOCategoryVolume          = BIT(3)
    };

    class GOPrimitive
    {
    public:
        GOPrimitive(GOCategory category, bool isVisible, glm::vec4 color);
        // ~GOPrimitive();
        virtual ~GOPrimitive() = default;

        uint32_t GenerateId();
        inline const uint32_t GetId() const { return m_Id; }

        virtual GOType GetGOType() = 0;

        inline GOCategory GetCategory() const { return m_Category; }
        inline bool GetVisibility() { return m_IsVisible; }
        inline glm::vec4 GetColor() { return m_Color; }
        inline bool GetState() { return m_State; }

        inline void SetVisibility(bool isVisible) { m_IsVisible = isVisible; }
        inline void SetColor(glm::vec4 color) { m_Color = color; }
        inline void SetState(bool state) { m_State = state; }

    // private:
    //     static std::vector<uint32_t> s_Ids;

    protected:
        uint32_t m_Id;
        GOCategory m_Category;
        bool m_IsVisible;
        glm::vec4 m_Color;
        bool m_State;
    };
    using GOPrimitivePointer = std::shared_ptr<GOPrimitive>;

    //TODO: add THICKNESS as property
    class GOPoint : public GOPrimitive
    {
    public:
        GOPoint(glm::vec3 position);
        virtual ~GOPoint() = default;

        virtual GOType GetGOType() override { return GOType::GOTypePoint; }

        inline glm::vec3 GetPosition() const { return m_Position; }
        inline float X() const { return m_Position.x; }
        inline float Y() const { return m_Position.y; }
        inline float Z() const { return m_Position.z; }
    
    private:
        glm::vec3 m_Position;
    };

    //TODO: add THICKNESS as property

    class GOLine : public GOPrimitive
    {
    public:
        GOLine(glm::vec3 p1, glm::vec3 p2);
        virtual ~GOLine() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeLine; }

        inline GOPoint GetPStart() const { return m_PStart; }
        inline GOPoint GetPEnd() const { return m_PEnd; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
    };

    //TODO: add THICKNESS as property

    class GOCircle : public GOPrimitive
    {
    public:
        GOCircle(GOPoint center, float radius);
        virtual ~GOCircle() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeCircle; }

    private:
        GOPoint m_Center;
        float m_Radius;
    };


    class GOCylinder : public GOPrimitive
    {
    public:
        GOCylinder(GOPoint p1, GOPoint p2, float radius);
        virtual ~GOCylinder() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeCylinder; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
        float m_Radius;
    };

    //TODO: add THICKNESS as property

    class GOPolyline : public GOPrimitive
    {
    public:
        GOPolyline(std::vector<GOPoint> points);
        virtual ~GOPolyline() = default;

        virtual GOType GetGOType() override { return GOType::GOTypePolyline; }

    private:
        std::vector<GOPoint> m_Points;
    };

    //TODO: add THICKNESS as property

    class GOTriangle : public GOPrimitive
    {
    public:
        GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3);
        virtual ~GOTriangle() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeTriangle; }

    private:
        GOPoint m_P1;
        GOPoint m_P2;
        GOPoint m_P3;
    };


    class GOMesh : public GOPrimitive
    {
    public:
        GOMesh(std::vector<GOPoint> points, std::vector<uint32_t> indices);
        virtual ~GOMesh() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeMesh; }

    private:
        std::vector<GOPoint> m_Points;
        std::vector<uint32_t> m_Indices;
    };

    //TODO: add THICKNESS as property

    class GOText : public GOPrimitive
    {
    public:
        GOText(std::string text, GOPoint anchor, double size);
        virtual ~GOText() = default;

        virtual GOType GetGOType() override { return GOType::GOTypeText; }

    private:
        std::string m_Text;
        GOPoint m_Anchor;
        double m_Size;
    };
}