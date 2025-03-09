//
// Created by ssj5v on 06-03-2025.
//

#include "sdfrenderer.h"
#include <iostream>
#include <ostream>
#include <../cmake-build-debug/_deps/glm-src/glm/glm.hpp>
#include "glutils/gl_utils.h"

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

    camera.position = glm::vec3(0,0,5);
    camera.rotation = glm::vec3(0,0,0);

    lightingShaderData.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
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
    camera.update(deltaTime);


    //start draw call
    glUseProgram(shader.getId());
    pushShaderParams(time);
    draw();
    prevFrameTime = time;
    //end draw call
}

void SDFRenderer::mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    return;
    auto instance = static_cast<SDFRenderer*>(glfwGetWindowUserPointer(window));

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.002f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    instance->camera.rotation.x += xOffset; // Yaw (horizontal rotation)
    instance->camera.rotation.y = glm::clamp(instance->camera.rotation.y + yOffset, -1.5f, 1.5f); // Pitch (vertical rotation)
}

void SDFRenderer::processInput()
{
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(windowCtx, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += camera.forward * cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= camera.forward * cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= cameraSpeed * camera.right;
    if (glfwGetKey(windowCtx, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += cameraSpeed * camera.right;
    if (glfwGetKey(windowCtx, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.position.y += cameraSpeed;
    if (glfwGetKey(windowCtx, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.position.y -= cameraSpeed;
}

void SDFRenderer::clean()
{
    std::cout << "SDFRenderer::Cleaning SDFRenderer" << std::endl;
}

void SDFRenderer::updateResolution(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    auto instance = static_cast<SDFRenderer*>(glfwGetWindowUserPointer(window));
    instance->genericShaderData.resolution = glm::vec2(width, height);
    std::cout << "SDFRenderer::Updating Resolution..."<< width << "X"<< height << std::endl;
}

void SDFRenderer::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    CheckOpenGLError();
}

void SDFRenderer::pushShaderParams(double time)
{
    genericShaderData.time = time;

    rayShaderData.origin = camera.position;
    rayShaderData.direction = camera.forward;

    genericShaderData.pushToShader();
    lightingShaderData.pushToShader();
    rayShaderData.pushToShader();
}

void SDFRenderer::setupShaderUniformBuffers()
{
    genericShaderData.init(shader.getId());
    lightingShaderData.init(shader.getId());
    rayShaderData.init(shader.getId());
}