//
// Created by ssj5v on 06-03-2025.
//

#ifndef SDFRENDERER_H
#define SDFRENDERER_H
#include "shader/Shader.h"
#include "shader/data/generic_shader_data.h"
#include "shader/data/lighting_shader_data.h"
#include "shader/data/ray_shader_data.h"
#include "GLFW/glfw3.h"
#include "scene/scene.h"
#include "ui/scene_ui.h"


class SDFRenderer {
private:
    GLFWwindow* windowCtx;
    float width, height;
    bool isReady = false;
    double prevFrameTime = 0.0f;
    double deltaTime  = 0.0f;

    //shader stuff
    Shader shader;
    GenericShaderData genericShaderData;
    LightingShaderData lightingShaderData;
    RayShaderData rayShaderData;

    //input stuff
    static bool firstMouse;
    static float lastX;
    static float lastY;

    //full screen quad to render our vertices.
    unsigned int VAO,VBO;
    float quadVertices[12] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };

    //Scene
    Scene scene;
    SceneUI sceneUI;

    //Camera controls
    bool isLookInputActive;

public:
    SDFRenderer(int width, int height, GLFWwindow* window);
    void init();
    void update(double time);
    void processInput();
    void clean();
private:
    void draw();
    void pushShaderParams(double time);
    void setupShaderUniformBuffers();
    void setupImGUI();
    [[nodiscard]] bool getLookInput() const { return isLookInputActive; }
    [[nodiscard]] double getDeltaTime() const {return deltaTime;}
    static void updateResolution(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
};



#endif //SDFRENDERER_H
