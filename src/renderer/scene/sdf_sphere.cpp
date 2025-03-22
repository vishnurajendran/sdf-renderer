//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_sphere.h"

#include <imgui.h>
#include <iostream>

SDFShapeType SDFSphere::getType()
{
    return SDFShapeType::Sphere;
}

SDFSphere::SDFSphere(glm::vec3 position, float radius)
{
    this->position = position;
    this->shaderDataStruct.radius = radius;
}

void SDFSphere::update(double deltaTime)
{
    SDFShape::update(deltaTime);
}

void SDFSphere::updateDataToShader(unsigned int shaderId)
{
    SDFShape::updateDataToShader(shaderId);
}

void SDFSphere::drawInspectorGui()
{
    SDFShape::drawInspectorGui();
    if (ImGui::CollapsingHeader("Sphere Properties")){
        ImGui::Text("Radius: ");
        ImGui::SameLine();
        ImGui::InputFloat("##SPHERE_RAD",&shaderDataStruct.radius,0.1f,1.0f);
    }
}
