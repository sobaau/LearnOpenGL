#ifndef __GRASS_H__
#define __GRASS_H__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "shader.h"
#include "texture_loader.h"

class Grass
{
    float transparentVertices[30] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f
        };

    glm::vec3 location;
#ifdef __APPLE__
    Shader grassShader{"/Users/soba/dev/code/LearnOpenGL/src/shaders/grass.vert",
                       "/Users/soba/dev/code/LearnOpenGL/src/shaders/grass.frag"};
    unsigned int grassTexture = loadTexture("/Users/soba/dev/code/LearnOpenGL/src/textures/grass.png");
#elif _WIN32
    Shader grassShader{"shaders/grass.vert", "shaders/grass.frag"};
    unsigned int grassTexture = loadTexture("textures/grass.png");
#endif
    unsigned int grassVAO;
    unsigned int grassVBO;

public:
    Grass(glm::vec3 loc);
    ~Grass();
    void Draw(glm::mat4 projection, glm::mat4 view);
};
#endif // __GRASS_H__