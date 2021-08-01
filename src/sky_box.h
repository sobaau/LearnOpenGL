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
    std::vector<float> skyboxVertices;
    Shader skyBoxShader;
    unsigned int skyboxVAO{0}; 
    unsigned int skyboxVBO{0};

public:
    SkyBox();
    void draw(glm::mat4 &view, glm::mat4 &projection);
    unsigned int skyTexture;
};

#endif // SKY_BOX_H_