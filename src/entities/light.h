#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/glm.hpp>
#include <string>
struct Light {
    std::string name;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Light() = delete;
    Light(std::string &name, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular);
};
#endif // LIGHT_H_