#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <imgui.h>

class imgDemo
{
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;

public:
    explicit imgDemo(GLFWwindow *window);
    void shutdown();
    void draw(glm::vec3 *point);
};