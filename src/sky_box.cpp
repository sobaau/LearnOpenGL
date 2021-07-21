#include "texture_loader.h"
#include "sky_box.h"

SkyBox::SkyBox() :  faces(
    {
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/right.jpg",
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/left.jpg",
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/top.jpg",
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/bottom.jpg",
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/front.jpg",
        "/Users/soba/dev/code/LearnOpenGL/src/textures/skybox/back.jpg"
    }), 
     skyboxVertices ({
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
}),
    skyBoxShader("shaders/sky_box.vert","shaders/sky_box.frag"),
    skyTexture(loadCubemap(faces))
{
    glGenVertexArrays(1,&skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    skyBoxShader.use();
    skyBoxShader.setInt("skybox", 0);
}

void SkyBox::draw(glm::mat4 &view, glm::mat4 &projection) 
{
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    skyBoxShader.use();
    skyBoxShader.setMat4("view", view);
    skyBoxShader.setMat4("projection", projection);
    glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS); // set depth function back to default
}
