/**
 * @file
 * @brief Контроллер камеры
 * @author https://github.com/Greggot/
 */

#include "ux/ux_camera_controller.hpp"
#include "geometry/gm_types.hpp"
#include "ux/ux_mouse_event.hpp"

namespace ux {

Camera_controller::Camera_controller():
    eye(0.5, 0, 0.5),
    target(0, 0, 0),
    up(0, 0, 1)
{
    update_matrices();
}

void Camera_controller::handle(const Mouse_event& event)
{
    switch (event.event_type) {
        case ux::Mouse_event::Event_type::down:
            before = event.position;
            dragged = true;
            if (event.mouse_button == Mouse_event::Mouse_button::middle)
                rotate_mode = true;
            break;
        case ux::Mouse_event::Event_type::up:
            dragged = false;
            if (event.mouse_button == Mouse_event::Mouse_button::middle)
                rotate_mode = false;
            break;
        case ux::Mouse_event::Event_type::motion:
            handle_motion(event);
            break;
        case ux::Mouse_event::Event_type::scroll_down:
            model.scene_box.height *= 1.1;
            model.scene_box.width *= 1.1;
            update_matrices();
            break;
        case ux::Mouse_event::Event_type::scroll_up:
            model.scene_box.height *= 0.9;
            model.scene_box.width *= 0.9;
            update_matrices();
            break;
        default:
            break;
    }
}

void Camera_controller::handle(const Size_change_event& event)
{
    model.scene_box.width = float(event.size.x);
    model.scene_box.height = float(event.size.y);
    update_matrices();
}

void Camera_controller::handle(const Key_event& event)
{
    switch(event.key) {
        case 306:
            rotate_mode = event.type == Key_event::Event_type::down;
            break;
        default:
            break;
    }
}

const gm::matrix4& Camera_controller::view() const
{
    return model.view;
}
const gm::matrix4& Camera_controller::projection() const
{
    return model.projection;
}

void Camera_controller::handle_motion(const Mouse_event& event)
{
    if (!dragged)
        return;

    const auto after = event.position;
    const auto dx = after.x - before.x;
    const auto dy = before.y - after.y;

    if (rotate_mode) {
        handle_rotation({ -dx, dy });
    } else {
        const auto right = gm::normalize(gm::cross(target - eye, up));
        const auto delta = (float(dx) * right / model.scene_box.width) + (float(dy) * up / model.scene_box.height);
        handle_translation(delta);
    }
    before = after;
    update_matrices();
}

void Camera_controller::handle_rotation(gm::vector2<int> delta)
{
    const auto right = gm::normalize(gm::cross(target - eye, up));
    gm::vector4 vec { eye - target, 1.0 };
    vec = gm::rotate_degree(gm::matrix4 { 1.0 }, float(delta.x), up) * vec;
    vec = gm::rotate_degree(gm::matrix4 { 1.0 }, float(delta.y), right) * vec;
    eye = vec;
    eye += target;
}

void Camera_controller::handle_translation(gm::vector3 delta)
{
    target -= delta;
    eye -= delta;
}

void Camera_controller::update_matrices()
{
    model.projection = gm::projection_orthogonal(model.scene_box.width / 2, model.scene_box.height / 2, model.scene_box.depth);
    model.view = gm::view_matrix(eye, target, up);
}

} // namespace ux
