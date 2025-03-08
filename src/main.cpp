#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "SDFRenderer.h"
#include "shader/Shader.h"

// Window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Callback function for resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints for OpenGL version 4.1 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SDF Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set OpenGL viewport and callback
    glViewport(0, 0, WIDTH, HEIGHT);

    // create renderer
    SDFRenderer renderer(WIDTH, HEIGHT, window);
    renderer.init();
    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        //update renderer
        renderer.update(glfwGetTime());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.clean();
    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
