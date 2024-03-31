/**
 * @file
 * @brief Узел дерева объектов
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_mesh.hpp"

namespace node {

/// @brief Узел дерева объектов. Пока что содержит только 
/// модель. В дальнейшем будет обрастать бизнес-логикой
class Node {
public:
    Node(const gm::Mesh& mesh):
        mesh_model(mesh) { }

    const gm::Mesh& mesh() const {
        return mesh_model;
    }
    gm::Mesh& mesh() {
        return mesh_model;
    }
private:
    gm::Mesh mesh_model;
};

} // namespace node