#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
#include <imgui.h>
struct WorldLight;
struct PointLight;
class debugUI
{
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    bool show_demo_window;
    bool show_another_window;
    bool open = false;
    int light{0};

    ImVec4 clear_color;
    static void menu_bar(GLFWwindow *window);
    void world_light(glm::vec3 &colour, WorldLight &worldLight);
public:
    explicit debugUI(GLFWwindow *window);
    void shutdown();
    void draw(GLFWwindow *window, std::vector<PointLight> &pointLights, WorldLight &worldLight);
    void editLight(PointLight &light);
};