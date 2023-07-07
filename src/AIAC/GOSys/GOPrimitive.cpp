#include "aiacpch.h"

#include "AIAC/Log.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Application.h"


namespace AIAC
{
    static const float WEIGHT_TO_CYLINDER_RADIUS_RATE = 1.0 / 20.0f;

    GOPrimitive::GOPrimitive(bool isVisible, glm::vec4 color)
        : m_IsVisible(isVisible), m_Color(color), m_State(false)
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

    void GOPrimitive::Remove(const std::shared_ptr<GOPrimitive>& ptrGO)
    {
        AIAC_GOREG->Unregister(ptrGO->GetId());
    }


    GOPoint::GOPoint(float x, float y, float z, float weight)
    {
        m_Position = glm::vec3(x, y, z);
        m_Type = GOTypeFlags::_GOPoint;
        m_Weight = weight;
    }

    GOPoint::GOPoint(glm::vec3 position, float weight)
        : m_Position(position)
    {
        m_Type = GOTypeFlags::_GOPoint;
        m_Weight = weight;
    }

    std::shared_ptr<GOPoint> GOPoint::Add(float x, float y, float z, float weight)
    {
        auto ptrGO = std::make_shared<GOPoint>(GOPoint(x, y, z, weight));
        ptrGO->InitGLObject();
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    std::shared_ptr<GOPoint> GOPoint::Add(glm::vec3 position, float weight)
    {
        auto ptrGO = std::make_shared<GOPoint>(GOPoint(position, weight));
        ptrGO->InitGLObject();
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    void GOPoint::InitGLObject()
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec4> colors;
        vertices.push_back(m_Position);
        colors.push_back(m_Color);
        m_GLObjects.push_back(std::make_shared<GLPointObject>(vertices, colors, m_Weight));
    }

    std::shared_ptr<GOPoint> GOPoint::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOPoint>(id);
    }

