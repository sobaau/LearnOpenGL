#include "shader.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) : ID(glCreateProgram())
{
    // 1. retrieve the vertex/fragment source code from filePath
    auto vShaderString = loadShader(vertexPath);
    auto fShaderString = loadShader(fragmentPath);

    const GLchar *vShaderCode = vShaderString.c_str();
    const GLchar *fShaderCode = fShaderString.c_str();

    // 2. compile shaders
    // vertex shader
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(std::string_view vertexPath,
               std::string_view geoPath,
               std::string_view fragmentPath)
    : ID(glCreateProgram())
{
    // 1. retrieve the vertex/fragment source code from filePath
    auto vShaderString = loadShader(vertexPath);
    auto fShaderString = loadShader(fragmentPath);
    auto gShaderString = loadShader(geoPath);

    const GLchar *vShaderCode = vShaderString.c_str();
    const GLchar *fShaderCode = fShaderString.c_str();
    const GLchar *gShaderCode = gShaderString.c_str();

    // 2. compile shaders
    // vertex shader
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // geo Shader
    auto geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, nullptr);
    glCompileShader(geometry);
    checkCompileErrors(geometry, "GEOMETRY");
    // shader Program
    glAttachShader(ID, vertex);
    glAttachShader(ID, geometry);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(ID);
}
// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::checkCompileErrors(unsigned int shader, std::string_view type)
{
    auto success = 0;
    std::string infoLog;
    constexpr auto logSize = 1024;
    infoLog.resize(logSize);
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == 0) {
            glGetShaderInfoLog(shader, logSize, nullptr, &infoLog[0]);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog
                      << "\n -- --------------------------------------------------- "
                         "-- "
                      << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(shader, logSize, nullptr, &infoLog[0]);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog
                      << "\n -- --------------------------------------------------- "
                         "-- "
                      << std::endl;
        }
    }
}

std::string Shader::loadShader(std::string_view shaderPath)
{
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
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        std::cout << shaderPath << std::endl;

        return "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ \n";
    }
}
