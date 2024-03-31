/**
 * @file
 * @brief Импорт файлов STL
 * @author https://github.com/Greggot/
 */

#include "import_export/ie_stl.hpp"
#include <fstream>

namespace ie {
namespace stl {

struct Header {
    std::array<char, 80> ASCII { 0 };
    unsigned int facets_size = 0;
};

#pragma pack(push, 2)
struct Triangle {
    gm::vector3 normal {};
    std::array<gm::vector3, 3> vertices {};
    uint16_t attrbyte_count { 0 };
};
#pragma pack(pop)

gm::Mesh import(const char* path)
{
    std::ifstream file(path, std::ios::binary | std::ios::in);

    Header header;
    file.read((char*)(&header), sizeof(header));

    gm::Mesh mesh;
    for (unsigned int i = 0; i < header.facets_size; ++i)
    {
        Triangle triangle;
        file.read((char*)(&triangle), sizeof(triangle));
        mesh.add_triangle({ triangle.vertices.at(0),
            triangle.vertices.at(1),
            triangle.vertices.at(2) });
    }
    return mesh;
}

} // namespace stl
} // namespace ie
