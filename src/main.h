#ifndef MAIN_H_
#define MAIN_H_
#include "entities/world_light.h"
#include "entities/point_light.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
class Grass;
class Model;
class Shader;
class cubeDemo;

struct GlobalSettings {
    int SCR_WIDTH;
    int SCR_HEIGHT;
    double lastX;
    double lastY;
    bool firstMouse;
    float deltaTime;
    float lastFrame;
    bool processMouse;
    bool debug;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void renderLights(const Shader &ourShader, std::vector<PointLight> &pointLights, WorldLight &worldLight);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // MAIN_H_