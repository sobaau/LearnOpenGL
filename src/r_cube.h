#ifndef R_CUBE_H_
#define R_CUBE_H_

#include "shader.h"       // for Shader
#include <glm/mat4x4.hpp>
#include <array>
class Camera;

class ReflCube
{
    std::array<float, 216> vertices;
    unsigned int RVAO, RVBO;
    Shader reflShader;

public:
    ReflCube();
    void draw(glm::mat4 &view, glm::mat4 &projection, Camera &camera);
};

#endif // R_CUBE_H_