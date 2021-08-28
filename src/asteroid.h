#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "camera.h"
#include "model.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <memory>

class AsteroidDemo
{
public:
    AsteroidDemo();
    void draw(glm::mat4 &projection, glm::mat4 &view);
    Shader asteroidShader;
    Shader planetShader;
    Model rock;
    Model planet;
private:
    constexpr static unsigned int amount{10000};
    constexpr static float radius{75.0};
    constexpr static float offset{50.5f};
    std::vector<glm::mat4> asteroidMatrices;
};
#endif // ASTEROID_H_