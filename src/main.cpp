#include "main.h"
#include "asteroid.h"
#include "camera.h"
#include "cube_demo.h"
#include "debug_ui.h"
#include "entities/point_light.h"
#include "entities/world_light.h"
#include "grass.h"
#include "model.h"
#include "r_cube.h"
#include "shader.h"
#include "sky_box.h"
#include <future>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

GlobalSettings globalSettings {
    1680,
    1050,
    (1280.0 / 2.0),
    (720.0 / 2.0),
    true,
    0.0f,
    0.0f,
    true,
    false
};

static Camera camera(glm::vec3(0.0f, 0.0f, 0.0f)); //NOLINT

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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
    //glfwSetKeyCallback(window, key_callback);
    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
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
    glEnable(GL_MULTISAMPLE);

    //stbi_set_flip_vertically_on_load(true);

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

    //Frame buffer to render to texture for imgui
    unsigned int FBO{0};
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glfwGetFramebufferSize(window, &globalSettings.SCR_WIDTH, &globalSettings.SCR_HEIGHT);
    unsigned int fb_tex{0};
    glGenTextures(1, &fb_tex);
    glBindTexture(GL_TEXTURE_2D, fb_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, globalSettings.SCR_WIDTH, globalSettings.SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_tex, 0);
    unsigned int rbo{0};
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, globalSettings.SCR_WIDTH, globalSettings.SCR_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // Depthbuffer
    unsigned int depthMapFBO{0};
    glGenFramebuffers(1, &depthMapFBO);
    const unsigned int SHADOW_WIDTH = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;
    unsigned int depthMap{0};
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::cout << "Loading Sponza Shaders \n";
    Shader sponzaShader("../assets/shaders/shader.vert", "../assets/shaders/light.frag");
    std::cout << "Loading Sponza Model \n";
    Model sponzaModel("../assets/sponza/sponza.obj");

    std::cout << "Loading Screen Shaders \n";
    Shader screenShader("../assets/shaders/screen.vert", "../assets/shaders/screen.frag");

    std::cout << "Loading Geo Shaders \n";
    Shader geoShader("../assets/shaders/geo.vert", "../assets/shaders/geo.geom", "../assets/shaders/geo.frag");

    Shader simpleDepthShader("../assets/shaders/simple_depth_shader.vert", "../assets/shaders/simple_depth_shader.frag");

    screenShader.use();
    screenShader.set_int("screenTexture", 0);

    std::cout << "Loading Grass \n";
    std::vector<glm::vec3> grassLocations;
    grassLocations.reserve(5);
    grassLocations.emplace_back(-1.5f, 0.0f, -0.48f);
    grassLocations.emplace_back(1.5f, 0.0f, 0.51f);
    grassLocations.emplace_back(0.0f, 0.0f, 0.7f);
    grassLocations.emplace_back(-0.3f, 0.0f, -2.3f);
    grassLocations.emplace_back(0.5f, 0.0f, -0.6f);
    Grass grass(grassLocations);

    std::cout << "Loading Demo Cubes \n";
    CubeDemo cubes;

    std::cout << "Loading Skybox \n";
    SkyBox skyBox;

    std::cout << "Loading reflCube \n";
    ReflCube reflCube;

    std::cout << "Loading Asteroids \n";
    AsteroidDemo as;

    WorldLight wLight("World Light",
                      {-0.2f, -1.0f, -0.3f}, {0.05f, 0.05f, 0.05f},
                      {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f},{0.0f,0.0f,0.0f});

    std::vector<PointLight> pointLights;
    pointLights.reserve(4);
    pointLights.emplace_back(PointLight("Point Light 1",
                                        {0.7f, 0.2f, 2.0f},
                                        1.0f, 0.09f, 0.032f,
                                        {0.05f, 0.05f, 0.05f},
                                        {0.8f, 0.8f, 0.8f},
                                        {1.0f, 1.0f, 1.0f}));
    pointLights.emplace_back(PointLight("Point Light 2",
                                        {2.3f, -3.3f, -4.0f},
                                        1.0f, 0.09f, 0.032f,
                                        {0.05f, 0.05f, 0.05f},
                                        {0.8f, 0.8f, 0.8f},
                                        {1.0f, 1.0f, 1.0f}));
    pointLights.emplace_back(PointLight("Point Light 3",
                                        {-4.0f, 2.0f, -12.0f},
                                        1.0f, 0.09f, 0.032f,
                                        {0.05f, 0.05f, 0.05f},
                                        {0.8f, 0.8f, 0.8f},
                                        {1.0f, 1.0f, 1.0f}));
    pointLights.emplace_back(PointLight("Point Light 4",
                                        {0.5f, 0.0f, -0.6f},
                                        1.0f, 0.09f, 0.032f,
                                        {0.05f, 0.05f, 0.05f},
                                        {0.8f, 0.8f, 0.8f},
                                        {1.0f, 1.0f, 1.0f}));

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    bool mKeyPressed = false;
    DebugUI debugUI(window);

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        auto currentFrame = static_cast<float>(glfwGetTime());
        globalSettings.deltaTime = currentFrame - globalSettings.lastFrame;
        globalSettings.lastFrame = currentFrame;
        // input
        // -----
        process_input(window, mKeyPressed);
        // render
        // ------
        // clear all relevant buffers
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // 1. first render to depth map
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        render_scene(sponzaShader, sponzaModel, cubes, reflCube, as, grass, wLight, pointLights, skyBox);
        
        // 2. then render scene as normal with shadow mapping (using depth map)
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glViewport(0, 0, globalSettings.SCR_WIDTH, globalSettings.SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        render_scene(sponzaShader, sponzaModel, cubes, reflCube, as, grass, wLight, pointLights, skyBox);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //if (globalSettings.debug) {
        debugUI.draw(window, pointLights, wLight, fb_tex, camera);
        //}

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    grass.clean_up();
    glfwTerminate();
    return 0;
}

