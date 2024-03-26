/**
 * @file
 * @brief  Униформы - значения, что можно передавать в шейдеры
 * @author https://github.com/Greggot/
 */

#pragma once
#include "geometry/gm_types.hpp"
#include <GL/glew.h>
#include <array>
#include <string_view>

enum class Uniform {
    model,
    view,
    projection,
    color,
};

static const struct Uniforms {
    std::array<std::string_view, 4> unifrom_names { "model", "view", "projection", "color" };
    const char* operator[](Uniform uni) const { return std::data(unifrom_names[(int)uni]); }

    void pass(unsigned int shader, Uniform uni, const gm::matrix4& value) const
    {
        const auto name = operator[](uni);
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniformMatrix4fv(id, 1, GL_FALSE, gm::data(value));
    }

    void pass(unsigned int shader, Uniform uni, const gm::vector4& value) const
    {
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniform4fv(id, 1, gm::data(value));
    }

    void pass(unsigned int shader, Uniform uni, const gm::vector3& value) const
    {
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniform3fv(id, 1, gm::data(value));
    }
} uniforms;
