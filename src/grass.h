#ifndef GRASS_H_
#define GRASS_H_

#include <array>
#include <map>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "shader.h"
class Grass
{
    std::array<float, 30> transparentVertices;
    Shader grassShader;
    unsigned int grassTexture;
    std::map<float, glm::vec3> sorted;
    unsigned int grassVAO;
    unsigned int grassVBO;

public:
    std::vector<glm::vec3> locations;
    explicit Grass(std::vector<glm::vec3> loc);
    void cleanUp();
    void Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPos);
};
#endif // GRASS_H_