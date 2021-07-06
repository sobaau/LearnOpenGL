#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

class imgDemo{
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    bool show_demo_window;
    bool show_another_window;
    GLFWwindow* window;
    ImVec4 clear_color;
public:
    imgDemo(GLFWwindow* window);
    ~imgDemo();
    void draw();
};