/**
 * @file
 * @brief Конвертация размеров виджета под заданное соотношение сторон
 * @author https://github.com/Greggot/
 */

#pragma once
#include "ui/ui_viewport_ratio.hpp"
#include <wx/wx.h>

namespace ui {

/// @brief Конвертация размеров виджета под заданное соотношение сторон
struct Viewport_converter {
    wxSize viewport_size;
    wxSize widget_size;
    bool ratio_by_x { false };

    void update_widget_size(const wxSize& size, const Viewport_ratio& ratio)
    {
        widget_size = size;
        viewport_size = ratio.convert(size);
        ratio_by_x = size.x > size.y;
    }

    wxSize convert()
    {
        if (ratio_by_x)
            return { widget_size.x, viewport_size.y };
        else
            return { viewport_size.x, widget_size.y };
    }
};

} // namespace ui