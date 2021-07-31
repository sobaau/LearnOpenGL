#include "sky_box.h"
#include "texture_loader.h"
#include <glad/glad.h>
#include <string>

SkyBox::SkyBox()
    : faces(
          {"textures/skybox/right.jpg",
           "textures/skybox/left.jpg",
           "textures/skybox/top.jpg",
           "textures/skybox/bottom.jpg",
           "textures/skybox/front.jpg",
           "textures/skybox/back.jpg"}),
      skyboxVertices({// positions
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,

                      -1.0f, -1.0f, 1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, 1.0f,
                      -1.0f, -1.0f, 1.0f,

                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,

                      -1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f,
                      -1.0f, -1.0f, 1.0f,

                      -1.0f, 1.0f, -1.0f,
                      1.0f, 1.0f, -1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      -1.0f, 1.0f, -1.0f,

                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f}),
      skyBoxShader("shaders/sky_box.vert", "shaders/sky_box.frag"),
      skyboxVAO(0),
      skyboxVBO(0),
      skyTexture(loadCubemap(faces))
{
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(skyboxVertices.size() * sizeof(float)), &skyboxVertices.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    skyBoxShader.use();
    skyBoxShader.setInt("skybox", 0);
}

void SkyBox::draw(glm::mat4 &view, glm::mat4 &projection)
{
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    skyBoxShader.use();
    skyBoxShader.setMat4("view", view);
    skyBoxShader.setMat4("projection", projection);
    glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    constexpr auto nVertex = 36;
    glDrawArrays(GL_TRIANGLES, 0, nVertex);
    glDepthFunc(GL_LESS); // set depth function back to default
}
