#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WorldLight;
struct PointLight;
struct Camera;
class DebugUI
{    
public:
    explicit DebugUI(GLFWwindow *window);
    void shutdown();
    void draw(GLFWwindow *window, std::vector<PointLight> &pointLights, WorldLight &worldLight, unsigned int fb, Camera &camera);

private:
    bool show_demo_window;
    bool show_another_window;
    bool open = false;
    int light{0};

    ImVec4 clear_color;
    static void menu_bar(GLFWwindow *window);
    void world_light(WorldLight &worldLight);
    void docking_space();
    void edit_light(PointLight &light);
    void light_list(std::vector<PointLight> &pointLights, Camera &camera);
    void render_viewport(GLFWwindow *window, unsigned int fb);
};