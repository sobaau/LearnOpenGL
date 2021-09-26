#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/glm.hpp>
struct Light {
    virtual glm::vec3 get_ambient() = 0;
    virtual glm::vec3 get_diffuse() = 0;
    virtual glm::vec3 get_specular() = 0;
};
#endif // LIGHT_H_