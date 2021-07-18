#pragma once
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class imgDemo{
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;
public:
    imgDemo(GLFWwindow* window);
    ~imgDemo();
    void draw(glm::vec3 *point);
};