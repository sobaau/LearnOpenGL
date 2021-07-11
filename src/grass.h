#ifndef __GRASS_H__
#define __GRASS_H__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "shader.h"
#include "texture_loader.h"
class Grass {
    float transparentVertices[5*6] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f};

    glm::vec3 location;
    Shader grassShader;
    unsigned int grassTexture;
    unsigned int grassVAO;
    unsigned int grassVBO;

public:
    Grass(glm::vec3 loc);
    ~Grass();
    void Draw(glm::mat4 projection, glm::mat4 view);
};
#endif // __GRASS_H__