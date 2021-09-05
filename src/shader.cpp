#include "shader.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <future>

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) : id(glCreateProgram())
{
    // 1. retrieve the vertex/fragment source code from filePath

    std::future<std::string> vertexThread = std::async(&load_shader,vertexPath);
    std::future<std::string> fragmentThread = std::async(&load_shader,fragmentPath);
    auto vShaderString = vertexThread.get();
    auto fShaderString = fragmentThread.get();

    const GLchar *vShaderCode = vShaderString.c_str();
    const GLchar *fShaderCode = fShaderString.c_str();

    // 2. compile shaders
    // vertex shader
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX", vertexPath);
    // fragment Shader
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT", fragmentPath);

    // shader Program
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    check_compile_errors(id, "PROGRAM", "");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(std::string_view vertexPath,
               std::string_view geoPath,
               std::string_view fragmentPath)
    : id(glCreateProgram())
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::future<std::string> vertexThread = std::async(&load_shader,vertexPath);
    std::future<std::string> fragmentThread = std::async(&load_shader,fragmentPath);
    std::future<std::string> geoThread = std::async(&load_shader,geoPath);
    auto vShaderString = vertexThread.get();
    auto fShaderString = fragmentThread.get();
    auto gShaderString = geoThread.get();

    const GLchar *vShaderCode = vShaderString.c_str();
    const GLchar *fShaderCode = fShaderString.c_str();
    const GLchar *gShaderCode = gShaderString.c_str();

    // 2. compile shaders
    // vertex shader
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX", vertexPath);
    // fragment Shader
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT", fragmentPath);
    // geo Shader
    auto geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, nullptr);
    glCompileShader(geometry);
    check_compile_errors(geometry, "GEOMETRY", geoPath);
    // shader Program
    glAttachShader(id, vertex);
    glAttachShader(id, geometry);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    check_compile_errors(id, "PROGRAM", "");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(id);
}
// utility uniform functions
void Shader::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::set_vec4(const std::string &name, float x, float y, float z,
                     float w) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::check_compile_errors(unsigned int shader, std::string_view type, std::string_view path)
{
    auto success = 0;
    std::string infoLog;
    constexpr auto logSize = 1024;
    infoLog.resize(logSize);
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == 0) {
            glGetShaderInfoLog(shader, logSize, nullptr, &infoLog[0]);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << " at " << path.data() << "\n"
                      << infoLog
                      << "\n -- --------------------------------------------------- "
                         "-- "
                      << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(shader, logSize, nullptr, &infoLog[0]);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << " at " << path.data() <<  "\n"
                      << infoLog
                      << "\n -- --------------------------------------------------- "
                         "-- "
                      << std::endl;
        }
    }
}

std::string Shader::load_shader(std::string_view shaderPath)
{
    std::cout << "Loading " << shaderPath << "\n";
    // 1. retrieve the vertex/fragment source code from filePath
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        shaderFile.open(shaderPath.data());
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();

        return shaderStream.str();
    } catch (std::ifstream::failure const &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << "\n";
        std::cout << shaderPath << "\n";

        return "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ \n";
    }
}
