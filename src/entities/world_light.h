#ifndef WORLD_LIGHT_H_
#define WORLD_LIGHT_H_

#include "light.h"
#include <glm/glm.hpp>
#include <string>
struct WorldLight : public Light{
    glm::vec3 direction;
    WorldLight() = delete;
    WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};
#endif // WORLD_LIGHT_H_