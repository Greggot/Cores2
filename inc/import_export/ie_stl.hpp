/**
 * @file
 * @brief Импорт файлов STL
 * @author https://github.com/Greggot/
 */

#pragma once
#include "geometry/gm_mesh.hpp"

namespace ie {
namespace stl {

gm::Mesh import(const char* path);

} // namespace stl
} // namespace io
