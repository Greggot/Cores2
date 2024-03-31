/**
 * @file
 * @brief Меню импорта файлов
 * @author https://github.com/Greggot/
 */

#pragma once

#include "application/app_application.hpp"
#include "import_export/ie_obj.hpp"
#include "import_export/ie_stl.hpp"
#include "ui/ui_ids.hpp"
#include <string_view>
#include <wx/wx.h>

namespace ui {

/// @brief Меню импорта файлов. Обращается к @ref app::Application,
/// чтобы получить актуальное дерево моделей. Обращение именно к 
/// приложению потому, что меню является единым для всего приложения,
/// вне зависимости от количества деревьев и их представлений.
class File_menu : public wxMenu {
public:
    File_menu()
    {
        append_menu_item(File_menu_ids::open_file, "Open file...", &File_menu::open_model_file, "");
    }

private:
    void append_menu_item(int ID, std::string_view Name,
        void (File_menu::*Method)(wxCommandEvent&), std::string_view Description)
    {
        Append(new wxMenuItem(nullptr, ID, std::data(Name), std::data(Description)));
        Bind(wxEVT_MENU, Method, this, ID);
    }

    void open_model_file(wxCommandEvent&)
    {
        std::string description = "";
        for (const auto& file : std::vector<std::string> { "obj", "stl" }) {
            description += file;
            description += " files (*.";
            description += file;
            description += ")|*.";
            description += file;
            description += "|";
        }
        description.erase(description.size() - 1);

        wxFileDialog open(nullptr, wxString("Open Model"), "", "", description, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (open.ShowModal() == wxID_CANCEL)
            return;

        auto path = open.GetPath();
        auto extention = path.Mid(path.Index('.') + 1);

        if (extention == "obj") {
            const auto mesh = ie::obj::import(open.GetPath().mb_str().data());
            app::application().current_tree_presenter().create_node(mesh);
        } else if (extention == "stl") {
            const auto mesh = ie::stl::import(open.GetPath().mb_str().data());
            app::application().current_tree_presenter().create_node(mesh);
        }
    }
};

} // namespace ui
