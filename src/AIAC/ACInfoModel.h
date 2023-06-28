#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <glm/glm.hpp>
#include "AIAC/GOSys/GOPrimitive.h"
#include "pugixml.hpp"

namespace AIAC{
class TimberInfo{
public:
    struct Drill{
        std::string id;
        glm::vec3 start;
        glm::vec3 end;
        double radius;
        std::vector<GOPrimitive> objsToRender;
    };
    struct Face{
        std::string id;
        bool exposed;
        glm::vec3 normal;
        glm::vec3 center;
        std::set<std::string> lines;
        std::set<std::string> neighbors;
        std::vector<GOPrimitive> objsToRender;
    };
    struct Line{
        std::string id;
        bool exposed;
        glm::vec3 start;
        glm::vec3 end;
        std::set<std::string> neighbors;
        std::vector<GOPrimitive> objsToRender;
    };
    struct Cut{
        std::string id;
        std::map<std::string, Face> faces;
        std::map<std::string, Line> lines;
    };

    std::string GetID() const { return m_ID; }
    std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }
    bool IsExecuted() const { return m_Executed; }

private:
    std::string m_ID;
    std::vector<glm::vec3> m_Bbox;
    bool m_Executed = false; // TODO: states instead of executed?
    std::map<std::string, Drill> m_Drills;
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
     * @brief Get all TimberInfo IDs
     */
    std::vector<std::string> GetTimberIDs() const;

    /**
     * @brief Get the TimberInfo object
     */
    TimberInfo GetTimberInfo(std::string timberID);

    /**
     * @brief Get the active TimberInfo object
     */
    TimberInfo GetActiveTimberInfo() { return GetTimberInfo(m_CurrentActiveTimberID); }

    /**
     * @brief Set the active TimberInfo object
     */
    void SetActiveTimberInfo(std::string timberID) { m_CurrentActiveTimberID = timberID; }

private:
    std::map<std::string, TimberInfo> m_TimberInfo;
    std::string m_CurrentActiveTimberID;
};

}
