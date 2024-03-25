/**
 * @file
 * @brief  Отображение осей координат
 * @author https://github.com/Greggot/
 */

#pragma once

#include "visualization/vi_drawable.hpp"
#include <glm/glm.hpp>

namespace vi {

/// @brief Отображение осей координат
/// @todo Добавить презентер для осей и метод для задания матрицы модели
class Axes : public Drawable {
public:
    Axes();
    void draw() override;

private:
    glm::mat4 model;
    void initialize();
};

} // namespace vi
