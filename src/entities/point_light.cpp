#include "point_light.h"
#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>
PointLight::PointLight(std::string name, glm::vec3 position,
                       float constant, float linear,
                       float quadratic, glm::vec3 ambient,
                       glm::vec3 diffuse, glm::vec3 specular) : constant(constant),
                                                                linear(linear), quadratic(quadratic),
                                                                Light(ambient, diffuse, specular), Entity(position,name)
{
}