#include "light.h"
#include <string>
#include <glm/glm.hpp>
#include <utility>
Light::Light(std::string &name, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular) : name(std::move(name)), ambient(ambient), diffuse(diffuse), specular(specular)
{
    
}
