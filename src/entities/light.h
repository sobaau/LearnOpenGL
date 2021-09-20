#ifndef LIGHT_H_
#define LIGHT_H_
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
struct Light {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Light() = delete;
    Light(glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular);
};
#endif // LIGHT_H_