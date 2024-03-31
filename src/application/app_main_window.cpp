/**
 * @file
 * @brief  Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */

#include "application/app_main_window.hpp"
#include "ui/ui_file_menu.hpp"
#include "ui/ui_scene_viewer.hpp"
#include <wx/event.h>
#include <wx/msgdlg.h>

namespace app {

Main_window::Main_window(const wxString& title, const wxPoint& position, const wxSize& size):
    wxFrame(NULL, wxID_ANY, title, position, size),
    tree_presenter(this)
{
    SetBackgroundColour(wxColour { 0x60, 0x60, 0x60 });
    CreateStatusBar();

    menu_bar_init();
}

void Main_window::menu_bar_init() 
{
	auto* menu_bar = new wxMenuBar();
	menu_bar->Append(new ui::File_menu, "File");
	SetMenuBar(menu_bar);
}

} // namespace app
