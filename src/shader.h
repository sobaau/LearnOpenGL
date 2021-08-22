#ifndef SHADER_H
#define SHADER_H
#include <glm/fwd.hpp>
#include <iosfwd>
#include <string>
class Shader
{
public:
    // the program ID
    unsigned int id;
    // constructor reads and builds the shader
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    Shader(std::string_view vertexPath, std::string_view geoPath, std::string_view fragmentPath);
    // use/activate the shader
    void use() const;
    // utility uniform functions
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_vec2(const std::string &name, const glm::vec2 &value) const;
    void set_vec2(const std::string &name, float x, float y) const;
    void set_vec3(const std::string &name, const glm::vec3 &value) const;
    void set_vec3(const std::string &name, float x, float y, float z) const;
    void set_vec4(const std::string &name, const glm::vec4 &value) const;
    void set_vec4(const std::string &name, float x, float y, float z, float w) const;
    void set_mat2(const std::string &name, const glm::mat2 &mat) const;
    void set_mat3(const std::string &name, const glm::mat3 &mat) const;
    void set_mat4(const std::string &name, const glm::mat4 &mat) const;

private:
    static void check_compile_errors(unsigned int shader, std::string_view type,std::string_view path);
    static std::string load_shader(std::string_view shaderPath);
};

#endif