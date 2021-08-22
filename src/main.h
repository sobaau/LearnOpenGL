#ifndef MAIN_H_
#define MAIN_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "entities/point_light.h"
#include "entities/world_light.h"
#include <glm/vec3.hpp>
#include <vector>
class Grass;
class Model;
class Shader;
class CubeDemo;
class SkyBox;
class AsteroidDemo;
class ReflCube;

struct GlobalSettings
{
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
void render_lights(const Shader &ourShader, std::vector<PointLight> &pointLights, WorldLight &worldLight);
void process_input(GLFWwindow *window, bool &mKeyPressed);
void render_scene(Shader &sponzaShader, Model &sponzaModel, CubeDemo &cubes, ReflCube &reflCube, AsteroidDemo &as, Grass &grass, WorldLight &wLight, std::vector<PointLight> &pointLights, SkyBox &skyBox);

#endif // MAIN_H_