void render_scene(Shader &sponzaShader, Model &sponzaModel, CubeDemo &cubes, ReflCube &reflCube, AsteroidDemo &as, 
                  Grass &grass, WorldLight &wLight, std::vector<PointLight> &pointLights, SkyBox &skyBox)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(globalSettings.SCR_WIDTH) / static_cast<float>(globalSettings.SCR_HEIGHT), 0.1f, 100.0f);
    auto view = camera.get_view_matrix();
    render_lights(as.planetShader, pointLights, wLight);
    render_lights(as.asteroidShader, pointLights, wLight);
    as.draw(projection, view);

    render_lights(cubes.get_shader(), pointLights, wLight);
    cubes.draw(camera, projection, view, pointLights, wLight);
    
    render_lights(sponzaShader, pointLights, wLight);
    // view/projection transformations
    sponzaShader.set_mat4("projection", projection);
    sponzaShader.set_mat4("view", view);
    // render the loaded model
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    sponzaShader.set_mat4("model", model);
    sponzaModel.draw(sponzaShader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.get_texture());
    reflCube.draw(view, projection, camera);
    
    view = glm::mat4(glm::mat3(camera.get_view_matrix()));
    skyBox.draw(view, projection);
    
    //renderLights(grass.grassShader, pointLights, wLight);
    view = camera.get_view_matrix();
    grass.draw(projection, view, camera.Position);
}

void render_lights(const Shader &ourShader, std::vector<PointLight> &pointLights, WorldLight &worldLight)
{
    ourShader.use();
    ourShader.set_int("material.diffuse", 0);
    ourShader.set_int("material.specular", 1);
    ourShader.set_float("material.shininess", 32.0f);
    /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
    // directional light
    ourShader.set_vec3("dirLight.direction", worldLight.direction);
    ourShader.set_vec3("dirLight.ambient", worldLight.ambient);
    ourShader.set_vec3("dirLight.diffuse", worldLight.diffuse);
    ourShader.set_vec3("dirLight.specular", worldLight.specular);
    if (!pointLights.empty()) {
        for (unsigned long i = 0; i < pointLights.size(); i++) {
            ourShader.set_vec3("pointLights[" + std::to_string(i) + "].position", pointLights[i].position);
            ourShader.set_vec3("pointLights[" + std::to_string(i) + "].ambient", pointLights[i].ambient);
            ourShader.set_vec3("pointLights[" + std::to_string(i) + "].diffuse", pointLights[i].diffuse);
            ourShader.set_vec3("pointLights[" + std::to_string(i) + "].specular", pointLights[i].specular);
            ourShader.set_float("pointLights[" + std::to_string(i) + "].constant", pointLights[i].constant);
            ourShader.set_float("pointLights[" + std::to_string(i) + "].linear", pointLights[i].linear);
            ourShader.set_float("pointLights[" + std::to_string(i) + "].quadratic", pointLights[i].quadratic);
            ourShader.set_int("LightPoints", static_cast<int>(pointLights.size()));
        }
    } else {
        ourShader.set_vec3("pointLights[0].position", glm::vec3(0.0f, 0.0f, 0.0f));
        ourShader.set_vec3("pointLights[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        ourShader.set_vec3("pointLights[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
        ourShader.set_vec3("pointLights[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
        ourShader.set_float("pointLights[0].constant", 0.0f);
        ourShader.set_float("pointLights[0].linear", 0.0f);
        ourShader.set_float("pointLights[0].quadratic", 0.0f);
    }

    // shader.setVec3("spotLight.position", camera.Position);
    // shader.setVec3("spotLight.direction", camera.Front);
    // shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    // shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    // shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    // shader.setFloat("spotLight.constant", 1.0f);
    // shader.setFloat("spotLight.linear", 0.09f);
    // shader.setFloat("spotLight.quadratic", 0.032f);
    // shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    // shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window, bool &mKeyPressed)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.process_keyboard(FORWARD, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.process_keyboard(BACKWARD, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.process_keyboard(LEFT, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.process_keyboard(RIGHT, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.process_keyboard(UP, globalSettings.deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !mKeyPressed) {
        mKeyPressed = true;
        if (globalSettings.processMouse) {
            globalSettings.processMouse = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            globalSettings.processMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) {
        mKeyPressed = false;
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
    if (globalSettings.processMouse) {
        camera.process_mouse_movement(xoffset, yoffset, true);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.process_mouse_scroll(static_cast<float>(yoffset));
}
