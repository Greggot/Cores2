/**
 * @file
 * @brief  Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */

#include "application/app_main_window.hpp"
#include "ui/ui_scene_viewer.hpp"

namespace app {

Main_window::Main_window(const wxString& title, const wxPoint& position, const wxSize& size):
    wxFrame(NULL, wxID_ANY, title, position, size),
    scene_viewer(new ui::Scene_viewer(this))
{
    CreateStatusBar();
    SetStatusText("Test window");
}

void Main_window::on_exit(wxCommandEvent& event) { Close(true); }

} // namespace app
