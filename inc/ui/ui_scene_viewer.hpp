/**
 * @file
 * @brief Окно просмотра 3D моделей объектов сцены
 * @author https://github.com/Greggot/
 */

#pragma once
#include "ui/ui_viewport_converter.hpp"
#include "visualization/vi_axes.hpp"
#include "visualization/vi_mesh.hpp"
#include <GL/glew.h>
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


private:
    wxGLContext* rendering_context;
    Viewport_converter viewport_converter;
    vi::Axes axes;
    vi::Mesh_strip test_mesh;

    void render(wxPaintEvent&);
    void prepare_render();
    void finish_render();
    void update_viewport();
    void start_update_thread();

    void render_init();
    void compile_shaders();

    bool is_canvas_updating { true };
    std::thread update_thread;
};

} // namespace ui