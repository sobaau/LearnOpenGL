#include "world_light.h"
#include "light.h"
#include <glm/glm.hpp>
#include <string>
WorldLight::WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : direction(direction), Light(name, ambient, diffuse, specular)
{
}
