#pragma once

// #include <utility>
#include "AIAC/Base.h"
// #include "AIAC/Application.h"
#include "glm/glm.hpp"

namespace AIAC
{
    // TODO: implement flag system
    // enum GOStateFlags
    // {
    //     GOFlagNone = 0,
    //     GOFlagSelected,
    //     GOFlagVisible,
    // };

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

    struct GOWeight
    {
        static constexpr float Default            = 1.0f;
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
                             glm::vec4 color = glm::vec4(0, 0, 0, 0.5));
        virtual ~GOPrimitive() = default;
        static void Remove(const uint32_t& id);

        uint32_t GenerateId();
        inline const uint32_t GetId() const { return m_Id; }

        inline GOCategory GetCategory() const { return m_Category; }
        inline bool IsVisible() const { return m_IsVisible; }
        inline glm::vec4 GetColor() const { return m_Color; }
        inline bool GetState() { return m_State; }
        inline GOTypeFlags GetType() { return m_Type; }

        inline void SetVisibility(bool isVisible) { m_IsVisible = isVisible; }
        inline void SetColor(glm::vec4 color) { m_Color = color; }
        inline void SetState(bool state) { m_State = state; }

        inline float GetWeight() const { return m_Weight; }
        inline void SetWeight(float weight) { m_Weight = weight; }

    protected:
        uint32_t m_Id;
        GOCategory m_Category;
        bool m_IsVisible;
        glm::vec4 m_Color;
        bool m_State;
        GOTypeFlags m_Type;
        float m_Weight = GOWeight::Default;
    };



    class GOPoint : public GOPrimitive
    {
    public:
        GOPoint(float x, float y, float z);
        GOPoint(glm::vec3 position);
        static uint32_t Add(float x, float y, float z);
        static uint32_t Add(glm::vec3 position);

        virtual ~GOPoint() = default;

        static std::shared_ptr<GOPoint> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOPoint>> GetAll();

        inline glm::vec3 GetPosition() const { return m_Position; }
        inline void SetPosition(glm::vec3 position) { m_Position = position; }
        inline float X() const { return m_Position.x; }
        inline float Y() const { return m_Position.y; }
        inline float Z() const { return m_Position.z; }
        inline void SetX(float x) { m_Position.x = x; }
        inline void SetY(float y) { m_Position.y = y; }
        inline void SetZ(float z) { m_Position.z = z; }

        inline void setWeight(float weight) { m_Weight = weight; }

        operator glm::vec3() const { return m_Position; }

    private:
        glm::vec3 m_Position;
    };


    class GOLine : public GOPrimitive
    {
    public:
        GOLine(GOPoint p1, GOPoint p2, float weight = GOWeight::Default);
        static uint32_t Add(GOPoint p1, GOPoint p2, float weight = GOWeight::Default);
        
        virtual ~GOLine() = default;

        static std::shared_ptr<GOLine> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOLine>> GetAll();

        inline GOPoint GetPStart() const { return m_PStart; }
        inline GOPoint GetPEnd() const { return m_PEnd; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
    };


    class GOCircle : public GOPrimitive
    {
    public:
        GOCircle(GOPoint center, float radius);
        static uint32_t Add(GOPoint center, float radius);
        
        virtual ~GOCircle() = default;

        static std::shared_ptr<GOCircle> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOCircle>> GetAll();

        inline glm::vec3 GetNormal() const { return m_Normal; }
        inline GOPoint GetCenter() const { return m_Center; }
        inline float GetRadius() const { return m_Radius; }
        inline glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

    private:
        GOPoint m_Center;
        glm::vec3 m_Normal = glm::vec3(0, 0, 1);
        glm::vec4 m_EdgeColor = glm::vec4(1, 0, 0, 1);
        float m_Radius;
    };


    class GOCylinder : public GOPrimitive
    {
    public:
        GOCylinder(GOPoint p1, GOPoint p2, float radius);
        static uint32_t Add(GOPoint p1, GOPoint p2, float radius);

        virtual ~GOCylinder() = default;

        static std::shared_ptr<GOCylinder> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOCylinder>> GetAll();

        GOPoint GetPStart() const { return m_PStart; }
        GOPoint GetPEnd() const { return m_PEnd; }
        float GetRadius() const { return m_Radius; }
        glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
        float m_Radius;
        glm::vec4 m_EdgeColor = glm::vec4(0, 1, 1, 1);
    };


    class GOPolyline : public GOPrimitive
    {
    public:
        GOPolyline(std::vector<GOPoint> points);
        static uint32_t Add(std::vector<GOPoint> points);

        virtual ~GOPolyline() = default;

        static std::shared_ptr<GOPolyline> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOPolyline>> GetAll();

        inline const std::vector<GOPoint> &GetPoints() const { return m_Points; }

        inline bool IsClosed() const { return m_IsClosed; }

        inline void setWeight(float weight) { m_Weight = weight; }

    private:
        std::vector<GOPoint> m_Points;
        bool m_IsClosed = true;
        float m_Weight = GOWeight::Default;
    };


    class GOTriangle : public GOPrimitive
    {
    public:
        GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3);
        static uint32_t Add(GOPoint p1, GOPoint p2, GOPoint p3);

        virtual ~GOTriangle() = default;

        static std::shared_ptr<GOTriangle> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOTriangle>> GetAll();

        const std::vector<glm::vec3> GetVertices() const {
            return std::vector<glm::vec3>{m_P1.GetPosition(), m_P2.GetPosition(), m_P3.GetPosition()};
        }

        inline void setWeight(float weight) { m_Weight = weight; }

    private:
        GOPoint m_P1;
        GOPoint m_P2;
        GOPoint m_P3;
        float m_Weight = GOWeight::Default;
    };


    class GOMesh : public GOPrimitive
    {
    public:
        GOMesh();
        GOMesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);
        static uint32_t Add();
        static uint32_t Add(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);

        virtual ~GOMesh() = default;

        static std::shared_ptr<GOMesh> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOMesh>> GetAll();

        const std::vector<glm::vec3> GetVertices() const { return m_Vertices; }
        const std::vector<uint32_t> GetIndices() const { return m_Indices; }
        const std::vector<glm::vec3> GetNormals() const { return m_Normals; }
        const std::vector<glm::vec4> GetColors() const { return m_Colors; }
        void SetVertices(std::vector<glm::vec3> vertices) { m_Vertices = vertices; }
        void SetIndices(std::vector<uint32_t> indices) { m_Indices = indices; }
        void SetNormals(std::vector<glm::vec3> normals) { m_Normals = normals; }
        void SetColors(std::vector<glm::vec4> colors) { m_Colors = colors; }

    private:
        std::vector<glm::vec3> m_Vertices;
        std::vector<uint32_t> m_Indices;
        std::vector<glm::vec3> m_Normals;
        std::vector<glm::vec4> m_Colors;
    };


    class GOText : public GOPrimitive
    {
    public:
        GOText(std::string text, GOPoint anchor, double size);
        static uint32_t Add(std::string text, GOPoint anchor, double size);

        virtual ~GOText() = default;

        static std::shared_ptr<GOText> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOText>> GetAll();

        std::string GetText() const { return m_Text; }

    private:
        GOPoint m_Anchor;
        std::string m_Text;
        double m_Size;
    };
}