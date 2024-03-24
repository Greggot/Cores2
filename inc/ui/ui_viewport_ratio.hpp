/**
 * @file
 * @brief  Соотношение сторон, под которое можно подгонять размер
 * @author https://github.com/Greggot/
 */

#pragma once

namespace ui {

/// @brief Соотношение сторон, под которое можно подгонять размер
struct Viewport_ratio {
    int x;
    int y;
    constexpr Viewport_ratio(int x, int y):
        x(x), y(y) { }

    template <class XY_t>
    XY_t convert(const XY_t& size) const
    {
        return { (size.y / y) * x, (size.x / x) * y };
    }
};

} // namespace ui
