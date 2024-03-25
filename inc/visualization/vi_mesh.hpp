/**
 * @file
 * @brief  Отображение меша - полигнальной модели из треугольников
 * @author https://github.com/Greggot/
 */

#pragma once

#include "visualization/vi_drawable.hpp"
#include "visualization/vi_uniforms.hpp"
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vi {

///
struct Triangle {
    std::array<glm::vec3, 3> vertices;

    Triangle(glm::vec3 i, glm::vec3 j, glm::vec3 k):
        vertices()
    {
        vertices.at(0) = i;
        vertices.at(1) = j;
        vertices.at(2) = k;
    }

    glm::vec3 normal() const
    {
        return glm::normalize(
            glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[1]));
    }
};

/// @brief Отображение меша. Треугольники представлены последовательностью
/// вершин, индексы не используются. Удобно при работе с файлами STL.
/// @todo Добавить передачу матриц для рендера в пространстве
class Mesh_strip : public Drawable {
public:
    Mesh_strip() = default;

    /// @todo Убрать тестовый поворот
    void draw() override
    {
        if (vertices.empty())
            return;

        bind_vertex_array();
        shader_holer().apply(Shader::mesh);
        uniforms.pass(shader_holer().at(Shader::mesh), Uniform::model, model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * vertices.size());

        model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 0, 1));
    }

    /// @brief Добавить треугольник в конец очереди
    /// @todo Добавить пересчет нормалей для вершин
    void add_triangle(const Triangle& triangle)
    {
        vertices.insert(vertices.end(),
            triangle.vertices.begin(), triangle.vertices.end());
    }

    /// @brief Создать буфер из вершин по набору заданных треугольников
    void apply()
    {
        if (vertices.empty())
            return;
        const auto* vertices_ptr = glm::value_ptr(vertices.front());
        generate_vertex_buffer(0, vertices_ptr, long(vertices.size() * sizeof(glm::vec3)));
    }

private:
    std::vector<glm::vec3> vertices;
    glm::mat4 model { 1.0 };
};

} // namespace vi
