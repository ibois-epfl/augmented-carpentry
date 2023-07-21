#pragma once

#include <utility>

#include "AIAC/Render/GLObject.h"
#include "AIAC/Base.h"
#include "glm/glm.hpp"

namespace AIAC
{
    struct GOColor
    {
        static constexpr glm::vec4 RED = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        static constexpr glm::vec4 GREEN = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        static constexpr glm::vec4 BLUE = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        static constexpr glm::vec4 YELLOW = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        static constexpr glm::vec4 MAGENTA = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
        static constexpr glm::vec4 CYAN = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        static constexpr glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        static constexpr glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        static constexpr glm::vec4 GRAY = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    };

    struct GOWeight
    {
        static constexpr float Default            = 1.01f;
        static constexpr float Bold               = 2.5f;
        static constexpr float Thick              = 5.0f;
        static constexpr float ExtraThick         = 10.0f;
        static constexpr float MaxThick           = 20.0f;
    };

    struct GOTextSize
    {
        static constexpr double Default            = 1.0;
        static constexpr double Small              = 2.5;
        static constexpr double Medium             = 5.0;
        static constexpr double Big                = 10.0;
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

    class GOPrimitive
    {
    public:
        explicit GOPrimitive(bool isVisible = true,
                             glm::vec4 color = glm::vec4(0, 0, 0, 1.0));
        virtual ~GOPrimitive() = default;
        static void Remove(const uint32_t& id);
        static void Remove(const std::shared_ptr<GOPrimitive>& ptrGO);

        uint32_t GenerateId();

        inline bool IsVisible() const { return m_IsVisible; }
        inline glm::vec4 GetColor() const { return m_Color; }
        inline bool GetState() { return m_State; }
        inline GOTypeFlags GetType() { return m_Type; }
        inline uint32_t GetId() { return m_Id; }

        inline void SetName(std::string name) { m_Name = std::move(name); }
        inline void SetVisibility(bool isVisible) { m_IsVisible = isVisible; }
        inline void SetColor(glm::vec4 color) { m_Color = color; InitGLObject();}
        inline void SetState(bool state) { m_State = state; }

        inline std::string GetName() const { return m_Name; }
        inline float GetWeight() const { return m_Weight; }
        inline int SetWeight(float weight) { m_Weight = weight; InitGLObject(); return m_Id;}

        virtual void Transform(const glm::mat4x4& transformMat) {};

        virtual void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) { AIAC_ERROR("Not Implemented"); };
        inline void Draw() { for(auto glObject : m_GLObjects) glObject->Draw(); }

        void ClearGLObject();
        virtual void InitGLObject() {}

    protected:
        std::string m_Name;
        uint32_t m_Id;
        bool m_IsVisible;
        glm::vec4 m_Color;
        bool m_State;
        GOTypeFlags m_Type;
        float m_Weight = GOWeight::Default;
        std::vector<std::shared_ptr<GLObject> > m_GLObjects;
    };


    class GOPoint : public GOPrimitive
    {
    public:
        GOPoint() = default;
        GOPoint(float x, float y, float z, float weight = GOWeight::Default);
        GOPoint(glm::vec3 position, float weight = GOWeight::Default);

    public:
        /**
         * @brief Add GOPoint to the scene.
         *
         * @param x X coordinate of the point.
         * @param y Y coordinate of the point.
         * @param z Z coordinate of the point.
         * @param weight Weight of the point.
         * @return uint32_t Id of the point.
         */
        static std::shared_ptr<GOPoint> Add(float x, float y, float z, float weight = GOWeight::Default);
        static std::shared_ptr<GOPoint> Add(glm::vec3 position, float weight = GOWeight::Default);

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

        inline void SetWeight(float weight) { m_Weight = weight; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            m_Position = transformMat * glm::vec4(m_Position, 1.0f);
            InitGLObject();
        }

        inline void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) /* override */ {
            auto ptrPoint = std::dynamic_pointer_cast<GOPoint>(ptrGO);
            if (ptrPoint != nullptr)
            {
                SetPosition(ptrPoint->GetPosition());
                InitGLObject();
                return;
            }
            AIAC_ERROR("Cannot set value from different type of primitive; The type is {}", ptrGO->GetType());
        }
        void InitGLObject();

        operator glm::vec3() const { return m_Position; }

    public:
        inline float DistanceTo(const GOPoint& point) const {
            return glm::distance(m_Position, point.m_Position);
        }

    private:
        glm::vec3 m_Position;

