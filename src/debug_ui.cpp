#include "debug_ui.h"
#include "camera.h"
#include "entities/point_light.h"
#include "entities/world_light.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

debugUI::debugUI(GLFWwindow *window) : show_demo_window(true), show_another_window(false), clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    const char *glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void debugUI::draw(GLFWwindow *window, std::vector<PointLight> &pointLights, WorldLight &worldLight, unsigned int fb, Camera &camera)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    world_light(worldLight);
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    lightList(pointLights, camera);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void debugUI::renderViewPort(GLFWwindow *window, unsigned int fb)
{
    ImGui::NewFrame();
    menu_bar(window);
    ImGui::Begin("GameWindow");
    {
        ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Always);
        ImGui::BeginChild("GameRender");
        ImVec2 wsize = ImGui::GetWindowSize();
        ImGui::Image((ImTextureID)fb, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}

void debugUI::editLight(PointLight &light)
{
    float step = .1f;
    ImGui::Begin(light.name.c_str());
    ImGui::SliderFloat3("Ambient", &light.ambient.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Position", &light.position.x, -100.f, 100.f);
    ImGui::PushItemWidth(100.f);
    ImGui::InputScalar("x", ImGuiDataType_Float, &light.position.x, &step);
    ImGui::SameLine();
    ImGui::InputScalar("y", ImGuiDataType_Float, &light.position.y, &step);
    ImGui::SameLine();
    ImGui::InputScalar("z", ImGuiDataType_Float, &light.position.z, &step);
    ImGui::PopItemWidth();
    ImGui::SliderFloat3("Specular", &light.specular.x, 0.0f, 1.0f);
    ImGui::SliderFloat("constant", &light.constant, 0.0f, 1.0f);
    ImGui::SliderFloat("linear", &light.linear, 0.0f, 1.0f);
    ImGui::SliderFloat("quadratic", &light.quadratic, 0.0f, 1.0f);
    ImGui::SliderFloat3("Colour", &light.diffuse.x, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", &light.diffuse.x);
    ImGui::End();
}

void debugUI::lightList(std::vector<PointLight> &pointLights, Camera &camera)
{
    if (ImGui::TreeNode("Point Lights")) {
        for (int i = 0; i < pointLights.size(); i++) {
            // Use SetNextItemOpen() so set the default state of a node to be open. We could
            // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
            if (i == 0) {
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            }
            if (ImGui::TreeNode((void *)(intptr_t)i, "%s", pointLights[i].name.c_str())) {
                if (ImGui::SmallButton("Edit")) {
                    light = i;
                    open = true;
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Delete")) {
                    open = false;
                    pointLights.erase(pointLights.begin() + i);
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Move to Camera")) {
                    pointLights[i].position = camera.Position;
                }
                ImGui::Text("Size is %i", pointLights.size());
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    if (open) {
        if (light < pointLights.size()) {
            editLight(pointLights[light]);
        }
    }
}

void debugUI::menu_bar(GLFWwindow *window)
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit")) {
                glfwSetWindowShouldClose(window, true);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void debugUI::world_light(WorldLight &worldLight)
{
    ImGui::Begin("World Light");
    ImGui::SliderFloat3("Ambient", &worldLight.ambient.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Direction", &worldLight.direction.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Specular", &worldLight.specular.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Diffuse", &worldLight.diffuse.x, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", &worldLight.diffuse.x);
    ImGui::End();
}

void debugUI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
