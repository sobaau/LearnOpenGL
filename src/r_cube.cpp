#include "r_cube.h"
#include "camera.h"                      // for Camera
#include "glad/glad.h"                   // for GL_ARRAY_BUFFER, GL_CULL_FACE
#include <glm/ext/matrix_transform.hpp>
#include <string>
ReflCube::ReflCube() :
reflShader("shaders/reflection.vert","shaders/reflection.frag")
{
    glGenVertexArrays(1,&RVAO);
    glGenBuffers(1, &RVBO);
    glBindVertexArray(RVAO);
    glBindBuffer(GL_ARRAY_BUFFER, RVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    reflShader.use();
    reflShader.setInt("skybox", 0);
}

void ReflCube::draw(glm::mat4 &view, glm::mat4 &projection, Camera &camera) 
{
    glDisable(GL_CULL_FACE);  
    reflShader.use();
    reflShader.setVec3("cameraPos", camera.Position);
    reflShader.setMat4("view", view);
    reflShader.setMat4("projection", projection);
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
    reflShader.setMat4("model", model);
    glBindVertexArray(RVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glEnable(GL_CULL_FACE);	  
}
