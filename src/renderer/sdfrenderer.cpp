//
// Created by ssj5v on 06-03-2025.
//

#include "sdfrenderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include "glutils/gl_utils.h"
#include "scene/sdf_shape.h"

bool SDFRenderer::firstMouse = true;
float SDFRenderer::lastX = 0.0f;
float SDFRenderer::lastY = 0.0f;

SDFRenderer::SDFRenderer(int width, int height, GLFWwindow* window)
{
    windowCtx = window;
    genericShaderData.resolution = glm::vec2(width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, updateResolution);
    glfwSetCursorPosCallback(window, mouseCallback);

    setupImGUI();
    sceneUI.init(&scene);
}

void SDFRenderer::init()
{
    std::cout << "SDFRenderer::Initializing SDF Renderer..." << std::endl;
    std::cout << "SDFRenderer::Compiling Shader..." << std::endl;
    auto res = shader.compile("assets/shaders/SDF.vert", "assets/shaders/SDF.frag");
    if (!res)
    {
        std::cerr << "SDFRenderer::Shader compilation failed!" << std::endl;
        return;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    setupShaderUniformBuffers();
    lightingShaderData.ambient = glm::vec3(0.6f);
    lightingShaderData.sunDirection = glm::vec3(1,1,-1);
    lightingShaderData.sunColor = glm::vec3(1,1, 1);

    isReady = true;
}

void SDFRenderer::update(double time)
{
    if (!isReady) return;
    // compute delta time
    deltaTime = (time - prevFrameTime);
    // process input
    processInput();

    // update scene-elements
    scene.update(deltaTime);

    //start draw call
    glUseProgram(shader.getId());
    pushShaderParams(time);
    draw();
    prevFrameTime = time;
    //end draw call
}

void SDFRenderer::mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    auto instance = static_cast<SDFRenderer*>(glfwGetWindowUserPointer(window));
    if (!instance->getLookInput())
        return;

    static float lastX = xpos;
    static float lastY = ypos;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 15.0f * instance->getDeltaTime();
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    instance->scene.getCamera()->rotation.y -= xOffset;
    instance->scene.getCamera()->rotation.x -= yOffset;
}

void SDFRenderer::processInput()
{
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(windowCtx, GLFW_KEY_W) == GLFW_PRESS)
        scene.getCamera()->position += scene.getCamera()->forward * cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_S) == GLFW_PRESS)
        scene.getCamera()->position -= scene.getCamera()->forward * cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_A) == GLFW_PRESS)
        scene.getCamera()->position -= cameraSpeed * scene.getCamera()->right;
    if (glfwGetKey(windowCtx, GLFW_KEY_D) == GLFW_PRESS)
        scene.getCamera()->position += cameraSpeed * scene.getCamera()->right;
    if (glfwGetKey(windowCtx, GLFW_KEY_SPACE) == GLFW_PRESS)
        scene.getCamera()->position.y += cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        scene.getCamera()->position.y -= cameraSpeed;

    if (glfwGetMouseButton(windowCtx, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        isLookInputActive = true;
    else
    {
        firstMouse = true;
        isLookInputActive = false;
    }
}

void SDFRenderer::clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "SDFRenderer::Cleaning SDFRenderer" << std::endl;
}

void SDFRenderer::updateResolution(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    auto instance = static_cast<SDFRenderer*>(glfwGetWindowUserPointer(window));
    instance->genericShaderData.resolution = glm::vec2(width, height);
    std::cout << "SDFRenderer::Updating Resolution..."<< width << "X"<< height << std::endl;
}

void SDFRenderer::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    sceneUI.draw();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    CheckOpenGLError();
}

void SDFRenderer::pushShaderParams(double time)
{
    genericShaderData.time = time;

    rayShaderData.origin = scene.getCamera()->position;
    rayShaderData.forward = scene.getCamera()->forward;
    rayShaderData.right = scene.getCamera()->right;
    rayShaderData.up = scene.getCamera()->up;

    genericShaderData.pushToShader();
    lightingShaderData.pushToShader();
    rayShaderData.pushToShader();

    scene.pushToShader(shader.getId());
}

void SDFRenderer::setupShaderUniformBuffers()
{
    genericShaderData.init(shader.getId());
    lightingShaderData.init(shader.getId());
    rayShaderData.init(shader.getId());
}

void SDFRenderer::setupImGUI()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags = ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;
    // Setup ImGui with GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(windowCtx, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
