/**
 * @file
 * @brief  Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */

#include "ui/ui_scene_viewer.hpp"
#include "visualization/vi_mesh.hpp"
#include <wx/event.h>
#include <wx/wx.h>

namespace ui {

static constexpr Viewport_ratio viewport_ratio { 4, 3 };

Scene_viewer::Scene_viewer(wxWindow* host):
    wxGLCanvas(host),
    rendering_context(new wxGLContext(this))
{
    // open_gl_init();
    Bind(wxEVT_PAINT, &Scene_viewer::render, this);
    Bind(wxEVT_SIZE, [this](wxSizeEvent&) {
        viewport_converter.update_widget_size(GetSize(), viewport_ratio);
    });
    start_update_thread();
}

/// @brief Отрисовать все трехмерные модели, представления сборки
void Scene_viewer::render(wxPaintEvent& paint_event)
{
    if (!is_open_gl_initialized)
        open_gl_init();
    prepare_render();
    update_viewport();

    test.draw();

    finish_render();
}

void Scene_viewer::start_update_thread()
{
    update_thread = std::thread([this] {
        constexpr int delayms = 1000 / 60;
        while (true) {
            Refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
        }
    });
}

/// @brief Подготовить контекст для wxPaint.
/// Задать флаги OpenGL: использование буфера цвета и глубины.
/// Очистить предыдущее значение флагов.
void Scene_viewer::prepare_render()
{
    SetCurrent(*rendering_context);
    wxPaintDC unused { this };
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
}

/// @brief Отправить буфер на видеокарту
void Scene_viewer::finish_render()
{
    glFlush();
    SwapBuffers();
}

/// @brief Задать viewport, который задается соотноешением сторон
void Scene_viewer::update_viewport()
{
    const auto viewport = viewport_converter.convert();
    glViewport(0, 0, viewport.x, viewport.y);
}

void Scene_viewer::compile_shaders()
{
    shader_holder.compiler().allocate_log_buffer(400);
    shader_holder.compiler().set_error_report_function([](std::string_view error) {
        fprintf(stderr, "%s\n", std::data(error));
    });
    shader_holder.allocate<vi::Shader::mesh>(
        "shaders/mesh_vertex.glsl",
        "shaders/mesh_fragment.glsl");
    shader_holder.compiler().deallocate_log_buffer();

    test = vi::Drawable(shader_holder.at(vi::Shader::mesh));
}

void Scene_viewer::open_gl_init()
{
    SetCurrent(*rendering_context);
    const auto error = glewInit();
    if (error != GLEW_OK)
        fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
    compile_shaders();
    is_open_gl_initialized = true;
}

} // namespace ui