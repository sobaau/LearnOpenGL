#include <stb_image.h>
#include "texture_loader.h"
#include "grass.h"

Grass::Grass(glm::vec3 loc) : location(loc),
                              grassShader("/Users/soba/dev/code/LearnOpenGL/src/shaders/grass.vert", 
                              "/Users/soba/dev/code/LearnOpenGL/src/shaders/grass.frag")

{
    stbi_set_flip_vertically_on_load(false);
    grassTexture = loadTexture("/Users/soba/dev/code/LearnOpenGL/src/textures/grass.png");
    grassShader.use();
    grassShader.setInt("texture1", 0);
    stbi_set_flip_vertically_on_load(true);
    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &grassVBO);
    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
}

Grass::~Grass() 
{
    glDeleteVertexArrays(1, &grassVAO);
    glDeleteBuffers(1, &grassVBO);
}

void Grass::Draw(glm::mat4 projection, glm::mat4 view)
{
        grassShader.use();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        glBindVertexArray(grassVAO);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, location);
        grassShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
}
