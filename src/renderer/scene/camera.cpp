//
// Created by ssj5v on 08-03-2025.
//

#include "camera.h"

#include <imgui.h>
#include <glad/glad.h>

void Camera::updateDataToShader(unsigned int shaderId)
{
    //nothing here.
    const unsigned int loc = glGetUniformLocation(shaderId, "cameraFarClip");
    glUniform1f(loc, farClip);
}

void Camera::update(double deltaTime)
{
    SceneElement::update(deltaTime);
    //nothing here
}

void Camera::drawInspectorGui()
{
    //nothing here..
    ImGui::Text("Far Clip");
    ImGui::SameLine();
    ImGui::DragFloat("##FarClip", &farClip, 0.01f, 1.0f, 1000.0f);
}
