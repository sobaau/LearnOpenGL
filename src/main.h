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
void renderLights(Shader &ourShader, glm::vec3 *pointLightPositions);
void processInput(GLFWwindow *window);
Framebuffer initFrameBuffer();
void mirror(Framebuffer &framebuff, cubeDemo &cubes, Shader &sponzaShader, Model &sponzaModel, glm::vec3 *pointLightPositions, Grass &grass);
void mirrorQuad(Shader &screenShader, Framebuffer const &framebuff);
unsigned int loadCubemap(vector<std::string> faces);
// settings
unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
auto lastX = SCR_WIDTH / 2.0f;
auto lastY = SCR_HEIGHT / 2.0f;
auto firstMouse = true;
// timing
auto deltaTime = 0.0f; // time between current frame and last frame
auto lastFrame = 0.0f;