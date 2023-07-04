#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <glm/glm.hpp>
#include "AIAC/GOSys/GOPrimitive.h"
#include "pugixml.hpp"

namespace AIAC{
class ScannedModel{
public:
    ScannedModel(){};
    ~ScannedModel(){};

    /**
     * @brief Load a .ply model from a file.
     * @param path Path to the model file.
     */
    void Load(std::string path);

    /**
     * @brief Build the bounding box based on the ply model.
     */
    void BuildBoundingBox();

    /**
     * @brief Update Boundary Box GOLine
     */
    void UpdateBboxGOLine();

private:
    uint32_t m_MeshID;
    std::vector<glm::vec3> m_Bbox;
    std::vector<std::shared_ptr<GOPrimitive>> m_BboxGOLineIDs;
};

}
