#ifndef SHADER_H
#define SHADER_H
#include <glm/fwd.hpp>
#include <iosfwd>
#include <string>
class Shader
{
public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the shader
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    Shader(std::string_view vertexPath, std::string_view geoPath, std::string_view fragmentPath);
    // use/activate the shader
    void use() const;
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    static void checkCompileErrors(unsigned int shader, std::string_view type);
    static std::string loadShader(std::string_view shaderPath);
};

#endif