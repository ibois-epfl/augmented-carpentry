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
     * @brief Get the bounding box of the ply model.
     * @return The bounding box of the ply model.
     */
    std::vector<glm::vec3> GetBoundingBox() const { return m_Bbox; }

    /**
     * @brief Update Boundary Box GOLine
     */
    void UpdateBboxGOLine();

    /**
     * @brief Get the length of the scanned model, which is calculated by averaging the four edges of the bounding box.
     * @return The length of the scanned model. (in TSLAM unit)
     */
    float GetLength();

private:
    std::shared_ptr<GOMesh> m_Mesh;
    std::vector<glm::vec3> m_Bbox;
    std::vector<std::shared_ptr<GOLine> > m_BboxGOLines;
};

}
