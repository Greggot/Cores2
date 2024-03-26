/**
 * @file
 * @brief  Меш - набор треугольников
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_frame.hpp"
#include "geometry/gm_triangle.hpp"
#include "visualization/vi_mesh.hpp"
namespace gm {

/// @brief Меш - набор треугольников. В дальнейшем
/// здесь будут дополнительные визуализаторы и методы
/// для выделения/проекции и пр.
class Mesh {
public:
    Mesh() = default;

    Frame& frame() { return local_frame; }
    const Frame& frame() const { return local_frame; }

    void add_triangle(const Triangle& triangle)
    {
        mesh_strip.add_triangle(triangle);
    }
    void apply_vertices()
    {
        mesh_strip.apply();
    }
    void apply_frame()
    {
        mesh_strip.mvp() = local_frame.mvp();
    }
    void draw()
    {
        mesh_strip.draw();
    }

private:
    Frame local_frame;
    vi::Mesh_strip mesh_strip;
};

static Mesh test_triangle(float length)
{
    Mesh mesh;
    mesh.add_triangle({ { 0, 0, 0 }, { length, 0, 0 }, { length, length, 0 } });
    mesh.apply_vertices();
    return mesh;
}

} // namespace gm
