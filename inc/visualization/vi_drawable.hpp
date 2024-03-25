/**
 * @file
 * @brief  Интерфейс объекта, что можно отрисовывать
 * @author https://github.com/Greggot/
 */

#pragma once
#include "visualization/vi_shader_holder.hpp"

/// @brief Визуальные объекты, привязанные к контексту рендера (OpenGL)
/// @todo Отделить низкоуровневые вызовы OpenGL, добавить альтернативу в виде Vulkan
namespace vi {

/// @brief  Интерфейс объекта, что можно отрисовывать
class Drawable {
public:
    Drawable() = default;
    Drawable(Drawable&&) = delete;
    Drawable(const Drawable&) = delete;
    Drawable& operator=(Drawable&&) = delete;
    Drawable& operator=(const Drawable&) = delete;
    virtual ~Drawable() = default;

    virtual void draw() = 0;

protected:
    vi::Shader_holder& shader_holer();
    const vi::Shader_holder& shader_holer() const;

    unsigned int generate_vertex_buffer(unsigned int layout, const float* data, long size);
    unsigned int generate_index_buffer(const unsigned int* indexes, long size);
    void generate_vertex_array();
    void bind_vertex_array();

private:
    unsigned int shader { 0 };
    unsigned int vao { 0 };
};

} // namespace vi
