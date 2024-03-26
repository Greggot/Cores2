/**
 * @file
 * @brief  Треугольник
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_types.hpp"
#include <array>

namespace gm {

struct Triangle {
    std::array<vector3, 3> vertices;

    Triangle(vector3 i, vector3 j, vector3 k):
        vertices()
    {
        vertices.at(0) = i;
        vertices.at(1) = j;
        vertices.at(2) = k;
    }

    vector3 normal() const
    {
        return normalize(cross(vertices[1] - vertices[0], vertices[2] - vertices[1]));
    }
};

} // namespace gm