    friend class GOPrimitive;
    friend class GOLine;
    friend class GOCircle;
    friend class GOCylinder;
    friend class GOPolyline;
    friend class GOTriangle;
    friend class GOMesh;
    friend class GOText;
    };

    class GOLine : public GOPrimitive
    {
    private:
        GOLine(GOPoint p1, GOPoint p2, float weight = GOWeight::Default);

    public:
        /**
         * @brief Add GOLine to the scene.
         *
         * @param p1 First point of the line.
         * @param p2 Second point of the line.
         * @param weight Weight of the line.
         * @return uint32_t Id of the line.
         */
        static std::shared_ptr<GOLine> Add(GOPoint p1, GOPoint p2, float weight = GOWeight::Default);

        virtual ~GOLine() = default;

        static std::shared_ptr<GOLine> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOLine>> GetAll();

        inline GOPoint GetPStart() const { return m_PStart; }
        inline GOPoint GetPEnd() const { return m_PEnd; }
        inline void SetPStart(GOPoint pStart) { m_PStart = pStart; }
        inline void SetPEnd(GOPoint pEnd) { m_PEnd = pEnd; }
        inline void SetPts(GOPoint pStart, GOPoint pEnd) { m_PStart = pStart; m_PEnd = pEnd; }
        inline float GetLength() const { return glm::distance(m_PStart.GetPosition(), m_PEnd.GetPosition()); }

        /**
         * @brief Compute the angle between the current line object and another one
         * 
         * @param ptrGO2 the second line
         * @return float the angle in degrees
         */
        float ComputeAngle(std::shared_ptr<GOLine> ptrGO2);

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            m_PStart.Transform(transformMat);
            m_PEnd.Transform(transformMat);
            InitGLObject();
        }

        inline void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) /* override */ {
            auto ptrLine = std::dynamic_pointer_cast<GOLine>(ptrGO);
            if (ptrLine != nullptr)
            {
                SetPts(ptrLine->GetPStart(), ptrLine->GetPEnd());
                InitGLObject();
                return;
            }
            AIAC_ERROR("Cannot set value from different type of primitive; The type is {}", ptrGO->GetType());
        }
        void InitGLObject();

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;

    friend class GOPoint;
    };

    class GOCircle : public GOPrimitive
    {
    private:
        GOCircle(GOPoint center, float radius);
        GOCircle(GOPoint center, glm::vec3 normal, float radius);

    public:
        /**
         * @brief Add GOCircle to the scene.
         *
         * @param center Center of the circle.
         * @param radius Radius of the circle.
         * @return uint32_t Id of the circle.
         */
        static std::shared_ptr<GOCircle> Add(GOPoint center, float radius);
        static std::shared_ptr<GOCircle> Add(GOPoint center, glm::vec3 normal, float radius);

        virtual ~GOCircle() = default;

        static std::shared_ptr<GOCircle> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOCircle>> GetAll();

        inline glm::vec3 GetNormal() const { return m_Normal; }
        inline GOPoint GetCenter() const { return m_Center; }
        inline float GetRadius() const { return m_Radius; }
        inline glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

        inline void SetNormal(glm::vec3 normal) { m_Normal = normal; }
        inline void SetCenter(GOPoint center) { m_Center = center; }
        inline void SetRadius(float radius) { m_Radius = radius; }
        inline void SetEdgeColor(glm::vec4 edgeColor) { m_EdgeColor = edgeColor; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            m_Center.Transform(transformMat);
            m_Normal = glm::normalize(glm::vec3(transformMat * glm::vec4(m_Normal, 0.0f)));
            InitGLObject();
        }

        inline void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) /* override */ {
            auto ptrCircle = std::dynamic_pointer_cast<GOCircle>(ptrGO);
            if (ptrCircle)
            {
                SetCenter(ptrCircle->GetCenter());
                SetNormal(ptrCircle->GetNormal());
                SetRadius(ptrCircle->GetRadius());
                SetEdgeColor(ptrCircle->GetEdgeColor());
                InitGLObject();
                return;
            }
            AIAC_ERROR("Cannot set value from different type of primitive; The type is {}", ptrGO->GetType());
        }

        void InitGLObject();

    private:
        GOPoint m_Center;
        glm::vec3 m_Normal = glm::vec3(0, 0, 1);
        glm::vec4 m_EdgeColor = glm::vec4(1, 0, 0, 1);
        float m_Radius;

    friend class GOPoint;
    };

    class GOCylinder : public GOPrimitive
    {
    private:
        GOCylinder(GOPoint p1, GOPoint p2, float radius);

    public:
        /**
         * @brief Add GOCylinder to the scene.
         * 
         * @param p1 First point of the cylinder.
         * @param p2 Second point of the cylinder.
         * @param radius Radius of the cylinder.
         * @return uint32_t Id of the cylinder.
         */
        static std::shared_ptr<GOCylinder> Add(GOPoint p1, GOPoint p2, float radius);

        virtual ~GOCylinder() = default;

        static std::shared_ptr<GOCylinder> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOCylinder>> GetAll();

        GOPoint GetPStart() const { return m_PStart; }
        GOPoint GetPEnd() const { return m_PEnd; }
        float GetRadius() const { return m_Radius; }
        glm::vec4 GetEdgeColor() const { return m_EdgeColor; }

        void SetPStart(GOPoint pStart) { m_PStart = pStart; }
        void SetPEnd(GOPoint pEnd) { m_PEnd = pEnd; }
        void SetRadius(float radius) { m_Radius = radius; }
        void SetEdgeColor(glm::vec4 edgeColor) { m_EdgeColor = edgeColor; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            m_PStart.Transform(transformMat);
            m_PEnd.Transform(transformMat);
            InitGLObject();
        }

        inline void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) /* override */ {
            auto ptrCylinder = std::dynamic_pointer_cast<GOCylinder>(ptrGO);
            if (ptrCylinder)
            {
                SetPStart(ptrCylinder->GetPStart());
                SetPEnd(ptrCylinder->GetPEnd());
                SetRadius(ptrCylinder->GetRadius());
                SetEdgeColor(ptrCylinder->GetEdgeColor());
                InitGLObject();
                return;
            }
            AIAC_ERROR("Cannot set value from different type of primitive; The type is {}", ptrGO->GetType());
        }
        void InitGLObject();

    private:
        GOPoint m_PStart;
        GOPoint m_PEnd;
        float m_Radius;
        glm::vec4 m_EdgeColor = glm::vec4(0, 1, 1, 1);

    friend class GOPoint;
    };

    // FIXME: the polyline  is not renderered
    class GOPolyline : public GOPrimitive
    {
    private:
        GOPolyline(std::vector<GOPoint> points, bool isClosed = false, float weight = GOWeight::Default);

    public:
        /**
         * @brief Add GOPolyline to the scene.
         * 
         * @param points Points of the polyline.
         * @return uint32_t Id of the polyline.
         */
        static std::shared_ptr<GOPolyline> Add(std::vector<GOPoint> points, bool isClosed = false, float weight = GOWeight::Default);
        static std::shared_ptr<GOPolyline> Add(std::vector<glm::vec3> points, bool isClosed = false, float weight = GOWeight::Default);

        virtual ~GOPolyline() = default;

        static std::shared_ptr<GOPolyline> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOPolyline>> GetAll();

        inline const std::vector<GOPoint> &GetPoints() const { return m_Points; }

        inline bool IsClosed() const { return m_IsClosed; }

        inline void SetWeight(float weight) { m_Weight = weight; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            for (auto& point : m_Points) {
                point.Transform(transformMat);
            }
            InitGLObject();
        }

        GOPrimitive operator* (const glm::mat4x4& transformMat)
        {
            GOPolyline polyline = *this;
            polyline.Transform(transformMat);
            return polyline;
        }
        void InitGLObject();

    private:
        std::vector<GOPoint> m_Points;
        bool m_IsClosed = false;
        float m_Weight = GOWeight::Default;

    friend class GOPoint;
    };

    class GOTriangle : public GOPrimitive
    {
    private:
        GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3);

    public:
        /**
         * @brief Add GOTriangle to the scene.
         * 
         * @param p1 First point of the triangle.
         * @param p2 Second point of the triangle.
         * @param p3 Third point of the triangle.
         * @return uint32_t Id of the triangle.
         */
        static std::shared_ptr<GOTriangle> Add(GOPoint p1, GOPoint p2, GOPoint p3);

        virtual ~GOTriangle() = default;

        static std::shared_ptr<GOTriangle> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOTriangle>> GetAll();

        const std::vector<glm::vec3> GetVertices() const {
            return std::vector<glm::vec3>{m_P1.GetPosition(), m_P2.GetPosition(), m_P3.GetPosition()};
        }

        inline void SetWeight(float weight) { m_Weight = weight; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            m_P1.Transform(transformMat);
            m_P2.Transform(transformMat);
            m_P3.Transform(transformMat);
            InitGLObject();
        }

        GOPrimitive operator* (const glm::mat4x4& transformMat)
        {
            GOTriangle triangle = *this;
            triangle.Transform(transformMat);
            return triangle;
        }

        void InitGLObject();

    private:
        GOPoint m_P1;
        GOPoint m_P2;
        GOPoint m_P3;
        float m_Weight = GOWeight::Default;
    
    friend class GOPoint;
    };

    class GOMesh : public GOPrimitive
    {
    private:
        GOMesh();
        GOMesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices,
               std::vector<glm::vec3> normals = std::vector<glm::vec3>(),
               std::vector<glm::vec4> colors = std::vector<glm::vec4>());

    public:
        /**
         * @brief Add empty GOMesh to the scene.
         */
        static std::shared_ptr<GOMesh> Add();

        /**
         * @brief Add GOMesh to the scene.
         * 
         * @param vertices Vertices of the mesh.
         * @param indices Indices of the mesh.
         * @return uint32_t Id of the mesh.
         */
        static std::shared_ptr<GOMesh> Add(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);

        /**
         * @brief Load .ply and add the corresponding GOMesh to the scene.
         * @return uint32_t Id of the mesh.
         */
        static std::shared_ptr<GOMesh> LoadPly(std::string);

        virtual ~GOMesh() = default;

        static std::shared_ptr<GOMesh> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOMesh>> GetAll();

        const std::vector<glm::vec3> GetVertices() const { return m_Vertices; }
        const std::vector<uint32_t> GetIndices() const { return m_Indices; }
        const std::vector<glm::vec3> GetNormals() const { return m_Normals; }
        const std::vector<glm::vec4> GetColors() const { return m_Colors; }
        void SetVertices(std::vector<glm::vec3> vertices) { m_Vertices = vertices; InitGLObject(); }
        void SetIndices(std::vector<uint32_t> indices) { m_Indices = indices; InitGLObject(); }
        void SetNormals(std::vector<glm::vec3> normals) { m_Normals = normals; }
        void SetColors(std::vector<glm::vec4> colors) { m_Colors = colors; InitGLObject(); }
        void SetColor(glm::vec4 color) { m_Colors = std::vector<glm::vec4>(m_Vertices.size(), color); InitGLObject(); }
        // FIXME: override the SetColor function for Mesh
        
        void InitGLObject();
        

        inline void Transform(const glm::mat4x4& transformMat) /* override */ {
            // vertices
            for (auto& vertex : m_Vertices) {
                vertex = glm::vec3(transformMat * glm::vec4(vertex, 1.0f));
            }
            // normals
            for (auto& normal : m_Normals) {
                normal = glm::normalize(glm::vec3(transformMat * glm::vec4(normal, 0.0f)));
            }
            InitGLObject();
        }

        GOPrimitive operator* (const glm::mat4x4& transformMat)
        {
            GOMesh mesh = *this;
            mesh.Transform(transformMat);
            return mesh;
        }


    private:
        std::vector<glm::vec3> m_Vertices;
        std::vector<uint32_t> m_Indices;
        std::vector<glm::vec3> m_Normals;
        std::vector<glm::vec4> m_Colors;
    
    friend class GOPoint;
    };

    class GOText : public GOPrimitive
    {
    private:
        GOText(std::string text, GOPoint anchor, double size);

    public:
        /**
         * @brief Add GOText to the scene.
         * 
         * @param text Text of the text.
         * @param anchor Anchor of the text.
         * @param size Size of the text.
         * @return uint32_t Id of the text.
         */
        static std::shared_ptr<GOText> Add(std::string text, GOPoint anchor, double size = GOTextSize::Default);
        virtual ~GOText() = default;

        static std::shared_ptr<GOText> Get(const uint32_t& id);
        static std::vector<std::shared_ptr<GOText>> GetAll();

        inline const std::string GetText() const { return m_Text; }
        inline const GOPoint GetAnchor() const { return m_Anchor; }
        inline const double GetTextSize() const { return m_Size; }

        inline void SetText(const std::string text) { m_Text = text; }
        inline void SetAnchor(const GOPoint anchor) { m_Anchor = anchor; }
        inline void SetTextSize(const double size) { m_Size = size; }

        inline void Transform(const glm::mat4x4& transformMat) /* override */ { m_Anchor.Transform(transformMat); }
        
        inline void SetValueFrom(const std::shared_ptr<GOPrimitive>& ptrGO) /* override */ {
            auto ptrPoint = std::dynamic_pointer_cast<GOText>(ptrGO);
            if (ptrPoint != nullptr)
            {
                SetText(ptrPoint->GetText());
                SetAnchor(ptrPoint->GetAnchor());
                SetTextSize(ptrPoint->GetTextSize());
                InitGLObject();
                return;
            }
            AIAC_ERROR("Cannot set value from different type of primitive; The type is {}", ptrGO->GetType());
        }

        GOPrimitive operator* (const glm::mat4x4& transformMat)
        {
            GOText text = *this;
            text.Transform(transformMat);
            return text;
        }

    private:
        GOPoint m_Anchor;
        std::string m_Text;
        double m_Size;

    friend class GOPoint;
    };
}