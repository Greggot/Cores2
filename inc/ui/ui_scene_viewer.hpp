/**
 * @file
 * @brief Окно просмотра 3D моделей объектов сцены
 * @author https://github.com/Greggot/
 */

#pragma once
#include "ui/ui_viewport_converter.hpp"
#include "visualization/vi_mesh.hpp"
#include "visualization/vi_shader_holder.hpp"
#include <GL/glew.h>
#include <thread>
#include <wx/event.h>
#include <wx/glcanvas.h>
#include <wx/unix/glegl.h>

/// Элементы пользовательского интерфейса
namespace ui {

/// @brief Окно просмотра 3D моделей объектов сцены
class Scene_viewer : public wxGLCanvas {
public:
    Scene_viewer(wxWindow* host);

private:
    wxGLContext* rendering_context;
    Viewport_converter viewport_converter;
    vi::Shader_holder shader_holder;

    void render(wxPaintEvent&);
    void prepare_render();
    void finish_render();
    void update_viewport();
    void start_update_thread();

    bool is_open_gl_initialized { false };
    void open_gl_init();
    void compile_shaders();

    vi::Drawable test;
    std::thread update_thread;
};

} // namespace ui