#include "cube_demo.h"
#include "camera.h" // for Camera
#include "cube_layout.h"
#include "texture_loader.h"
#include "entities/point_light.h"
#include "entities/world_light.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <string> // for operator+, to_string
#include <vector> // for allocator, vector

cubeDemo::cubeDemo()
    : cubePositions({glm::vec3(0.0f, 0.0f, 0.0f),
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
    cubeLayout cube;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(cube.verticesSize + cube.normalsSize + cube.texSize), nullptr , GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(cube.verticesSize), &cube.vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(cube.verticesSize), static_cast<GLsizeiptr>(cube.normalsSize), &cube.normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(cube.normalsSize + cube.verticesSize), static_cast<GLsizeiptr>(cube.texSize), &cube.textures[0]);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void *>(cube.verticesSize));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void *>(cube.normalsSize + cube.verticesSize));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
}

void cubeDemo::draw(Camera const &camera, const glm::mat4 &projection, const glm::mat4 &view, const std::vector<PointLight> &pointLights, const WorldLight &worldLight)
{
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
    for (const auto &pointLight : pointLights) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLight.position);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        lightCubeShader.setMat4("model", model);
        lightCubeShader.setVec3("diffuse",pointLight.diffuse);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}

Shader cubeDemo::getShader() const
{
    return lightingShader;
}

void cubeDemo::cleanUp()
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}