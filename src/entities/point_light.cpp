#include "point_light.h"
#include "entitiy.h"
#include "light.h"
#include <glm/glm.hpp>
#include <string>
PointLight::PointLight(std::string name, glm::vec3 position,
                       float constant, float linear,
                       float quadratic, glm::vec3 ambient,
                       glm::vec3 diffuse, glm::vec3 specular) : constant(constant),
                                                                linear(linear), quadratic(quadratic),
                                                                ambient(ambient), diffuse(diffuse), specular(specular), position(position), name(std::move(name))
{
}

glm::vec3 PointLight::get_ambient() {
    
    return ambient;
}

glm::vec3 PointLight::get_diffuse() {
    
    return diffuse;
}

glm::vec3 PointLight::get_specular() {
    
    return specular;
}

glm::vec3 PointLight::get_position() {
    
    return position;
}

std::string PointLight::get_name() {
    
    return name;
}
