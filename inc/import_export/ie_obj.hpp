/**
 * @file
 * @brief Импорт файлов OBJ
 * @author https://github.com/Greggot/
 */

#pragma once
#include "geometry/gm_mesh.hpp"

namespace ie {
namespace obj {

gm::Mesh import(const char* path);

} // namespace obj
} // namespace ie