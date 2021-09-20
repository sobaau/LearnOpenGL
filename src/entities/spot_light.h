#ifndef SPOT_LIGHT_H_
#define SPOT_LIGHT_H_

#include "light.h"
#include <glm/glm.hpp>
struct SpotLight : public Light
{
    glm::vec3 direction;
    glm::vec3 constant;
    glm::vec3 linear;
    glm::vec3 quadratic;
    glm::vec3 cutOff;
    glm::vec3 outerCutOff;
};
#endif // SPOT_LIGHT_H_