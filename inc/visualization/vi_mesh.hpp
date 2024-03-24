/**
 * @file
 * @brief  Главное окно, содержащее внутри себя все панели, меню и пр.
 * @author https://github.com/Greggot/
 */

#pragma once
#include "visualization/vi_uniforms.hpp"
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace vi {

struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

struct Colored_mesh : public Mesh {
    glm::vec3 color;
};

class Drawable {
public:
    Drawable() = default;
    explicit Drawable(unsigned int shader):
        shader(shader)
    {
        float vertices[12] = {
            0, 0, 0,
            0, 0.5, 0,
            0.5, 0.5, 0
        };

        float normals[12] = {
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
        };
        generate_vertex_buffer(0, (float*)(vertices), sizeof(glm::vec3) * 3);
        generate_vertex_buffer(1, (float*)normals, sizeof(glm::vec3) * 3);
    }
    virtual ~Drawable() { }

    virtual void draw()
    {
        glBindVertexArray(vao);

        glUseProgram(shader);
        uniforms.pass(shader, Uniform::color, glm::vec3 { 1.0, 0, 0 });
        pass_MVP(shader);

        glDrawArrays(GL_TRIANGLES, 0, 3 * 1);
    }

protected:
    void generate_vertex_buffer(unsigned int layout, const float* data, long size)
    {
        unsigned int vbo { 0 };
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferStorage(GL_ARRAY_BUFFER, size, data, GL_MAP_READ_BIT);
        glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(layout);
    }
    void generate_index_buffer(const unsigned int* indexes, long size)
    {
        unsigned int ebo { 0 };
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_MAP_READ_BIT);
    }

    void pass_MVP(unsigned int shader)
    {
        //     Uniforms.pass(shader, Uniform::Model, system_matrix * _model);

        //     if (camera == nullptr)
        //         return;
        //     Uniforms.pass(shader, Uniform::View, camera->view());
        //     Uniforms.pass(shader, Uniform::Projection, camera->projection());
        //     Uniforms.pass(shader, Uniform::LightPosition, camera->position());
    }

private:
    glm::mat4 _model {};
    glm::mat4 system_matrix {};
    unsigned int shader { 0 };
    unsigned int vao { 0 };
};

} // namespace vi
