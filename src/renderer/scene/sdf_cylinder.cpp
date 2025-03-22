//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_cylinder.h"

#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"

SDFShapeType SDFCylinder::getType()
{
    return SDFShapeType::Cylinder;
}

SDFCylinder::SDFCylinder(glm::vec3 position, float halfHeight, float radius)
{
    this->position = position;
    this->shaderDataStruct.radius = radius;
    this->shaderDataStruct.halfExtents = glm::vec3(0,halfHeight,0); //re-use this field
}

void SDFCylinder::update(double deltaTime)
{
    SDFShape::update(deltaTime);
}

void SDFCylinder::updateDataToShader(unsigned int shaderId)
{
    SDFShape::updateDataToShader(shaderId);
}

void SDFCylinder::drawInspectorGui()
{
    SDFShape::drawInspectorGui();
    if (ImGui::CollapsingHeader("Cylinder Properties")){
        ImGui::Text("Radius");
        ImGui::SameLine();
        ImGui::InputFloat("##CYL_RAD", &shaderDataStruct.radius);
        ImGui::Text("Height");
        ImGui::SameLine();
        ImGui::InputFloat("##CYL_HEIGHT", &shaderDataStruct.halfExtents.y);
    }
}
