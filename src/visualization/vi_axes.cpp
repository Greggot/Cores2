/**
 * @file
 * @brief  Отображение осей координат
 * @author https://github.com/Greggot/
 */

#include "visualization/vi_axes.hpp"
#include "geometry/gm_types.hpp"
#include "visualization/vi_uniforms.hpp"

namespace vi {

void Axes::draw()
{
    if (!is_initialized) {
        initialize();
        is_initialized = true;
    }

    glDisable(GL_DEPTH_TEST);
    bind_vertex_array();

    shader_holer().apply(Shader::axis);
    uniforms.pass(shader_holer().at(Shader::axis), Uniform::model, mvp());

    glLineWidth(3);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
}

void Axes::initialize()
{
    const gm::vector4 axis { 0, 0, 0, 0.5 };
    const gm::matrix3x4 vertices { axis, axis, axis };
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
    generate_vertex_buffer(0, gm::data(vertices), sizeof(vertices));
}

} // namespace vi
