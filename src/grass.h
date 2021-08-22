#ifndef GRASS_H_
#define GRASS_H_

#include "shader.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <map>
#include <vector>
class Grass
{
    std::vector<float> transparentVertices;
    unsigned int grassTexture;
    std::map<float, glm::vec3> sorted;
    unsigned int grassVAO, grassVBO;

public:
    Shader grassShader;
    std::vector<glm::vec3> locations;
    explicit Grass(std::vector<glm::vec3> loc);
    void clean_up();
    void draw(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPos);
};
#endif // GRASS_H_