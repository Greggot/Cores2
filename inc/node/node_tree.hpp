/**
 * @file
 * @brief  Дерево объектов сцены 
 * @author https://github.com/Greggot/
 */

#pragma once

#include "node_node.hpp"
#include <memory>
#include <vector>

namespace node {

/// @brief  Дерево объектов сцены. Группирует @ref node::Node.
/// Пока что хранит только линейный список элементов. В дальнейшем
/// будет выстраивать иерархию между элементами. 
class Tree {
public:
    size_t add_node(std::unique_ptr<Node>&& node)
    {
        nodes.push_back(std::move(node));
        return nodes.size() - 1;
    }

    const Node& node(size_t index) const
    {
        return *nodes.at(index);
    }
    Node& node(size_t index)
    {
        return *nodes.at(index);
    }

private:
    std::vector<std::unique_ptr<Node>> nodes;
};

} // namespace node