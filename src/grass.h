#ifndef __GRASS_H__
#define __GRASS_H__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>
#include <map>
#include <array>
#include "camera.h"
#include "shader.h"
#include "texture_loader.h"

class Grass
{
    std::array<float, 30> transparentVertices = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
        };

    Shader grassShader{"shaders/grass.vert", "shaders/grass.frag"};
    unsigned int grassTexture = loadTexture("textures/grass.png");
    std::map<float, glm::vec3> sorted;
    unsigned int grassVAO;
    unsigned int grassVBO;

public:
    std::vector<glm::vec3> locations;
    explicit Grass(std::vector<glm::vec3> loc);
    void cleanUp();
    void Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPos);
};
#endif // __GRASS_H__