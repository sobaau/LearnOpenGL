#include "light.h"
#include <string>
#include <glm/glm.hpp>
#include <utility>
Light::Light(glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular) : ambient(ambient), diffuse(diffuse), specular(specular)
{
    
}
