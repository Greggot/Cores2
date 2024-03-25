/**
 * @file
 * @brief Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */
#pragma once
#include "ui/ui_scene_viewer.hpp"
#include <wx/wx.h>

namespace app {

class Main_window : public wxFrame {
public:
    Main_window(const wxString& title, const wxPoint& position, const wxSize& size);

private:
    ui::Scene_viewer* scene_viewer;
};

} // namespace app
