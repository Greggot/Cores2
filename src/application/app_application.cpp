/**
 * @file
 * @brief  Входная точка приложения
 * @author https://github.com/Greggot/
 */

#include "application/app_application.hpp"
#include "application/app_main_window.hpp"
#include <wx/wx.h>

namespace app {

/// @brief Имплементация класса приложения
class wxApplication : public Application, public wxApp {
public:
    /// @brief Создание объекта главного окна @ref app::Main_window
    bool OnInit() override
    {
        main_window = new Main_window("Hello World", wxDefaultPosition, { 400, 300 });
        main_window->Show(true);
        return true;
    }

    Tree_presenter& current_tree_presenter() final
    {
        return main_window->current_tree_presenter();
    }

private:
    Main_window* main_window { nullptr };
};

} // namespace app

int main(int argc, char** argv)
{
    return wxEntry(argc, argv);
}

app::wxApplication& wxGetApp()
{
    return *dynamic_cast<app::wxApplication*>(wxApp::GetInstance());
}

app::Application& app::application()
{
    return *dynamic_cast<app::Application*>(wxApp::GetInstance());
}

wxAppConsole* wxCreateApp()
{
    wxAppConsole::CheckBuildOptions("3"
                                    "."
                                    "3"
                                    "."
                                    "0"
                                    " ("
                                    "wchar_t"
                                    ",compiler with C++ ABI compatible with gcc 4"
                                    ",STL containers"
                                    ",compatible with 3.2"
                                    ")",
        "your program");
    return new app::wxApplication;
}
wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction)wxCreateApp);