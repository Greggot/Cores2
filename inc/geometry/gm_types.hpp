/**
 * @file
 * @brief  Прослойка для GLM
 * @author https://github.com/Greggot/
 */

#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

/// Геометрические примитивы
namespace gm {

template <class Scalar_t = float>
struct vector2 {
    Scalar_t x;
    Scalar_t y;
    vector2(Scalar_t x = { 0 }, Scalar_t y = { 0 }):
        x(x), y(y)
    { }
};
using vector3 = glm::vec3;
using vector4 = glm::vec4;
using matrix4 = glm::mat4;
using matrix3x4 = glm::mat3x4;

template <class Matrix_t>
auto data(Matrix_t& matrix)
{
    return glm::value_ptr(matrix);
}

inline vector3 cross(const vector3& left, const vector3& right)
{
    return glm::cross(left, right);
}

inline vector3 normalize(const vector3& vector)
{
    return glm::normalize(vector);
}

inline matrix4 rotate_radian(const matrix4& matrix, float angle, const vector3& axis)
{
    return glm::rotate(matrix, angle, axis);
}

inline matrix4 rotate_degree(const matrix4& matrix, float angle, const vector3& axis)
{
    return glm::rotate(matrix, glm::radians(angle), axis);
}

inline matrix4 view_matrix(const vector3& position, const vector3& target, const vector3& up)
{
    return glm::lookAt(position, target, up);
}

inline matrix4 projection_orthogonal(float width, float height, float depth)
{
    return glm::ortho(-width, width, -height, height, -depth / 2, depth / 2);
}

} // namespace gm
