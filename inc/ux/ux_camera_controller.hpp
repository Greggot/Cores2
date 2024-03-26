/**
 * @file
 * @brief Контроллер камеры
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_types.hpp"
#include "geometry/gm_camera_model.hpp"

namespace ux {

/// @brief  Модель камеры области отображения
struct Mouse_event {
    enum class Mouse_button {
        left,
        right,
        middle
    } mouse_button;
    enum class Event_type {
        motion,
        down,
        up,
        scroll_up,
        scroll_down,
    } event_type;
    int x;
    int y;
};

/// @brief Контроллер камеры, применяющий преобразования подобия 
/// (sim(3)) к положению камеры.
class Camera_controller {
public:
    Camera_controller():
        eye(0.5, 0, 0.5),
        target(0, 0, 0),
        up(0, 0, 1)
    {
        model.projection = gm::projection_orthogonal(model.scene_box.width, model.scene_box.height, model.scene_box.depth);
        model.view = gm::view_matrix(eye, target, up);
    }

    void handle(const Mouse_event& event) {
        switch (event.event_type) {
            case ux::Mouse_event::Event_type::scroll_down:
                model.view = gm::rotate_degree(model.view, 0.5f, up);
                break;
            case ux::Mouse_event::Event_type::scroll_up:
                model.view = gm::rotate_degree(model.view, -0.5f, up);
                break;
            default:
                break;
        }
    }

    const gm::matrix4& view() const {
        return model.view;
    }
    const gm::matrix4& projection() const {
        return model.projection;
    }

private:
    gm::vector3 eye;
    gm::vector3 target;
    gm::vector3 up;

    gm::Camera_model model;
};

} // namespace ux
