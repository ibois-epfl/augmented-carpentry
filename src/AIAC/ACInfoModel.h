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

class TimberInfo{
public:
    struct Hole{
        ACIMState m_State;
        std::string m_ID;
        glm::vec3 m_Start;
        bool m_StartAccessible;
        glm::vec3 m_End;
        bool m_EndAccessible;
        double m_Radius;
        std::set<std::string> m_Neighbors;
        std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitives;
    };
    struct Cut{
        struct Face{
            ACIMState m_State;
            std::string m_ID;
            bool m_Accessible;
            glm::vec3 m_Normal;
            glm::vec3 m_Center;
            std::set<std::string> m_Edges;
            std::set<std::string> m_Neighbors;
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitives;
        };
        struct Edge{
            std::string m_ID;
            bool m_Accessible;
            glm::vec3 m_Start;
            glm::vec3 m_End;
            std::set<std::string> m_Neighbors;
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitives;
        };
        ACIMState m_State;
        std::string m_ID;
        std::map<std::string, Face> m_Faces;
        std::map<std::string, Edge> m_Edges;
    };

    std::string GetID() const { return m_ID; }
    std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }

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

    friend class ACInfoModel;
};

class ACInfoModel
{
public:
    ACInfoModel(){};
    ~ACInfoModel(){};

    /**
     * @brief Load a .ply model from a file.
     * @param path Path to the model file.
     */
    void Load(std::string path);

    /**
     * @brief Get the TimberInfo object
     */
    TimberInfo GetTimberInfo();

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

    TimberInfo m_TimberInfo;

    std::vector<std::shared_ptr<GOLine>> m_BboxGOLines;
};

}
