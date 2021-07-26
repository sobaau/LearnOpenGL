#include "cube_demo.h"
#include "camera.h" // for Camera
#include "texture_loader.h"
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <string> // for operator+, to_string
#include <vector> // for allocator, vector

cubeDemo::cubeDemo() : vertices({// positions          // normals           // texture coords
                                 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                                 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                                 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                                 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                                 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                                 -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

                                 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                                 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                                 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                                 -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                                 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                                 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                 -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                                 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                                 -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                                 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                                 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                                 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                                 -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                                 -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

                                 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                                 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                                 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}),
                       cubePositions({glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(2.0f, 5.0f, -15.0f),
                                      glm::vec3(-1.5f, -2.2f, -2.5f),
                                      glm::vec3(-3.8f, -2.0f, -12.3f),
                                      glm::vec3(2.4f, -0.4f, -3.5f),
                                      glm::vec3(-1.7f, 3.0f, -7.5f),
                                      glm::vec3(1.3f, -2.0f, -2.5f),
                                      glm::vec3(1.5f, 2.0f, -2.5f),
                                      glm::vec3(1.5f, 0.2f, -1.5f),
                                      glm::vec3(-1.3f, 1.0f, -1.5f)}),
                       lightCubeShader("shaders/shader.vert", "shaders/light_cube.frag"),
                       lightingShader("shaders/shader.vert", "shaders/light.frag"),
                       diffuseMap(loadTexture("textures/container2.png")),
                       specularMap(loadTexture("textures/container2_specular.png"))
{
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
}

void cubeDemo::Draw(Camera const &camera, const unsigned int &SCR_WIDTH, const unsigned int &SCR_HEIGHT, const glm::mat4 &projection, const glm::mat4 &view, const std::vector<glm::vec3> &pointLightPositions)
{

    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader.use();
    lightingShader.setVec3("viewPos", camera.Position);
    lightingShader.setFloat("material.shininess", 32.0f);
    /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
    // directional light
    lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    for (auto i = 0; i < pointLightPositions.size(); i++) {
        lightingShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
        lightingShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
        lightingShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
        lightingShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
    }
    lightingShader.setVec3("spotLight.position", camera.Position);
    lightingShader.setVec3("spotLight.direction", camera.Front);
    lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("spotLight.constant", 1.0f);
    lightingShader.setFloat("spotLight.linear", 0.09f);
    lightingShader.setFloat("spotLight.quadratic", 0.032f);
    lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    // view/projection transformations
    lightingShader.setMat4("projection", projection);
    lightingShader.setMat4("view", view);

    // world transformation
    auto model = glm::mat4(1.0f);
    lightingShader.setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    // render containers
    glBindVertexArray(cubeVAO);

    for (auto pos : cubePositions) {
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // also draw the lamp object(s)
    lightCubeShader.use();
    lightCubeShader.setMat4("projection", projection);
    lightCubeShader.setMat4("view", view);
    glBindVertexArray(0);

    // we now draw as many light bulbs as we have point lights.
    glBindVertexArray(lightCubeVAO);
    for (auto pointLightPosition : pointLightPositions) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPosition);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        lightCubeShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}

void cubeDemo::cleanUp()
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}