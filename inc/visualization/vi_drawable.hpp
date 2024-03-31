/**
 * @file
 * @brief  Интерфейс объекта, что можно отрисовывать
 * @author https://github.com/Greggot/
 */

#pragma once
#include "geometry/gm_types.hpp"
#include "visualization/vi_shader_holder.hpp"

/// @brief Визуальные объекты, привязанные к контексту рендера (OpenGL)
/// @todo Отделить низкоуровневые вызовы OpenGL, добавить альтернативу в виде Vulkan
namespace vi {

/// @brief  Интерфейс объекта, что можно отрисовывать
class Drawable {
public:
    Drawable() = default;
    Drawable(Drawable&&) = delete;
    Drawable(const Drawable&) = default;
    Drawable& operator=(Drawable&&) = delete;
    Drawable& operator=(const Drawable&) = default;
    virtual ~Drawable() = default;

    virtual void draw() const = 0;

    gm::matrix4& mvp() { return world_to_screen; }
    const gm::matrix4& mvp() const { return world_to_screen; }

protected:
    vi::Shader_holder& shader_holer();
    const vi::Shader_holder& shader_holer() const;

    unsigned int generate_vertex_buffer(unsigned int layout, const float* data, long size);
    unsigned int generate_index_buffer(const unsigned int* indexes, long size);
    void generate_vertex_array();
    void bind_vertex_array() const;

private:
    unsigned int shader { 0 };
    unsigned int vao { 0 };
    gm::matrix4 world_to_screen { 1.0 };
};

} // namespace vi
