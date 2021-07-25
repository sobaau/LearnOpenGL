#ifndef MAIN_H_
#define MAIN_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec3.hpp>
#define STB_IMAGE_IMPLEMENTATION
class Grass;
class Model;
class Shader;
class cubeDemo;
struct Framebuffer
{
    unsigned int quadVAO, quadVBO, framebuffer, textureColorbuffer, rbo;
};
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void renderLights(Shader &ourShader, std::vector<glm::vec3> &pointLightPositions);
void processInput(GLFWwindow *window);
Framebuffer initFrameBuffer();
void mirror(Framebuffer &framebuff, cubeDemo &cubes, Shader &sponzaShader, Model &sponzaModel, std::vector<glm::vec3> &pointLightPositions, Grass &grass);
void mirrorQuad(Shader &screenShader, Framebuffer const &framebuff);

#endif // MAIN_H_