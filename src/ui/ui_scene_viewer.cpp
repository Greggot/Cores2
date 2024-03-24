#include "ui/ui_scene_viewer.hpp"
#include <wx/event.h>
#include <wx/wx.h>

namespace ui {

static constexpr Viewport_ratio viewport_ratio { 4, 3 };

Scene_viewer::Scene_viewer(wxWindow* host):
    wxGLCanvas(host),
    rendering_context(new wxGLContext(this))
{
    Bind(wxEVT_PAINT, &Scene_viewer::render, this);
    Bind(wxEVT_SIZE, [this](wxSizeEvent&) {
        viewport_converter.update_widget_size(GetSize(), viewport_ratio);
    });
}

/// @brief Отрисовать все трехмерные модели, представления сборки
void Scene_viewer::render(wxPaintEvent& paint_event)
{
    prepare_render();
    update_viewport();
    finish_render();
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

} // namespace ui