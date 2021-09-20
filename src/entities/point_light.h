#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
struct PointLight : public Light, public Entity
{
    float constant;
    float linear;
    float quadratic;
    PointLight() = delete;
    PointLight(std::string name, glm::vec3 position,
               float constant, float linear,
               float quadratic, glm::vec3 ambient,
               glm::vec3 diffuse, glm::vec3 specular);
};
#endif // POINT_LIGHT_H_