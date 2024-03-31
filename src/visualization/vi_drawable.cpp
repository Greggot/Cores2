/**
 * @file
 * @brief  Интерфейс объекта, что можно отрисовывать
 * @author https://github.com/Greggot/
 */

#include "visualization/vi_drawable.hpp"
#include "application/app_application.hpp"

namespace vi {

vi::Shader_holder& Drawable::shader_holer()
{
    return app::application().shader_holder();
}
const vi::Shader_holder& Drawable::shader_holer() const
{
    return app::application().shader_holder();
}

unsigned int Drawable::generate_vertex_buffer(unsigned int layout, const float* data, long size)
{
    unsigned int vbo { 0 };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferStorage(GL_ARRAY_BUFFER, size, data, GL_MAP_READ_BIT);
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(layout);
    return vbo;
}
unsigned int Drawable::generate_index_buffer(const unsigned int* indexes, long size)
{
    unsigned int ebo { 0 };
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_MAP_READ_BIT);
    return ebo;
}
void Drawable::generate_vertex_array()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}
void Drawable::bind_vertex_array() const
{
    glBindVertexArray(vao);
}

} // namespace vi
