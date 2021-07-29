#pragma once
#include "shader.h"
#include <array>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
class Camera;

class cubeDemo
{
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    const std::array<float, 288> vertices;
    std::array<glm::vec3, 10> cubePositions;
    Shader lightCubeShader;
    Shader lightingShader;

public:
    const unsigned int diffuseMap;
    const unsigned int specularMap;
    cubeDemo();
    void cleanUp();
    void Draw(Camera const &camera, const glm::mat4 &projection, const glm::mat4 &view, const std::vector<glm::vec3> &pointLightPositions);
};