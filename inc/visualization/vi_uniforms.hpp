/**
 * @file
 * @brief  Униформы - значения, что можно передавать в шейдеры
 * @author https://github.com/Greggot/
 */

#pragma once
#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    void pass(unsigned int shader, Uniform uni, const glm::mat4& value) const
    {
        const auto name = operator[](uni);
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
    }

    void pass(unsigned int shader, Uniform uni, const glm::vec4& value) const
    {
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniform4fv(id, 1, glm::value_ptr(value));
    }

    void pass(unsigned int shader, Uniform uni, const glm::vec3& value) const
    {
        auto id = glGetUniformLocation(shader, operator[](uni));
        glUniform3fv(id, 1, glm::value_ptr(value));
    }
} uniforms;
