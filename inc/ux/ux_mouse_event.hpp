/**
 * @file
 * @brief Стркутура события мыши
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_types.hpp"
namespace ux {

/// @brief Событие мыши, чтобы изолировать преобразования
/// камеры от реализации событий wxWidgets или SDL
struct Mouse_event {
    enum class Mouse_button {
        left,
        right,
        middle
    } mouse_button { Mouse_button::left };
    enum class Event_type {
        motion,
        down,
        up,
        scroll_up,
        scroll_down,
    } event_type { Event_type::motion };
    gm::vector2<int> position;
};

struct Size_change_event {
    gm::vector2<int> size;
};

} // namespace ux