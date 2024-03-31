/**
 * @file
 * @brief Презентер дерева объектов робототехнической системы
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_mesh.hpp"
#include "node/node_node.hpp"
#include "node/node_tree.hpp"
#include "ui/ui_scene_viewer.hpp"
#include <wx/window.h>

namespace app {

/// @brief Презентер дерева объектов робототехнической системы.
/// Содержит внутри себя модель дерева, а также его представления -
/// @ref ui::Scene_viewer - для отображения трехмерных моделей, а 
/// также контрол дерева в дальнейшем для изменения связей элементов.
class Tree_presenter {
public:
    Tree_presenter(wxWindow* host):
        scene_viewer(new ui::Scene_viewer(host))
    {
    }

    /// @brief Добавление узла с обновлением представлений дерева
    void add_node(std::unique_ptr<node::Node>&& node)
    {
        const auto new_node_index = tree.add_node(std::move(node));
        auto& node_mesh = tree.node(new_node_index).mesh();
        node_mesh.apply_vertices();
        scene_viewer->add_mesh(node_mesh);
    }

    /// @brief Создание узла из 3D модели, добавление в дерево
    void create_node(const gm::Mesh& mesh)
    {
        add_node(std::make_unique<node::Node>(mesh));
    }

private:
    node::Tree tree;
    ui::Scene_viewer* scene_viewer;
};

} // namespace app