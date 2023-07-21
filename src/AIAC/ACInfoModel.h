#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <glm/glm.hpp>
#include "AIAC/GOSys/GOPrimitive.h"
#include "pugixml.hpp"

namespace AIAC{

enum class ACIMState{
    NOT_DONE,
    CURRENT,
    DONE,
};

static std::map<ACIMState, glm::vec4> HOLE_AXIS_COLOR = {
    {ACIMState::NOT_DONE, glm::vec4(0.1f, 0.9f, 0.9f, 1.0f)},
    {ACIMState::CURRENT, glm::vec4(0.1f, 0.9f, 0.5f, 1.0f)},
    {ACIMState::DONE, glm::vec4(0.3f, 0.3f, 0.3f, 0.5f)}
};

static std::map<ACIMState, glm::vec4> HOLE_CYLINDER_COLOR = {
    {ACIMState::NOT_DONE, glm::vec4(0.1f, 0.9f, 0.9f, 0.2f)},
    {ACIMState::CURRENT, glm::vec4(0.1f, 0.9f, 0.5f, 0.2f)},
    {ACIMState::DONE, glm::vec4(0.3f, 0.3f, 0.3f, 0.2f)}
};

static std::map<ACIMState, glm::vec4> CUT_FACE_COLOR = {
    {ACIMState::NOT_DONE, glm::vec4(0.9f, 0.6f, 0.2f, 0.2f)},
    {ACIMState::CURRENT, glm::vec4(0.1f, 0.9f, 0.5f, 0.2f)},
    {ACIMState::DONE, glm::vec4(0.3f, 0.3f, 0.3f, 0.2f)}
};

static std::map<ACIMState, glm::vec4> CUT_EDGE_COLOR = {
    {ACIMState::NOT_DONE, glm::vec4(0.9f, 0.6f, 0.2f, 1.0f)},
    {ACIMState::CURRENT, glm::vec4(0.1f, 0.9f, 0.5f, 1.0f)},
    {ACIMState::DONE, glm::vec4(0.3f, 0.3f, 0.3f, 0.5f)}
};


class TimberInfo{
public:
    class Component {
    public:
        Component(std::string type) : m_Type(type) {}
        virtual void SetAsCurrent();
        virtual void SetAsDone();
        virtual void SetAsNotDone();

    public:
        bool IsMarkedDone; // This one is for UI

    public:  __always_inline
        std::string GetTypeString() const { return m_Type; }

    protected:
        ACIMState m_State;
        std::string m_Type;
        pugi::xml_node m_ACIMDocNode;
        std::string m_ID;
        std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitives;

    friend class ACInfoModel;
    friend class TimberInfo;
    };

    class Hole: public Component{
    public:
        Hole() : Component("HOLE") {}
    public:
        virtual void SetAsCurrent();
        virtual void SetAsDone();
        virtual void SetAsNotDone();

    public:  __always_inline
        std::shared_ptr<GOPoint> GetStartPointGO() { return m_StartPointGO; }
        std::shared_ptr<GOPoint> GetEndPointGO() { return m_EndPointGO; }

    private:
        glm::vec3 m_Start;
        bool m_StartExposed;
        glm::vec3 m_End;
        bool m_EndExposed;
        double m_Radius;
        std::set<std::string> m_Neighbors;

        // GOPrimitives
        std::shared_ptr<GOLine> m_AxisGO;
        std::shared_ptr<GOCylinder> m_CylinderGO;
        std::shared_ptr<GOPoint> m_StartPointGO;
        std::shared_ptr<GOPoint> m_EndPointGO;
        std::shared_ptr<GOText> m_RadiusLabelGO;
        std::shared_ptr<GOText> m_IDLabelGO;

        friend class ACInfoModel;
    };

    class Cut: public Component{
    public:
        Cut() : Component("CUT") {}

        virtual void SetAsCurrent();
        virtual void SetAsDone();
        virtual void SetAsNotDone();

        class Face: public Component{
        public:
            Face() : Component("FACE") {}
            bool IsExposed() const { return m_Exposed; }
            glm::vec3 GetNormal() const { return m_Normal; }
            glm::vec3 GetCenter() const { return m_Center; }
            std::set<std::string> GetEdges() const { return m_Edges; }
            std::set<std::string> GetNeighbors() const { return m_Neighbors; }
            std::vector<glm::vec3> GetCorners() const { return m_Corners; }

        private:
            virtual void SetAsCurrent();

            bool m_Exposed;
            glm::vec3 m_Normal;
            glm::vec3 m_Center;
            std::set<std::string> m_Edges;
            std::set<std::string> m_Neighbors;
            std::vector<glm::vec3> m_Corners;
            std::shared_ptr<GOMesh> m_GO;

