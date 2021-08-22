#include "debug_ui.h"
#include "camera.h"
#include "entities/point_light.h"
#include "entities/world_light.h"
#include "imgui.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <vector>

DebugUI::DebugUI(GLFWwindow *window) : show_demo_window(true), show_another_window(false), clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    //io.FontGlobalScale = 5;
    const char *glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
}

void DebugUI::draw(GLFWwindow *window, std::vector<PointLight> &pointLights, WorldLight &worldLight, unsigned int fb, Camera &camera)
{
    //ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    menu_bar(window);
    docking_space();
    world_light(worldLight);
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    light_list(pointLights, camera);
    render_viewport(window, fb);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void DebugUI::docking_space(){
        ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    ImGui::PopStyleVar(3);
    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    ImGui::End();
}

void DebugUI::render_viewport(GLFWwindow *window, unsigned int fb)
{
    ImGui::SetNextWindowSize(ImVec2(1680.0f / 2.0f, 1050.0f / 2.0f), ImGuiCond_Once);
    ImGui::Begin("RenderWindow");
    {
        ImGui::BeginChild("GameRender");
        ImVec2 wsize = ImGui::GetWindowSize();
        auto ratioX = wsize.x / 1680.0f;
        auto ratioY = wsize.y / 1050.0f;
        auto ratio = ratioX < ratioY ? ratioX : ratioY;
        auto renderSize = ImVec2(
            1680.0f * ratio,
            1050.0f * ratio);
        auto a = ImVec2((wsize.x - renderSize.x) * 0.5f, (wsize.y - renderSize.y) * 0.5f);
        ImGui::SetCursorPos(a);
        ImGui::Image((ImTextureID)fb, renderSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}

void DebugUI::light_list(std::vector<PointLight> &pointLights, Camera &camera)
{
    ImGui::Begin("Point Lights");
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
            edit_light(pointLights[light]);
        }
    }
    ImGui::End();
}

void DebugUI::edit_light(PointLight &light)
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

void DebugUI::menu_bar(GLFWwindow *window)
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

void DebugUI::world_light(WorldLight &worldLight)
{
    ImGui::Begin("World Light");
    ImGui::SliderFloat3("Ambient", &worldLight.ambient.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Direction", &worldLight.direction.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Specular", &worldLight.specular.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Diffuse", &worldLight.diffuse.x, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", &worldLight.diffuse.x);
    ImGui::End();
}

void DebugUI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
