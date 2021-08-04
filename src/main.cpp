#include "main.h"
#include "camera.h"
#include "cube_demo.h"
#include "grass.h"
#include "debug_ui.h"
#include "model.h"
#include "r_cube.h"
#include "shader.h"
#include "sky_box.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include "asteroid.h"
GlobalSettings globalSettings{//NOLINT
                              .SCR_WIDTH = 1680,
                              .SCR_HEIGHT = 1050,
                              .lastX = static_cast<double>(1280 / 2.0),
                              .lastY = static_cast<double>(720 / 2.0),
                              .firstMouse = true,
                              .deltaTime = 0.0f,
                              .lastFrame = 0.0f,
                              .processMouse = true};
static Camera camera(glm::vec3(0.0f, 0.0f, 0.0f)); //NOLINT

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(globalSettings.SCR_WIDTH, globalSettings.SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    //stbi_set_flip_vertically_on_load(true);
    Shader sponzaShader("shaders/shader.vert", "shaders/light.frag");
    Model sponzaModel("sponza/sponza.obj");
    Shader screenShader("shaders/screen.vert", "shaders/screen.frag");
    Shader geoShader("shaders/geo.vert", "shaders/geo.geom", "shaders/geo.frag");
    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    debugUI demoWindow(window);
    std::vector<glm::vec3> pointLightPositions;
    pointLightPositions.reserve(4);
    pointLightPositions.emplace_back(glm::vec3(0.7f, 0.2f, 2.0f));
    pointLightPositions.emplace_back(glm::vec3(2.3f, -3.3f, -4.0f));
    pointLightPositions.emplace_back(glm::vec3(-4.0f, 2.0f, -12.0f));
    pointLightPositions.emplace_back(glm::vec3(0.0f, 0.0f, -3.0f));

    std::vector<glm::vec3> grassLocations;
    grassLocations.reserve(5);
        grassLocations.emplace_back(glm::vec3(-1.5f, 0.0f, -0.48f));
        grassLocations.emplace_back(glm::vec3(1.5f, 0.0f, 0.51f));
        grassLocations.emplace_back(glm::vec3(0.0f, 0.0f, 0.7f));
        grassLocations.emplace_back(glm::vec3(-0.3f, 0.0f, -2.3f));
        grassLocations.emplace_back(glm::vec3(0.5f, 0.0f, -0.6f));
    std::vector<float> points{
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f // bottom-left
    };

    unsigned int GVBO{0};
    unsigned int GVAO{0};
    glGenVertexArrays(1, &GVAO);
    glGenBuffers(1, &GVBO);
    glBindBuffer(GL_ARRAY_BUFFER, GVBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(points.size() * sizeof(&points[0])), &points.front(), GL_STATIC_DRAW);
    glBindVertexArray(GVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(&points[0]), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(&points[0]), reinterpret_cast<void *>(2 * sizeof(&points[0])));
    glBindVertexArray(0);

    Grass grass(grassLocations);
    cubeDemo cubes;
    SkyBox skyBox;
    ReflCube reflCube;
    AsteroidDemo as;

    int a = (float)1;
    vec3c vc{0.8f, 0.8f, 0.8f};
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        auto currentFrame = static_cast<float>(glfwGetTime());
        globalSettings.deltaTime = currentFrame - globalSettings.lastFrame;
        globalSettings.lastFrame = currentFrame;
        // input
        // -----
        processInput(window);
        // render
        // ------
        //mirror(framebuff,cubes,sponzaShader,sponzaModel,pointLightPositions.data(),grass);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        //glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(globalSettings.SCR_WIDTH) / static_cast<float>(globalSettings.SCR_HEIGHT), 0.1f, 100.0f);
        auto view = camera.GetViewMatrix();

        as.Draw(projection, view);
        cubes.Draw(camera, projection, view, pointLightPositions);
        sponzaShader.use();
        renderLights(sponzaShader, pointLightPositions, vc);
        // view/projection transformations
        sponzaShader.setMat4("projection", projection);
        sponzaShader.setMat4("view", view);
        // render the loaded model
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        sponzaShader.setMat4("model", model);
        //sponzaShader.setFloat("time", glfwGetTime());
        sponzaModel.Draw(sponzaShader);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.skyTexture);
        reflCube.draw(view, projection, camera);
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyBox.draw(view, projection);
        // geoShader.use();
        // glBindVertexArray(GVAO);
        // glDrawArrays(GL_POINTS, 0, 4);
        view = camera.GetViewMatrix();
        grass.Draw(projection, view, camera.Position);
        //mirrorQuad(screenShader,framebuff);
        demoWindow.draw(pointLightPositions.data(), window, vc);
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    grass.cleanUp();
    glfwTerminate();
    return 0;
}

void renderLights(Shader &shader, std::vector<glm::vec3> &pointLightPositions,vec3c colour)
{
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    shader.setFloat("material.shininess", 32.0f);
    /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
    // directional light
    shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    for (unsigned long i = 0; i < pointLightPositions.size(); i++) {
        shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
        shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", colour.x,colour.y, colour.z);
        shader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
        shader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
        shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
    }
    // spotLight
    shader.setVec3("spotLight.position", camera.Position);
    shader.setVec3("spotLight.direction", camera.Front);
    shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09f);
    shader.setFloat("spotLight.quadratic", 0.032f);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if(globalSettings.processMouse){
            globalSettings.processMouse = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            globalSettings.processMouse = true;
            glfwSetInputMode(window,GLFW_CURSOR , GLFW_CURSOR_DISABLED);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, globalSettings.deltaTime);
    }
       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, globalSettings.deltaTime);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (globalSettings.firstMouse) {
        globalSettings.lastX = xpos;
        globalSettings.lastY = ypos;
        globalSettings.firstMouse = false;
    }

    auto xoffset = static_cast<float>(xpos - globalSettings.lastX);
    auto yoffset = static_cast<float>(globalSettings.lastY - ypos); // reversed since y-coordinates go from bottom to top

    globalSettings.lastX = xpos;
    globalSettings.lastY = ypos;
    if(globalSettings.processMouse){
        camera.ProcessMouseMovement(xoffset, yoffset, true);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
