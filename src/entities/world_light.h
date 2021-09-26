#ifndef WORLD_LIGHT_H_
#define WORLD_LIGHT_H_

#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
struct WorldLight : public Light , public Entity {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    std::string name;

    WorldLight() = delete;
    WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
    
    glm::vec3 get_ambient() override;
    glm::vec3 get_diffuse() override;
    glm::vec3 get_specular() override;
    glm::vec3 get_position() override;
    std::string get_name() override;
};
#endif // WORLD_LIGHT_H_