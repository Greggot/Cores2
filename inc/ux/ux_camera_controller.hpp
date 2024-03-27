/**
 * @file
 * @brief Контроллер камеры
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_camera_model.hpp"
#include "geometry/gm_types.hpp"
#include "ux/ux_mouse_event.hpp"

namespace ux {

/// @brief Контроллер камеры, применяющий преобразования подобия
/// (sim(3)) к положению камеры.
class Camera_controller {
public:
    Camera_controller();
    void handle(const Mouse_event&);
    void handle(const Size_change_event&);
    void handle(const Key_event&);

    const gm::matrix4& view() const;
    const gm::matrix4& projection() const;

private:
    gm::vector3 eye;
    gm::vector3 target;
    gm::vector3 up;

    gm::Camera_model model;

    bool rotate_mode { false };
    bool dragged { false };
    gm::vector2<int> before;

    void handle_motion(const Mouse_event&);
    void handle_rotation(gm::vector2<int>);
    void handle_translation(gm::vector3);

    void update_matrices();
};

} // namespace ux
