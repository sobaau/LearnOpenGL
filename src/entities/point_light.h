#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "light.h"
#include "entitiy.h"
#include <glm/glm.hpp>
struct PointLight : public Entity, public Light 
{
    float constant;
    float linear;
    float quadratic;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    std::string name;

    PointLight() = delete;
    PointLight(std::string name, glm::vec3 position,
               float constant, float linear,
               float quadratic, glm::vec3 ambient,
               glm::vec3 diffuse, glm::vec3 specular);

    glm::vec3 get_ambient() override;
    glm::vec3 get_diffuse() override;
    glm::vec3 get_specular() override;
    glm::vec3 get_position() override;
    std::string get_name() override;
};
#endif // POINT_LIGHT_H_