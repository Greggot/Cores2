/**
 * @file
 * @brief  Входная точка приложения
 * @author https://github.com/Greggot/
 */

#pragma once
#include "application/app_tree_presenter.hpp"
#include "visualization/vi_shader_holder.hpp"

/// Объекты верхнего уровня: главное окно и приложение
namespace app {

class Application {
public:
    const vi::Shader_holder& shader_holder() const { return holder; }
    vi::Shader_holder& shader_holder() { return holder; }

    bool is_open_gl_initialized() const { return open_gl_initialized; }
    void open_gl_initialization_complete() { open_gl_initialized = true; }

    virtual Tree_presenter& current_tree_presenter() = 0;

private:
    /// @brief Шейдеры должны быть глобально доступны для
    /// объектов отображения. Их сложно связать с окном отображения,
    /// поскольку у него может быть несколько инстансов. А создавать
    /// для него singleton звучит как не самая лучшая идея.
    vi::Shader_holder holder;
    bool open_gl_initialized { false };
};

/// @brief Функция, возвращающая объект приложения
Application& application();

} // namespace app
