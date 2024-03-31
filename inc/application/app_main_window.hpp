/**
 * @file
 * @brief Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */
#pragma once
#include "application/app_tree_presenter.hpp"
#include "ui/ui_file_menu.hpp"
#include <wx/wx.h>

namespace app {

class Main_window : public wxFrame {
public:
    Main_window(const wxString& title, const wxPoint& position, const wxSize& size);
    Tree_presenter& current_tree_presenter() { return tree_presenter; }

private:
    // ui::Scene_viewer* scene_viewer;
    Tree_presenter tree_presenter;
    ui::File_menu* file_menu;

    void menu_bar_init();
};

} // namespace app
