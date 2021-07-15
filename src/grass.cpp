#include "grass.h"
Grass::Grass(std::vector<glm::vec3> loc) : locations(loc)
{
    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &grassVBO);
    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    grassShader.use();
    grassShader.setInt("texture1", 0);

}

void Grass::cleanUp() 
{
    glDeleteVertexArrays(1, &grassVAO);
    glDeleteBuffers(1, &grassVBO);
}


void Grass::Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPos)
{
        glDisable(GL_CULL_FACE);  
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindVertexArray(grassVAO);
        grassShader.use();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        for (unsigned int i = 0; i < locations.size(); i++)
        {
            float distance = glm::length(cameraPos - locations[i]);
            sorted[distance] = locations[i];
        }
       for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);
            grassShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // for (auto loc : locations){
        //     auto model = glm::mat4(1.0f);
        //     model = glm::translate(model, loc);
        //     grassShader.setMat4("model", model);
        //     glDrawArrays(GL_TRIANGLES, 0, 6);
        // }
        sorted.clear();
        glEnable(GL_CULL_FACE);  

        glBindVertexArray(0);
}