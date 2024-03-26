/**
 * @file
 * @brief  Модель камеры области отображения
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_types.hpp"

namespace gm {

/// @brief  Модель камеры области отображения
struct Camera_model {
    gm::matrix4 view { 1.0 };
    gm::matrix4 projection { 1.0 };

    /// @brief  Размер бокса сцены - видимой области
    struct Scene_box {
        float width { 1 };
        float height { 1 };
        float depth { 10000 };
    } scene_box;
};

} // namespace gm