    std::vector<std::shared_ptr<GOPoint>> GOPoint::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOPoint>();
    }


    GOLine::GOLine(GOPoint p1, GOPoint p2, float weight)
        : m_PStart(p1), m_PEnd(p2)
    {
        m_Weight = weight;
        m_Type = GOTypeFlags::_GOLine;
    }

    std::shared_ptr<GOLine> GOLine::Add(GOPoint p1, GOPoint p2, float weight)
    {
        auto ptrGO = std::make_shared<GOLine>(GOLine(p1, p2, weight));
        ptrGO->InitGLObject();
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    void GOLine::InitGLObject()
    {
        std::vector<glm::vec3> vertices;
        vertices.push_back(m_PStart.GetPosition());
        vertices.push_back(m_PEnd.GetPosition());
        m_GLObjects = CreatePolyline(vertices, false, m_Color, m_Weight);

        // if (m_Weight <= 1.0f) {
        //     std::vector<glm::vec4> colors;
        //     colors.push_back(m_Color);
        //     colors.push_back(m_Color);
        //     m_GLObjects.push_back(std::make_shared<GLLineObject>(vertices, colors, m_Weight));
        // } else {
        //     float radius = m_Weight * WEIGHT_TO_CYLINDER_RADIUS_RATE;
        //     m_GLObjects = CreateCylinder(m_PStart.GetPosition(), m_PEnd.GetPosition(), radius,
        //                                  m_Color, m_Color);
        // }
    }

    std::shared_ptr<GOLine> GOLine::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOLine>(id);
    }

    std::vector<std::shared_ptr<GOLine>> GOLine::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOLine>();
    }


    GOCircle::GOCircle(GOPoint center, float radius)
        : m_Center(center), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCircle;
    }

    std::shared_ptr<GOCircle> GOCircle::Add(GOPoint center, float radius)
    {
        auto ptrGO = std::make_shared<GOCircle>(GOCircle(center, radius));
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    std::shared_ptr<GOCircle> GOCircle::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOCircle>(id);
    }

    std::vector<std::shared_ptr<GOCircle>> GOCircle::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOCircle>();
    }


    GOCylinder::GOCylinder(GOPoint p1, GOPoint p2, float radius)
        : m_PStart(p1), m_PEnd(p2), m_Radius(radius)
    {
        m_Type = GOTypeFlags::_GOCylinder;
    }

    std::shared_ptr<GOCylinder> GOCylinder::Add(GOPoint p1, GOPoint p2, float radius)
    {
        auto ptrGO = std::make_shared<GOCylinder>(GOCylinder(p1, p2, radius));
        ptrGO->InitGLObject();
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    void GOCylinder::InitGLObject(){
        m_GLObjects = CreateCylinder(m_PStart.GetPosition(), m_PEnd.GetPosition(), m_Radius,
                                     m_Color, m_Color);
    }

    std::shared_ptr<GOCylinder> GOCylinder::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOCylinder>(id);
    }

    std::vector<std::shared_ptr<GOCylinder>> GOCylinder::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOCylinder>();
    }


    GOPolyline::GOPolyline(std::vector<GOPoint> points)
        : m_Points(points)
    {
        m_Type = GOTypeFlags::_GOPolyline;
    }

    std::shared_ptr<GOPolyline> GOPolyline::Add(std::vector<GOPoint> points)
    {
        auto ptrGO = std::make_shared<GOPolyline>(GOPolyline(points));
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    void GOPolyline::InitGLObject() {
        m_GLObjects = CreatePolyline(m_Points, m_IsClosed, m_Color, m_Weight);
    }

    std::shared_ptr<GOPolyline> GOPolyline::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOPolyline>(id);
    }

    std::vector<std::shared_ptr<GOPolyline>> GOPolyline::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOPolyline>();
    }

    GOTriangle::GOTriangle(GOPoint p1, GOPoint p2, GOPoint p3)
        : m_P1(p1), m_P2(p2), m_P3(p3)
    {
        m_Type = GOTypeFlags::_GOTriangle;
    }

    void GOTriangle::InitGLObject() {
        std::vector<uint32_t> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec4> colors;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        vertices.push_back(m_P1.GetPosition());
        vertices.push_back(m_P2.GetPosition());
        vertices.push_back(m_P3.GetPosition());
        colors.push_back(m_Color);
        colors.push_back(m_Color);
        colors.push_back(m_Color);
        m_GLObjects.push_back(std::make_shared<GLMeshObject>(vertices, colors, indices));
    }

    std::shared_ptr<GOTriangle> GOTriangle::Add(GOPoint p1, GOPoint p2, GOPoint p3)
    {
        auto ptrGO = std::make_shared<GOTriangle>(GOTriangle(p1, p2, p3));
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    std::shared_ptr<GOTriangle> GOTriangle::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOTriangle>(id);
    }

    std::vector<std::shared_ptr<GOTriangle>> GOTriangle::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOTriangle>();
    }


    GOMesh::GOMesh()
    {
        m_Type = GOTypeFlags::_GOMesh;
    }

    GOMesh::GOMesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices, std::vector<glm::vec3> normals, std::vector<glm::vec4> colors)
        : m_Vertices(vertices), m_Indices(indices), m_Normals(normals), m_Colors(colors)
    {
        m_Type = GOTypeFlags::_GOMesh;
    }

    GOMesh::InitGLObject(){
        m_GLObjects = GLMeshObject(m_Vertices, m_Indices, m_Normals, m_Colors);
    }

    std::shared_ptr<GOMesh> GOMesh::Add()
    {
        auto ptrGO = std::make_shared<GOMesh>(GOMesh());
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    std::shared_ptr<GOMesh> GOMesh::Add(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
    {
        auto ptrGO = std::make_shared<GOMesh>(GOMesh(vertices, indices));
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    uint32_t GOMesh::LoadPly(std::string path){
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices);
        if( !scene) {
            fprintf( stderr, importer.GetErrorString());
            getchar();
            return false;
        }

        const aiMesh* mesh = scene->mMeshes[0]; // TODO: here we use only the 1st mesh, make more?

        auto ptrGO = std::make_shared<GOMesh>(GOMesh());

        ptrGO->m_Vertices.reserve(mesh->mNumVertices);
        for(unsigned int i=0; i<mesh->mNumVertices; i++){
            aiVector3D pos = mesh->mVertices[i];
            ptrGO->m_Vertices.emplace_back(pos.x, pos.y, pos.z);
        }

        ptrGO->m_Indices.reserve(mesh->mNumFaces * 3);
        for(unsigned int i=0; i<mesh->mNumFaces; i++){
            aiFace face = mesh->mFaces[i];
            ptrGO->m_Indices.push_back(face.mIndices[0]);
            ptrGO->m_Indices.push_back(face.mIndices[1]);
            ptrGO->m_Indices.push_back(face.mIndices[2]);
        }

//        if(mesh->mNormals != nullptr){
//            ptrGO->m_Normals.reserve(mesh->mNumVertices);
//            for(unsigned int i=0; i<mesh->mNumVertices; i++){
//                aiVector3D norm = mesh->mNormals[i];
//                ptrGO->m_Normals.emplace_back(norm.x, norm.y, norm.z);
//            }
//        }
//
//        if(mesh->mColors != nullptr){
//            ptrGO->m_Colors.reserve(mesh->mNumVertices);
//            for(unsigned int i=0; i<mesh->mNumVertices; i++){
//                aiColor4D color = mesh->mColors[0][i];
//                ptrGO->m_Colors.emplace_back(color.r, color.g, color.b, color.a);
//            }
//        }

        uint32_t idGO = ptrGO->GetId();
        AIAC_GOREG->Register(idGO, ptrGO);
        return idGO;
    }

    std::shared_ptr<GOMesh> GOMesh::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOMesh>(id);
    }

    std::vector<std::shared_ptr<GOMesh>> GOMesh::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOMesh>();
    }


    GOText::GOText(std::string text, GOPoint anchor, double size)
        : m_Text(text), m_Anchor(anchor), m_Size(size)
    {
        m_Anchor.SetVisibility(false);
        m_Type = GOTypeFlags::_GOText;
    }

    std::shared_ptr<GOText> GOText::Add(std::string text, GOPoint anchor, double size)
    {
        auto ptrGO = std::make_shared<GOText>(GOText(text, anchor, size));
        AIAC_GOREG->Register(ptrGO);
        return ptrGO;
    }

    // std::shared_ptr<GOText> GOText::Add(std::string text, glm::vec3 anchor, double size)
    // {
    //     auto ptrGO = std::make_shared<GOText>(GOText(text, anchor, size));
    //     uint32_t idGO = ptrGO->GetId();
    //     AIAC_GOREG->Register(idGO, ptrGO);
    //     return idGO;
    // }

    std::shared_ptr<GOText> GOText::Get(const uint32_t& id)
    {
        return AIAC_GOREG->GetGO<GOText>(id);
    }

    std::vector<std::shared_ptr<GOText>> GOText::GetAll()
    {
        return AIAC_GOREG->GetAllGOs<GOText>();
    }
}