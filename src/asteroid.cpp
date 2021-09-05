
#include "asteroid.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <random>
#include <string_view>
#include <utility>
#include <glad/glad.h>

AsteroidDemo::AsteroidDemo() : asteroidShader("../assets/shaders/asteroid.vert", "../assets/shaders/light.frag"),
                               planetShader("../assets/shaders/shader.vert", "../assets/shaders/light.frag"),
                               rock("../assets/rock/rock.obj"),
                               planet("../assets/planet/planet.obj")
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 2147483647);
    asteroidMatrices.reserve(amount);
    for (unsigned int i = 0; i < amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = static_cast<float>(i) / static_cast<float>(amount) * 360.0f;
        float displacement = static_cast<float>((uniform_dist(rd) % static_cast<int>((2 * offset * 100)))) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = static_cast<float>((uniform_dist(rd) % static_cast<int>((2 * offset * 100)))) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = static_cast<float>((uniform_dist(rd) % static_cast<int>((2 * offset * 100)))) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((uniform_dist(rd) % 20)) / 100.0f + 0.05f;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        auto rotAngle = static_cast<float>((uniform_dist(rd) % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        asteroidMatrices.push_back(model);
    }
    // vertex buffer object
    unsigned int buffer{0};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &asteroidMatrices[0], GL_STATIC_DRAW);

    for (auto const &m : rock.meshes) {
        unsigned int VAO = m.VAO;
        glBindVertexArray(VAO);
        // vertex attributes
        std::size_t vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, static_cast<int>(4 * vec4Size), nullptr);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, static_cast<int>(4 * vec4Size), reinterpret_cast<void *>((1 * vec4Size)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, static_cast<int>(4 * vec4Size), reinterpret_cast<void *>((2 * vec4Size)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, static_cast<int>(4 * vec4Size), reinterpret_cast<void *>((3 * vec4Size)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
}

void AsteroidDemo::draw(glm::mat4 &projection, glm::mat4 &view)
{

    planetShader.use();
    planetShader.set_mat4("projection", projection);
    planetShader.set_mat4("view", view);

    // draw planet
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    planetShader.set_mat4("model", model);
    planet.draw(planetShader);

    // draw meteorites
    asteroidShader.use();
    asteroidShader.set_mat4("projection", projection);
    asteroidShader.set_mat4("view", view);
    //asteroidShader.setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rock.texturesLoaded[0].id);
    for (auto const &m : rock.meshes) {
        glBindVertexArray(m.VAO);
        glDrawElementsInstanced(
            GL_TRIANGLES, static_cast<int>(m.indices.size()), GL_UNSIGNED_INT, nullptr, amount);
    }
}
