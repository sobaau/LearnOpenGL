#ifndef __SKY_BOX_H__
#define __SKY_BOX_H__
#include <vector>
#include <array>
#include <iostream>
#include <glm/glm.hpp>
#include "shader.h"

class SkyBox {
    std::vector<std::string> faces;
    std::array<float,108> skyboxVertices;
    Shader skyBoxShader;
    unsigned int skyboxVAO, skyboxVBO;;
public:
    SkyBox();
    unsigned int skyTexture;
    void draw(glm::mat4 &view, glm::mat4 &projection);
};

#endif // __SKY_BOX_H__