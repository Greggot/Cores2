/**
 * @file
 * @brief  Отображение меша - полигнальной модели из треугольников
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_triangle.hpp"
#include "geometry/gm_types.hpp"
#include "visualization/vi_drawable.hpp"
#include "visualization/vi_uniforms.hpp"

namespace vi {

/// @brief Отображение меша. Треугольники представлены последовательностью
/// вершин, индексы не используются. Удобно при работе с файлами STL.
/// @todo Добавить передачу матриц для рендера в пространстве
class Mesh_strip : public Drawable {
public:
    Mesh_strip() = default;

    void draw() const override 
    {
        if (vertices.empty())
            return;

        bind_vertex_array();
        shader_holer().apply(Shader::mesh);
        uniforms.pass(shader_holer().at(Shader::mesh), Uniform::model, mvp());
        glDrawArrays(GL_TRIANGLES, 0, int(3 * vertices.size()));
    }

    /// @brief Добавить треугольник в конец очереди
    /// @todo Добавить пересчет нормалей для вершин
    void add_triangle(const gm::Triangle& triangle)
    {
        vertices.insert(vertices.end(),
            triangle.vertices.begin(), triangle.vertices.end());
    }

    /// @brief Создать буфер из вершин по набору заданных треугольников
    void apply()
    {
        if (vertices.empty())
            return;
        const auto* vertices_ptr = gm::data(vertices.front());
        generate_vertex_array();
        generate_vertex_buffer(0, vertices_ptr, long(vertices.size() * sizeof(gm::vector3)));
    }

private:
    std::vector<gm::vector3> vertices;
};

} // namespace vi
