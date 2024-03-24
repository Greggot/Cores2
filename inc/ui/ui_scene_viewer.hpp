/**
 * @file
 * @brief Окно просмотра 3D моделей объектов сцены
 * @author https://github.com/Greggot/
 */

#pragma once
#include "ui/ui_viewport_converter.hpp"
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

    void render(wxPaintEvent&);
    void prepare_render();
    void finish_render();
    void update_viewport();
};

} // namespace ui