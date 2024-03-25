/**
 * @file
 * @brief  Отображение осей координат
 * @author https://github.com/Greggot/
 */

#include "visualization/vi_axes.hpp"
#include "visualization/vi_uniforms.hpp"

namespace vi {

Axes::Axes():
    model(1.0)
{
    model = glm::lookAt(glm::vec3(0.5, 0, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}

void Axes::draw()
{
    if (!is_initialized) {
        initialize();
        is_initialized = true;
    }

    glDisable(GL_DEPTH_TEST);
    bind_vertex_array();

    shader_holer().apply(Shader::axis);
    uniforms.pass(shader_holer().at(Shader::axis), Uniform::model, model);
    
    glLineWidth(3);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
    model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 0, 1));
}

void Axes::initialize()
{
    const glm::vec4 axis { 0, 0, 0, 0.5 };
    const glm::mat3x4 vertices { axis, axis, axis };
    static constexpr std::array<unsigned int, 6> indexes {
        0,
        1,
        0,
        2,
        0,
        3,
    };

    generate_vertex_array();
    generate_index_buffer(std::data(indexes), sizeof(indexes));
    generate_vertex_buffer(0, glm::value_ptr(vertices), sizeof(vertices));
}

} // namespace vi
