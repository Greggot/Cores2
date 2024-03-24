/**
 * @file
 * @brief  Компилятор для шейдеров GLSL
 * @author https://github.com/Greggot/
 */

#pragma once

#include <GL/glew.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <string_view>

namespace vi {

/// @brief  Компилятор для шейдеров GLSL. Работает только с файловыми путями,
/// а также функцией, что вызывается при какой-либо ошибке. Аггрегируется в @ref vi::Shader_holder
class Shader_compiler {
public:
    Shader_compiler() = default;

    void set_error_report_function(const std::function<void(std::string_view)>& function)
    {
        error_report_function = function;
    }

    void allocate_log_buffer(size_t size)
    {
        log.resize(size);
        log_ptr = log.data();
    }

    void deallocate_log_buffer()
    {
        log.clear();
        log_ptr = log.data();
    }

    unsigned int build_shader(std::optional<std::string_view> vertex,
        std::optional<std::string_view> geometry,
        std::optional<std::string_view> fragment)
    {
        std::vector<unsigned int> shader_ids;
        if (vertex)
            shader_ids.push_back(compile_shader(GL_VERTEX_SHADER, vertex.value()));
        if (geometry)
            shader_ids.push_back(compile_shader(GL_GEOMETRY_SHADER, geometry.value()));
        if (fragment)
            shader_ids.push_back(compile_shader(GL_FRAGMENT_SHADER, fragment.value()));
        return link_shader_program(shader_ids);
    }

private:
    unsigned int compile_shader(unsigned int shader_type, std::string_view path)
    {
        const auto shader = glCreateShader(shader_type);
        const auto shader_string = load_shader_source(path);
        auto shader_data = std::data(shader_string);

        glShaderSource(shader, 1, &shader_data, nullptr);
        glCompileShader(shader);

        int success { 0 };
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success && error_report_function && log_ptr != nullptr)
        {
            std::cout << "Code: " << shader_data << "\n";
            glGetShaderInfoLog(shader, static_cast<int>(log.size()), nullptr, log_ptr);
            error_report_function(log_ptr);
            return 0;
        }
        return shader;
    }

    std::string load_shader_source(std::string_view path) const
    {
        std::ifstream shader_file(std::data(path));
        if (shader_file.is_open()) {
            std::stringstream buffer;
            buffer << shader_file.rdbuf();
            return buffer.str();
        }

        if (error_report_function) {
            error_report_function("Cannot read shader file: " + std::string { path });
        }
        return {};
    }

    unsigned int link_shader_program(const std::vector<unsigned int>& shaders)
    {
        const auto program = glCreateProgram();
        for (unsigned int shader : shaders)
        {
            if (shader != 0)
            {
                glAttachShader(program, shader);
                glDeleteShader(shader);
            }
        }
        glLinkProgram(program);

        int success { 0 };
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success && error_report_function && log_ptr != nullptr)
        {
            glGetProgramInfoLog(program, static_cast<int>(log.size()), NULL, log_ptr);
            error_report_function(log_ptr);
            return 0;
        }
        return program;
    }

    std::function<void(std::string_view)> error_report_function;
    std::vector<char> log;
    char* log_ptr { nullptr };
};

} // namespace vi
