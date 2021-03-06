#include "sky_box.h"
#include "texture_loader.h"
#include <string>
#include <glad/glad.h>

SkyBox::SkyBox()
    : faces(
          {"../assets/textures/skybox/right.jpg",
           "../assets/textures/skybox/left.jpg",
           "../assets/textures/skybox/top.jpg",
           "../assets/textures/skybox/bottom.jpg",
           "../assets/textures/skybox/front.jpg",
           "../assets/textures/skybox/back.jpg"}),
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
      skyBoxShader("../assets/shaders/sky_box.vert", "../assets/shaders/sky_box.frag"),
      skyTexture(load_cubemap(faces))
{
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(skyboxVertices.size() * sizeof(float)), &skyboxVertices.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    skyBoxShader.use();
    skyBoxShader.set_int("skybox", 0);
}

void SkyBox::draw(const glm::mat4 &view, const glm::mat4 &projection)
{
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    skyBoxShader.use();
    skyBoxShader.set_mat4("view", view);
    skyBoxShader.set_mat4("projection", projection);
    glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    constexpr auto nVertex = 36;
    glDrawArrays(GL_TRIANGLES, 0, nVertex);
    glDepthFunc(GL_LESS); // set depth function back to default
}
unsigned int SkyBox::get_texture(){
    return skyTexture;
}