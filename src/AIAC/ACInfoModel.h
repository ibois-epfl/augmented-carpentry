#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <glm/glm.hpp>

#include "pugixml.hpp"

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC{

enum class ACIMState{
    NOT_DONE,
    CURRENT,
    DONE
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

/**
 * @brief Convert a vec3 to String
 * @param vec3 vec3
 * @return string
 */
static std::string Vec3ToString(glm::vec3 vec3);

class TimberInfo{
public:
    class Component {
    public:
        Component(std::string type) : m_Type(type) {
            m_Scale = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
        }
        virtual void SetAsCurrent();
        virtual void SetAsDone();
        virtual void SetAsNotDone();
        virtual void SetVisibility(bool visible);
        virtual glm::vec3 GetCenter() const;

    public:
        bool IsMarkedDone; // This one is for UI

    public:  __always_inline
        std::string GetTypeString() const { return m_Type; }

    protected:
        float m_Scale; // When converting to SLAM world's coordinate, multiply this scale
        ACIMState m_State;
        std::string m_Type;
        pugi::xml_node m_ACIMDocNode;
        std::string m_ID;
        glm::vec3 m_Center;

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
        virtual void SetVisibility(bool visible);
        glm::vec3 GetCenter() const override { return (m_Start + m_End) * 0.5f; };
        void SwapStartEnd();


    public:  __always_inline
        std::shared_ptr<GOPoint> GetStartPointGO() { return m_StartPointGO; }
        std::shared_ptr<GOPoint> GetEndPointGO() { return m_EndPointGO; }

    public:  __always_inline
        double GetRadius() const { return m_Radius; }

    private:
        // These values uses original coordinate in xml file
        // i.e. not transformation (rotation / translation) is applied
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
        std::shared_ptr<GOText> m_IDLabelGO;

        friend class ACInfoModel;
    };

    class Cut: public Component{
    public:
        Cut() : Component("CUT") {}

        virtual void SetAsCurrent();
        virtual void SetAsDone();
        virtual void SetAsNotDone();
        virtual void SetVisibility(bool visible);
        glm::vec3 GetCenter() const override { return m_Center; };

        // Sub-class Face
        class Face: public Component{
        public:
            Face() : Component("FACE") {}
            glm::vec3 GetCenter() const override { return m_Center; };

            bool IsExposed() const { return m_Exposed; }
            glm::vec3 GetNormal() const { return m_Normal; }
            std::vector<glm::vec3> GetCorners() const { return m_Corners; }
            std::set<std::string> GetEdges() const { return m_Edges; }
            std::set<std::string> GetNeighbors() const { return m_Neighbors; }

        private:
            bool m_Exposed;
            glm::vec3 m_Normal;
            std::vector<glm::vec3> m_Corners;
            std::set<std::string> m_Edges;
            std::set<std::string> m_Neighbors;
            std::shared_ptr<GOMesh> m_GO;

            friend class Cut;
            friend class TimberInfo;
            friend class ACInfoModel;
        };

        // Sub-class Edge
        class Edge: public Component{
        public:
            GOPoint GetStartPt() { return m_GO->GetPStart(); }
            GOPoint GetEndPt() { return m_GO->GetPEnd(); }
            Edge() : Component("EDGE") {}

            /**
             * @brief Set the Cotas Visibility object
             * 
             * @param visible if true, the cotas will be visible
             */
            inline void SetCotasVisibility(bool visible) {
                for(auto& cota : m_Cotas) cota->SetVisibility(visible);
                for(auto& cotaLine : m_CotaLines) cotaLine->SetVisibility(visible);
                for(auto& cotaPt : m_CotaPts) cotaPt->SetVisibility(visible);
            }
            /**
             * @brief Clear the cotas
             * 
             */
            inline void ClearCotas() {
                m_Cotas.clear();
                m_CotaLines.clear();
                m_CotaPts.clear();
            }

        private:
            // These Start and End are original value (not transformed)
            glm::vec3 m_Start;
            glm::vec3 m_End;
            std::set<std::string> m_Neighbors;
            std::shared_ptr<GOLine> m_GO;

            /// @brief The visualization of the cotas/mesures
            std::vector<std::shared_ptr<GOText>> m_Cotas;
            std::vector<std::shared_ptr<GOLine>> m_CotaLines;
            std::vector<std::shared_ptr<GOPoint>> m_CotaPts;

            friend class Cut;
            friend class TimberInfo;
            friend class ACInfoModel;
        };

        inline bool IsSingleFace() const { return m_NonExposedFaceIDs.size() == 1; }
        inline Face& GetFace(std::string id) { return m_Faces[id]; }
        inline Edge& GetEdge(std::string id) { return m_Edges[id]; }
        inline std::map<std::string, Face>& GetAllFaces() { return m_Faces; }
        inline std::map<std::string, Edge>& GetAllEdges() { return m_Edges; }
        inline std::set<std::string>& GetAllNonExposedFaceIDs() { return m_NonExposedFaceIDs; }
        inline std::set<std::string>& GetAllNonExposedEdgeIDs() { return m_NonExposedEdgeIDs; }

        void HighlightFace(const std::string& faceId, glm::vec4 color = glm::vec4(0));
        inline std::string GetHighlightedFaceID() const { return m_HighlightedFaceID; }
        inline TimberInfo::Cut::Face GetHighlightedFace() { return m_Faces[m_HighlightedFaceID]; }
        
        inline std::map<std::string, Face> GetFaceNeighbors(std::string faceID) {
            std::map<std::string, Face> neighbors;
            for(auto& neighborID : m_Faces[faceID].m_Neighbors){
                neighbors[neighborID] = m_Faces[neighborID];
            }
            return neighbors;
        }
        inline std::map<std::string, Face> GetHighlightedFaceNeighbors() {
            return GetFaceNeighbors(m_HighlightedFaceID);
        }

        inline void SetVisibilityAllCotas(bool visible) {
            for(auto& edge : m_Edges){
                edge.second.SetCotasVisibility(visible);
            }
        }

    private:
        std::string m_HighlightedFaceID;
        std::map<std::string, Face> m_Faces;
        std::map<std::string, Edge> m_Edges;
        std::set<std::string> m_NonExposedFaceIDs;
        std::set<std::string> m_NonExposedEdgeIDs;
        std::shared_ptr<GOText> m_IDLabelGO;

        friend class ACInfoModel;
    };

    inline std::string GetID() const { return m_ID; }
    std::vector<std::string> GetAllComponentsIDs() const;

    inline Component* GetComponent(const std::string& id) { return m_Components[id]; }
    inline Component* GetCurrentComponent() { 
        if(m_Components.find(m_CurrentComponentID) == m_Components.end())
            return nullptr;
        return m_Components[m_CurrentComponentID];
    }
    std::string GetCurrentComponentID() { return m_CurrentComponentID; }
    void SetCurrentComponentTo(std::string id);
    void SetNextComponentAsCurrent();
    void SetPrevComponentAsCurrent();

    inline std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }
    inline std::vector<std::pair<int, int> > GetBboxEdgesIndices() const { return m_BboxEdgesIndices; }
    
    void HideAllComponentsExceptCurrent();
    void ShowAllComponents();
    void UpdateCotasVisibility(bool visible);

public: ///< small utilities to calculate the progress of fabrication
    /// @brief Get the number of fabricate components
    inline int GetFabricatedComponents() {
        int count = 0;
        for(auto& comp : m_Components){
            if(comp.second->m_State == ACIMState::DONE)
                count++;
        }
        return count;
    }
    /// @brief Get the total number of components
    inline int GetTotalComponents() { return m_Components.size(); }
    /// @brief Get the progress of fabrication in percentage
    inline float GetFabricationProgress() {
        return (float)GetFabricatedComponents() / GetTotalComponents() * 100;
    }

private:  ///< utils for visualization
    /**
     * @brief Transform the notation from .acim into more lightweight notation
     * for visuals (e.g. "Hole#1" -> "H1" and "Cut#1" -> "C1")
     * 
     * @param id the original id of the component
     * @return std::string the shortened id for visualization
     */
    std::string ShortenComponentID(std::string id);

public:
    bool IsShowingAllComponents = false;
    bool IsShowingCotas = false;

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
    std::vector<std::pair<int, int> > m_BboxEdgesIndices = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // bottom
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // top
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // vertical
    };
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
    ACInfoModel(){
        m_Scale = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
    };
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
     * @brief Get the filepath to the loaded ACInfoModel.
     */
    inline const std::string& GetFilePath() const { return m_FilePath; }

    /**
     * @brief Get the name of the loaded ACInfoModel without the extension.
     */
    inline const std::string GetName() const {
        auto nameWithExtension = m_FilePath.substr(m_FilePath.find_last_of("/\\") + 1);
        std::string nameWithoutExtension = nameWithExtension.substr(0, nameWithExtension.find_last_of("."));
        return nameWithoutExtension; }
    
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

    // /**
    //  * @brief Update the cotas
    //  */
    // void UpdateCotas();

    /**
     * @brief transform all the GOPrimitive belonging to the ACInfoModel
     * @param transformMat transformation matrix
     */
    void Transform(glm::mat4x4 transformMat);

    /**
     * @brief Get the length of the acim, which is calculated by averaging the four long edges of the bounding box.
     * @return The length of the acim bounding box. (in TSLAM unit)
     */
    float GetLength();

    /**
     * @brief Get the length of the acim, which is calculated by averaging the four long edges of the bounding box.
     * @return The length of the acim bounding box. (in Real World unit, meter)
     */
    inline float GetRealWorldLength() { return GetLength() / m_Scale; }

    /**
     * Set the visibility of bbox to true or false
     */
    void SetBboxVisibility(bool visible);

    /**
     * Increase / decrease real world length based on the measurement
     */
    void AddMeasuredBboxLength(const float diff);

    /**
     * Get the real world length of the bounding box (in Real World unit, meter)
     */
    inline float GetMeasuredBboxLength() const { return m_MeasuredBboxLength; };

    /**
     * Adjust the scale of the model based on the measured result
     */
    void AdjustScale();

private:
    float m_EdgeWeight = 1.1f;
    float m_LabelSize = 0.75f;

    float m_Scale;
    float m_MeasuredBboxLength;

    std::string m_FilePath;
    pugi::xml_document m_ACIMDoc;

    TimberInfo m_TimberInfo;

    std::vector<std::shared_ptr<GOLine>> m_BboxGOLines;
};

}
