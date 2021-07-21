#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <array>
#include <iostream>
#include <vector>
#include "texture_loader.h"
#include "camera.h"
#include "shader.h"

class cubeDemo {
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    const std::array<float, 288> vertices;
    std::array<glm::vec3,10> cubePositions;
    Shader lightCubeShader;
    Shader lightingShader;

public:
    glm::vec3 lightPos;
    const unsigned int diffuseMap;
    const unsigned int specularMap;
    cubeDemo();
    void cleanUp();
    void Draw(Camera const &camera, const unsigned int &SCR_WIDTH, const unsigned int &SCR_HEIGHT, const glm::mat4 &projection, const glm::mat4 &view, const std::vector<glm::vec3> &pointLightPositions);
};