#ifndef R_CUBE_H_
#define R_CUBE_H_

#include "shader.h"       // for Shader
#include <glm/mat4x4.hpp>
#include <vector>
class Camera;

class ReflCube
{
    std::vector<float> vertices;
    Shader reflShader;
    unsigned int RVAO;
    unsigned int RVBO;

public:
    ReflCube();
    void draw(glm::mat4 &view, glm::mat4 &projection, Camera &camera);
};

#endif // R_CUBE_H_