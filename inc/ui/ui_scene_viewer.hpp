/**
 * @file
 * @brief Окно просмотра 3D моделей объектов сцены
 * @author https://github.com/Greggot/
 */

#pragma once
#include "geometry/gm_mesh.hpp"
#include "ui/ui_viewport_converter.hpp"
#include "ux/ux_camera_controller.hpp"
#include "visualization/vi_axes.hpp"
#include <GL/glew.h>
#include <functional>
#include <thread>
#include <wx/event.h>
#include <wx/glcanvas.h>
#include <wx/unix/glegl.h>

/// Элементы пользовательского интерфейса
namespace ui {

/// @brief Окно просмотра 3D моделей объектов сцены
class Scene_viewer final : public wxGLCanvas {
public:
    Scene_viewer(wxWindow* host);
    Scene_viewer(Scene_viewer&) = delete;
    Scene_viewer(Scene_viewer&&) = delete;
    Scene_viewer& operator=(Scene_viewer&) = delete;
    Scene_viewer& operator=(Scene_viewer&&) = delete;
    ~Scene_viewer() final;

    void add_mesh(gm::Mesh& mesh) {
        meshes.push_back(mesh);
    }

private:
    wxGLContext* rendering_context;
    Viewport_converter viewport_converter;

    /// @todo Выделить во view просмотрщика сцены - класс визуального отображения сцены
    vi::Axes axes;
    std::vector<std::reference_wrapper<gm::Mesh>> meshes;

    ux::Camera_controller camera_controller;

    void render(wxPaintEvent&);
    void prepare_render();
    void finish_render();
    void start_update_thread();

    void update_viewport();
    void update_axes_viewport();

    void render_init();
    void compile_shaders();

    void update_view();

    bool is_canvas_updating { true };
    std::thread update_thread;
};

} // namespace ui