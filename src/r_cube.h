#ifndef R_CUBE_H_
#define R_CUBE_H_

#include "shader.h"       // for Shader
#include <glm/mat4x4.hpp>
#include <vector>
class Camera;

class ReflCube
{
public:
    ReflCube();
    void draw(glm::mat4 &view, glm::mat4 &projection, Camera &camera);

private:
    std::vector<float> vertices;
    Shader reflShader;
    unsigned int RVAO{0};
    unsigned int RVBO{0};
};

#endif // R_CUBE_H_