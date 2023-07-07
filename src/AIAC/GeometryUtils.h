# pragma once
# include <glm/glm.hpp>

namespace AIAC{
    /**
     * @brief Get the rotation matrix associated with counterclockwise rotation about
     * the given axis by theta radians.
     *
     * @param axis The axis of rotation.
     * @param theta The angle of rotation in radians.
     *
     * @return The rotation matrix.
     */
    glm::mat3x3 GetRotationMatrix(glm::vec3 axis, float theta);

    /**
     * @brief Get the translation matrix associated with the given translation vector
     * 
     * @param translationVector The translation vector
     * 
     * @return The translation matrix
    */
    glm::mat4x4 GetTranslationMatrix(glm::vec3 translationVector);

    /**
     * @brief Get the rigid transformation matrix from two correlated set of 3D points
     * @praam srcPts The source points
     * @param dstPts The destination points
     */
    glm::mat4x4 GetRigidTransformationMatrix(std::vector<glm::vec3> srcPts, std::vector<glm::vec3> dstPts);
}