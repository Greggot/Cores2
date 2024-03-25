/**
 * @file
 * @brief  Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */

#include "application/app_main_window.hpp"
#include "ui/ui_scene_viewer.hpp"
#include <wx/event.h>
#include <wx/msgdlg.h>

namespace app {

Main_window::Main_window(const wxString& title, const wxPoint& position, const wxSize& size):
    wxFrame(NULL, wxID_ANY, title, position, size),
    scene_viewer(new ui::Scene_viewer(this))
{
    SetBackgroundColour(wxColour { 0x60, 0x60, 0x60 });
    CreateStatusBar();
}

} // namespace app
