//
// Created by ssj5v on 06-03-2025.
//

#include "SDFRenderer.h"
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include "glutils/gl_utils.h"

SDFRenderer::SDFRenderer(int width, int height, GLFWwindow* window)
{
    genericShaderData.resolution = glm::vec2(width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, updateResolution);
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
    isReady = true;
}

void SDFRenderer::update(double time)
{
    if (!isReady) return;
    auto deltaTime = (time - prevFrameTime);
    //start draw call
    glUseProgram(shader.getId());
    pushShaderParams(time);
    draw();
    prevFrameTime = time;
    std::cout << "SDFRenderer::Updating SDF Renderer..."<< deltaTime << std::endl;
    //end draw call
}

void SDFRenderer::clean()
{
    std::cout << "SDFRenderer::Cleaning SDFRenderer" << std::endl;
}

void SDFRenderer::updateResolution(GLFWwindow* window, int width, int height)
{
    auto instance = static_cast<SDFRenderer*>(glfwGetWindowUserPointer(window));
   instance->genericShaderData.resolution = glm::vec2(width, height);
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

    lightingShaderData.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    lightingShaderData.sunDirection = glm::vec3(1,1,-1);
    lightingShaderData.sunColor = glm::vec3(1,1, 1);

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