            friend class Cut;
            friend class TimberInfo;
            friend class ACInfoModel;
        };
        class Edge: public Component{
        public:
            Edge() : Component("EDGE") {}

        private:
            virtual void SetAsCurrent();

            glm::vec3 m_Start;
            glm::vec3 m_End;
            std::set<std::string> m_Neighbors;
            std::shared_ptr<GOLine> m_GO;

            friend class Cut;
            friend class TimberInfo;
            friend class ACInfoModel;
        };

        inline Face& GetFace(std::string id) { return m_Faces[id]; }
        inline std::map<std::string, Face>& GetAllFaces() { return m_Faces; }
        inline std::map<std::string, Edge>& GetAllEdges() { return m_Edges; }
        inline glm::vec3 GetCenter() const { return m_Center; }
    
    private:
        std::map<std::string, Face> m_Faces;
        std::map<std::string, Edge> m_Edges;
        glm::vec3 m_Center;
        std::shared_ptr<GOText> m_IDLabelGO;

        friend class ACInfoModel;
    };

    inline std::string GetID() const { return m_ID; }
    std::vector<std::string> GetAllComponentsIDs() const;
    inline Component* GetComponent(std::string id) { return m_Components[id]; }
    inline Component* GetCurrentComponent() { 
        if(m_Components.find(m_CurrentComponentID) == m_Components.end())
            return nullptr;
        return m_Components[m_CurrentComponentID];
    }
    std::string GetCurrentComponentID() { return m_CurrentComponentID; }
    void SetCurrentComponentTo(std::string id);
    inline std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }

private:
    std::string m_ID;

    // The bounding box has this structure
    //
    //   (7)------------------------(6)
    //   / |                       / |  
    // (4)-----------------------(5) |
    //  |  |                      |  |
    //  | (3)---------------------|-(2)
    //  |/                        |/
    // (0)-----------------------(1)
    //
    std::vector<glm::vec3> m_Bbox;
    ACIMState m_State = ACIMState::NOT_DONE; // TODO: states instead of executed?
    std::map<std::string, Hole> m_Holes;
    std::map<std::string, Cut> m_Cuts;
    std::map<std::string, Component*> m_Components;  // FIXME: refactor with smart pointers
    std::string m_CurrentComponentID = "";

    friend class ACInfoModel;
};

class ACInfoModel
{
public:
    ACInfoModel(){};
    ~ACInfoModel(){};

    /**
     * @brief Load a .acim model from a file.
     * @param path Path to the model file.
     * @return true if the file is loaded successfully, false otherwise.
     */
    bool Load(std::string path);

    /**
     * @brief Save the current state to the loaded .acim file.
     */
    void Save();
    
    /**
     * @brief Get the pugi::xml_document object
     */
    inline pugi::xml_document& GetDoc() { return m_ACIMDoc; }

    /**
     * @brief Clear the loaded data.
     */
    void Clear();

    /**
     * @brief Get the TimberInfo object
     */
    inline TimberInfo& GetTimberInfo() { return m_TimberInfo; }

    /**
     * @brief Update the bounding box of the timber (use the current Active TimberInfo)
     */
    void UpdateBboxGOLine();

    /**
     * @brief transform all the GOPrimitive belonging to the ACInfoModel
     * @param transformMat transformation matrix
     */
    void TransformGOPrimitives(glm::mat4x4 transformMat);

    /**
     * @brief Get the length of the scanned model, which is calculated by averaging the four edges of the bounding box.
     * @return The length of the scanned model. (in TSLAM unit)
     */
    float GetLength();

    /**
     * @brief Convert string m_State to ACIMState
     * @param m_State ACIMState
     */
    static ACIMState StringToState(std::string m_State);

    /**
     * @brief Convert a string separated by space to glm::vec3
     * @param str string separated by space
     * @return glm::vec3
     */
    static glm::vec3 StringToVec3(std::string str);

    /**
     * @brief Convert a string separated by space to a list of string
     * @param str string separated by space
     * @return a std::vector<std::string>
     */
    static std::vector<std::string> StringToTokens(std::string str);

    /**
     * @brief Convert a string separated by space to a set of tokens
     * @param str string separated by space
     * @return a std::set<std::string>
     */
    static std::set<std::string> StringToSet(std::string str);

    /**
     * @brief Convert a string to bool
     * @param str string
     * @return bool
     */
    static bool StringToBool(std::string str);

private:
    float m_Scale = 50.0f;
    std::string m_FilePath;
    pugi::xml_document m_ACIMDoc;

    TimberInfo m_TimberInfo;

    std::vector<std::shared_ptr<GOLine>> m_BboxGOLines;
};

}
