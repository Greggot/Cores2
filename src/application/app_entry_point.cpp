/**
 * @file
 * @brief  Входная точка приложения
 * @author https://github.com/Greggot/
 */

#include "application/app_main_window.hpp"
#include <wx/wx.h>

/// Объекты верхнего уровня: главное окно и приложение 
namespace app {

class Application : public wxApp {
public:
    /// @brief Создание объекта главного окна @ref app::Main_window
    bool OnInit() override
    {
        auto* main_window = new Main_window("Hello World", wxDefaultPosition, wxDefaultSize);
        main_window->Show(true);
        return true;
    }
};

} // namespace app

wxIMPLEMENT_APP(app::Application);
