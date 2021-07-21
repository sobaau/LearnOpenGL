#ifndef __MAIN_H__
#define __MAIN_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "cube_demo.h"
#include "shader.h"
#include "camera.h"
#include "img_demo.h"
#include "model.h"
#include "grass.h"
#include "sky_box.h"
#include "r_cube.h"
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

#endif // __MAIN_H__