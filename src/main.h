#ifndef MAIN_H_
#define MAIN_H_

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
};
 struct vec3c {
        float x;
        float y;
        float z;
    };
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void renderLights(Shader &ourShader, std::vector<glm::vec3> &pointLightPositions,vec3c colour);
void processInput(GLFWwindow *window);

#endif // MAIN_H_