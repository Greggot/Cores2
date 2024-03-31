/**
 * @file
 * @brief Импорт файлов OBJ
 * @author https://github.com/Greggot/
 */

#include "import_export/ie_obj.hpp"
#include <fstream>
#include <string>

namespace ie {
namespace obj {

enum class symbol : char {
    vertex = 'v',
    face = 'f',
    part = 'u',
    material = 'm',
    material_filename = 'g',

    material_name = 'n',
    color = 'K',
};

struct Triangular {
    int i = 0;
    int j = 0;
    int k = 0;
};

using Color = gm::vector3;
using Vertex = gm::vector3;
using Tokens = std::vector<std::string>;
using Face_set = std::vector<Triangular>;

Triangular tokens_to_triangular(const Tokens& tokens)
{
    return Triangular {
        atoi(tokens[1].c_str()) - 1,
        atoi(tokens[2].c_str()) - 1,
        atoi(tokens[3].c_str()) - 1
    };
}

Vertex tokens_to_vertex(const Tokens& tokens)
{
    return Vertex {
        strtof(tokens[1].c_str(), nullptr),
        strtof(tokens[2].c_str(), nullptr),
        strtof(tokens[3].c_str(), nullptr)
    };
}

Tokens OBJ_line_to_tokens(const std::string& line)
{
    size_t index = 0;
    Tokens tokens;
    std::string buffer;

    while (line[index] != '\n')
    {
        if (line[index] == ' ') {
            tokens.push_back(buffer);
            buffer = "";
        } else
            buffer += line[index];
        ++index;
    }
    tokens.push_back(buffer);
    return tokens;
}

/// @brief Считать цвет из файла MTL
Color MTL_file_to_color(const char* path, const char* base)
{
    bool findmaterial = false;

    std::ifstream file(path);
    std::string buffer;
    while (std::getline(file, buffer))
    {
        auto mtldata = OBJ_line_to_tokens(buffer);
        switch ((symbol)mtldata[0][0])
        {
            case symbol::material_name:
                findmaterial = mtldata[1] == base;
                break;
            case symbol::color:
                if (!findmaterial)
                    break;
                return tokens_to_vertex(mtldata);
            default:
                break;
        }
    }
    return gm::vector3(0.553f, 0.843f, 0.89f);
}

/// @brief Получить путь к папке из пути к файлу
static std::string::const_iterator folder_from_path(const std::string& path)
{
    for (auto symbol = path.rbegin(); symbol != path.rend(); ++symbol)
        if (*symbol == '\\' || *symbol == '/')
            return std::next(symbol).base();
    return path.end();
}

/// @brief Получить путь к MTL файлу по пути к OBJ файлу. 
/// Обычно файл материала находится рядом с файлом модели.
static std::string get_mtl_path(std::string path, const std::string& name)
{
    path.erase(path.begin(), folder_from_path(path));
    path += std::string("/") + name;
    return path;
}

/// @brief Считать набор вершин и индексов треугольников из файла OBJ
void read(const char* path, std::vector<Face_set>& overall_faces, std::vector<gm::vector3>& vertices)
{
    Face_set face_set;

    std::ifstream file(path);
    std::string buffer;
    while (std::getline(file, buffer))
    {
        const auto data = OBJ_line_to_tokens(buffer);
        if (data.front() == "usemtl") {
            if (!face_set.empty()) {
                overall_faces.push_back(face_set);
            }
        }

        switch (static_cast<symbol>(data.front().front()))
        {
            case symbol::vertex:
                vertices.push_back(tokens_to_vertex(data));
                break;
            case symbol::face:
                face_set.push_back(tokens_to_triangular(data));
                break;
            default:
                break;
        }
    }
    if (!face_set.empty()) {
        overall_faces.push_back(face_set);
    }
}

/// @brief Считать набор треугольников-индексов и конвертировать к мешу.
/// @todo Конвертировать в меш, который поддерживает индексацию треугольников.
gm::Mesh import(const char* path)
{
    std::vector<std::vector<Triangular>> overall_faces;
    std::vector<gm::vector3> vertices;
    read(path, overall_faces, vertices);

    size_t normals_amount = 0;
    for (const auto& faces : overall_faces)
        normals_amount += faces.size();

    std::vector<gm::vector3> normals;
    normals.resize(normals_amount * 3);

    gm::Mesh mesh;
    for (const auto& faces : overall_faces) {
        for (const auto& face : faces) {
            mesh.add_triangle({ vertices[face.i],
                vertices[face.j],
                vertices[face.k] });
        }
    }
    return mesh;
}

} // namespace obj
} // namespace ie