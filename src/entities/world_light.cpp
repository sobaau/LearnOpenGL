#include "world_light.h"
#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
#include <algorithm>

WorldLight::WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
    : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular), position(position), name(std::move(name))
{
}
glm::vec3 WorldLight::get_ambient() {
    
    return ambient;
}

glm::vec3 WorldLight::get_diffuse() {
    
    return diffuse;
}

glm::vec3 WorldLight::get_specular() {
    
    return specular;
}

glm::vec3 WorldLight::get_position() {
    
    return position;
}

std::string WorldLight::get_name() {
    
    return name;
}