/**
 * @file
 * @brief Окно просмотра 3D моделей объектов сцены
 * @author https://github.com/Greggot/
 */

#include "ui/ui_scene_viewer.hpp"
#include "application/app_application.hpp"
#include "geometry/gm_mesh.hpp"
#include "ux/ux_camera_controller.hpp"
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/window.h>
#include <wx/wx.h>

namespace ui {

static constexpr Viewport_ratio viewport_ratio { 4, 3 };

Scene_viewer::Scene_viewer(wxWindow* host):
    wxGLCanvas(host),
    rendering_context(new wxGLContext(this))
{
    render_init();
    Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent& event) {
        const auto position = wxGetMousePosition();
        const auto event_type = event.GetWheelRotation() > 0 ?
            ux::Mouse_event::Event_type::scroll_up : 
            ux::Mouse_event::Event_type::scroll_down;
        ux::Mouse_event mouse_event {
            ux::Mouse_event::Mouse_button::middle,
            event_type,
            position.x, position.y
        };
        camera_controller.handle(mouse_event);
        axes.mvp() = camera_controller.view();
        mesh.frame().set_view_projection(camera_controller.projection() * camera_controller.view());
        mesh.apply_frame();
    });
    Bind(wxEVT_SIZE, [this](wxSizeEvent&) {
        viewport_converter.update_widget_size(GetSize(), viewport_ratio);
    });
    start_update_thread();
}

Scene_viewer::~Scene_viewer()
{
    is_canvas_updating = false;
    update_thread.join();
}

/// @brief Отрисовать все трехмерные модели, представления сборки
void Scene_viewer::render(wxPaintEvent& paint_event)
{
    prepare_render();
    update_viewport();

    mesh.draw();

    update_axes_viewport();
    axes.draw();

    finish_render();
}

void Scene_viewer::start_update_thread()
{
    update_thread = std::thread([this] {
        constexpr int delayms = 1000 / 60;
        while (is_canvas_updating) {
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

/// @brief Задать отдельный viewport для осей в углу экрана
void Scene_viewer::update_axes_viewport()
{
    const auto viewport = viewport_converter.convert();
    glViewport(0, 0, viewport.x / 5, viewport.y / 5);
}

/// @brief Если контекст OpenGL не инициализирован, сделать так,
/// чтобы на первый wxPaintEvent во всем приложении инициализировался
/// контекст. Это нужно, чтобы не инициализировать его при создании каждого
/// инстанса Scene_viewer.
///
/// Находится именно тут, потому что
/// 1. Для инициализации нужно задать контекст рендера. Иначе пришлось бы
///     показывать его снаружи.
/// 2. Если предполагается, что будет несколько сцен, то нужно будет как-то
///     брать самую первую (особенную) из них
void Scene_viewer::render_init()
{
    if (app::application().is_open_gl_initialized()) {
        Bind(wxEVT_PAINT, &Scene_viewer::render, this);
        return;
    }

    Bind(wxEVT_PAINT, [this](const wxPaintEvent&) {
        SetCurrent(*rendering_context);
        const auto error = glewInit();
        if (error != GLEW_OK && error != 4) {
            wxMessageBox("Error: %s", glewGetErrorString(error));
        } else {
            compile_shaders();
            Bind(wxEVT_PAINT, &Scene_viewer::render, this);
            app::application().open_gl_initialization_complete();
        }
    });
}

/// @brief Собрать все шейдеры для глобального @ref vi::Shader_holder.
/// Оно нахо
void Scene_viewer::compile_shaders()
{
    auto& shader_holder = app::application().shader_holder();
    shader_holder.compiler().allocate_log_buffer(400);
    shader_holder.compiler().set_error_report_function([](std::string_view error) {
        wxMessageBox(std::data(error));
    });
    shader_holder.allocate<vi::Shader::mesh>(
        "shaders/mesh_vertex.glsl",
        "shaders/mesh_fragment.glsl");

    shader_holder.allocate<vi::Shader::axis>(
        "shaders/axes_vertex.glsl",
        "shaders/axes_fragment.glsl");
    shader_holder.compiler().deallocate_log_buffer();

    mesh = gm::test_triangle();
    // test_mesh.add_triangle({ { 0, 0, 0 }, { 0.5, 0, 0 }, { 0.5, 0.5, 0 } });
    // test_mesh.apply();
}

} // namespace ui