#pragma once
#include "shader.h"
#include "entities/point_light.h"
#include "entities/world_light.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
class Camera;

class CubeDemo
{
public:
    const unsigned int diffuseMap;
    const unsigned int specularMap;
    CubeDemo();
    void clean_up();
    void draw(Camera const &camera, const glm::mat4 &projection, const glm::mat4 &view, const std::vector<PointLight> &pointLights, const WorldLight &worldLight);
    [[nodiscard]] Shader get_shader() const;

private:
    unsigned int VBO{0};
    unsigned int cubeVAO{0};
    unsigned int lightCubeVAO{0};
    std::vector<glm::vec3> cubePositions;
    Shader lightCubeShader;
    Shader lightingShader;
};