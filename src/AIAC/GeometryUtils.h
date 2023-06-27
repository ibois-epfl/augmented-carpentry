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
    glm::mat3x3 GetRotationMatrix(glm::vec3 axis, float theta){
        // normalize axis
        axis = glm::normalize(axis);

        float a = cos(theta / 2.0f);
        float b = -axis.x * sin(theta / 2.0f);
        float c = -axis.y * sin(theta / 2.0f);
        float d = -axis.z * sin(theta / 2.0f);
        float aa = a * a;
        float bb = b * b;
        float cc = c * c;
        float dd = d * d;
        float bc = b * c;
        float ad = a * d;
        float ac = a * c;
        float ab = a * b;
        float bd = b * d;
        float cd = c * d;

        glm::mat3x3 mat;
        mat[0][0] = aa + bb - cc - dd;
        mat[0][1] = 2 * (bc + ad);
        mat[0][2] = 2 * (bd - ac);
        mat[1][0] = 2 * (bc - ad);
        mat[1][1] = aa + cc - bb - dd;
        mat[1][2] = 2 * (cd + ab);
        mat[2][0] = 2 * (bd + ac);
        mat[2][1] = 2 * (cd - ab);
        mat[2][2] = aa + dd - bb - cc;

        return mat;
    }
}