/**
 * @file
 * @brief  Хранитель программ-шейдеров
 * @author https://github.com/Greggot/
 */

#pragma once

#include "visualization/vi_shader_compiler.hpp"
#include <array>
#include <optional>
#include <string_view>

namespace vi {

/// @brief Перечисление всевозможных применяемых шейдеров
enum class Shader {
    mesh, /// Меш, у каждой вершины которого есть нормаль и цвет
    axis, /// Трехцветные координатные оси
    size
};

/// @brief  Хранитель программ-шейдеров. Через него можно применить шейдер,
/// а также получить @ref vi::Shader_compiler, чтобы настроить сборку.
class Shader_holder {
public:
    Shader_holder():
        programs()
    {
        programs.fill(0);
    }

    void apply(Shader shader) const
    {
        glUseProgram(programs.at(static_cast<size_t>(shader)));
    }

    unsigned int at(Shader shader) const
    {
        return programs.at(static_cast<size_t>(shader));
    }

    template <Shader shader>
    void allocate(std::optional<std::string_view> vertex,
        std::optional<std::string_view> fragment = std::nullopt,
        std::optional<std::string_view> geometry = std::nullopt)
    {
        constexpr auto shader_id = static_cast<size_t>(shader);
        static_assert(shader_id < static_cast<size_t>(Shader::size), "Incorrect shader enumeration");
        programs.at(shader_id) = shader_compiler.build_shader(vertex, geometry, fragment);
    }

    Shader_compiler& compiler() { return shader_compiler; }

private:
    std::array<unsigned int, static_cast<size_t>(Shader::size)> programs;
    Shader_compiler shader_compiler;
};

} // namespace vi
