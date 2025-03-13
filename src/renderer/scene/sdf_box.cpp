//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_box.h"

#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"

SDFShapeType SDFBox::getType()
{
    return SDFShapeType::Box;
}

SDFBox::SDFBox(glm::vec3 position, glm::vec3 halfExtents)
{
    this->position = position;
    this->shaderDataStruct.halfExtents = halfExtents;
}

void SDFBox::update(double deltaTime)
{
    SDFShape::update(deltaTime);
}

void SDFBox::updateDataToShader(unsigned int shaderId)
{
    SDFShape::updateDataToShader(shaderId);
}

void SDFBox::drawInspectorGui()
{
    SDFShape::drawInspectorGui();
    ImGui::Text("Half Extents");
    ImGui::SameLine();
    ImGui::InputFloat3("##HALF_EXT", glm::value_ptr(shaderDataStruct.halfExtents));
}
