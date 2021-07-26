#ifndef SKY_BOX_H_
#define SKY_BOX_H_

#include "shader.h"
#include <array>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class SkyBox
{
    std::vector<std::string> faces;
    std::array<float, 108> skyboxVertices;
    Shader skyBoxShader;
    unsigned int skyboxVAO, skyboxVBO;

public:
    SkyBox();
    unsigned int skyTexture;
    void draw(glm::mat4 &view, glm::mat4 &projection);
};

#endif // SKY_BOX_H_