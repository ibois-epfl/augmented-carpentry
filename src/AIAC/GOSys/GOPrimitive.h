#pragma once

#include <utility>

#include "AIAC/Base.h"
#include "glm/glm.hpp"


namespace AIAC
{
    enum GOFlags
    {
        GO_Flag_None = 0,
        GO_Flag_Highlighted,
        GO_Flag_Selected,
        GO_Flag_Visible,
        GO_Flag_Enabled,
    };

    enum GOTypeFlags
    {
        _GOPrimitive = 0,
        _GOPoint,
        _GOLine,
        _GOCircle,
        _GOCylinder,
        _GOPolyline,
        _GOTriangle,
        _GOMesh,
        _GOText,
    };


    struct GOThickness
    {
        static constexpr float Default            = 0.5f;
        static constexpr float Thin               = 0.1f;
        static constexpr float Thick              = 1.0f;
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
        explicit GOPrimitive(GOCategory category = GOCategoryNone,
                             bool isVisible = true,
                             glm::vec4 color = glm::vec4(0, 0, 0, 1));
        // ~GOPrimitive();
        virtual ~GOPrimitive() = default;

        uint32_t GenerateId();
        inline const uint32_t GetId() const { return m_Id; }

        inline GOCategory GetCategory() const { return m_Category; }
        inline bool GetVisibility() { return m_IsVisible; }
        inline glm::vec4 GetColor() const { return m_Color; }
        inline bool GetState() { return m_State; }
        inline GOTypeFlags GetType() { return m_Type; }

        inline void SetVisibility(bool isVisible) { m_IsVisible = isVisible; }
        inline void SetColor(glm::vec4 color) { m_Color = color; }
        inline void SetState(bool state) { m_State = state; }

    protected:
        uint32_t m_Id;
        GOCategory m_Category;
        bool m_IsVisible;
        glm::vec4 m_Color;
        bool m_State;
        GOTypeFlags m_Type;
    };
    using GOPrimitivePointer = std::shared_ptr<GOPrimitive>;


    class GOPoint : public GOPrimitive
    {
    public:
        GOPoint(glm::vec3 position);
        virtual ~GOPoint() = default;

        inline glm::vec3 GetPosition() const { return m_Position; }
        inline void SetPosition(glm::vec3 position) { m_Position = position; }
        inline float X() const { return m_Position.x; }
        inline float Y() const { return m_Position.y; }
        inline float Z() const { return m_Position.z; }
        inline void SetX(float x) { m_Position.x = x; }
        inline void SetY(float y) { m_Position.y = y; }
        inline void SetZ(float z) { m_Position.z = z; }

        inline float GetSize() const { return m_Size; }
        inline void SetSize(float size) { m_Size = size; }

    private:
        glm::vec3 m_Position;
        float m_Size = 1.0f;
    };


    class GOLine : public GOPrimitive
    {
    public:
        GOLine(GOPoint p1, GOPoint p2);
        virtual ~GOLine() = default;

        inline GOPoint GetPStart() const { return m_PStart; }
        inline GOPoint GetPEnd() const { return m_PEnd; }

        inline void SetThickness(float thickness) { m_Thickness = thickness; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
        float m_Thickness = GOThickness::Default;
    };


    class GOCircle : public GOPrimitive
    {
    public:
        GOCircle(GOPoint center, float radius);
        virtual ~GOCircle() = default;

        inline glm::vec3 GetNormal() const { return m_Normal; }
        inline GOPoint GetCenter() const { return m_Center; }
        inline float GetRadius() const { return m_Radius; }
        inline glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

        // TODO: What is this for?
        inline void SetThickness(float thickness) { m_Thickness = thickness; }

    private:
        GOPoint m_Center;
        glm::vec3 m_Normal = glm::vec3(0, 0, 1);
        glm::vec4 m_EdgeColor = glm::vec4(1, 0, 0, 1);
        float m_Radius;
        float m_Thickness = GOThickness::Default;
    };


    class GOCylinder : public GOPrimitive
    {
    public:
        GOCylinder(GOPoint p1, GOPoint p2, float radius);
        virtual ~GOCylinder() = default;

        GOPoint GetPStart() const { return m_PStart; }
        GOPoint GetPEnd() const { return m_PEnd; }
        float GetRadius() const { return m_Radius; }
        glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
        float m_Radius;
        glm::vec4 m_EdgeColor = glm::vec4(1, 1, 1, 1);
    };


    class GOPolyline : public GOPrimitive
    {
    public:
        GOPolyline(std::vector<GOPoint> points);
        virtual ~GOPolyline() = default;

        inline const std::vector<GOPoint> &GetPoints() const { return m_Points; }

        inline bool IsClosed() const { return m_IsClosed; }

        inline void SetThickness(float thickness) { m_Thickness = thickness; }

    private:
        // m_Points:
        // P0 ------------- P1
        //  |                \
        //  ----m_IsClosed---P2
        std::vector<GOPoint> m_Points;
        bool m_IsClosed = true;
        float m_Thickness = GOThickness::Default;
    };


    class GOTriangle : public GOPrimitive
    {
    public:
        GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3);
        virtual ~GOTriangle() = default;

        const std::vector<glm::vec3> GetVertices() const {
            return std::vector<glm::vec3>{m_P1.GetPosition(), m_P2.GetPosition(), m_P3.GetPosition()};
        }

        inline void SetThickness(float thickness) { m_Thickness = thickness; }

    private:
        GOPoint m_P1;
        GOPoint m_P2;
        GOPoint m_P3;
        float m_Thickness = GOThickness::Default;
    };


    class GOMesh : public GOPrimitive
    {
    public:
        GOMesh(std::vector<GOPoint> points, std::vector<uint32_t> indices);
        virtual ~GOMesh() = default;

    private:
        std::vector<GOPoint> m_Points;
        std::vector<uint32_t> m_Indices;
    };


    class GOText : public GOPrimitive
    {
    public:
        GOText(std::string text, GOPoint anchor, double size);
        virtual ~GOText() = default;

        std::string GetText() const { return m_Text; }

        void SetText(std::string text) { m_Text = std::move(text); }

        inline void SetThickness(float thickness) { m_Thickness = thickness; }

    private:
        std::string m_Text;
        GOPoint m_Anchor;
        double m_Size;
        float m_Thickness = GOThickness::Default;
    };
}