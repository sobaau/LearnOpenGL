#ifndef WORLD_LIGHT_H_
#define WORLD_LIGHT_H_

#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
struct WorldLight : public Light , public Entity{
    glm::vec3 direction;
    WorldLight() = delete;
    WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
};
#endif // WORLD_LIGHT_H_