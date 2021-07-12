#include "grass.h"

Grass::Grass(glm::vec3 loc) : location(loc)
{
    //stbi_set_flip_vertically_on_load(false);
    grassShader.use();
    grassShader.setInt("texture1", 0);
    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &grassVBO);
    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
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
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindVertexArray(grassVAO);
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, location);
        grassShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

}
