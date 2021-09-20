#include "world_light.h"
#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
WorldLight::WorldLight(std::string name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
    : direction(direction), Light(ambient, diffuse, specular), Entity(position, name)
{
}
