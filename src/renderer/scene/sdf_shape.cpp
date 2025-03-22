//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_shape.h"

#include <imgui.h>
#include <random>

#include "glm/gtc/type_ptr.hpp"

SDFShape::SDFShape()
{
    // assign a random color to each shape.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    shaderDataStruct.surfaceColor = glm::vec3( dis(gen),  dis(gen), dis(gen));
}

SDFShaderDataStruct SDFShape::getDataStruct()
{
    shaderDataStruct.position = position;
    shaderDataStruct.rotation = rotation;
    shaderDataStruct.shapeType = getType();
    return shaderDataStruct;
}

void SDFShape::updateDataToShader(unsigned int shaderId)
{

}

void SDFShape::update(double deltaTime)
{
    SceneElement::update(deltaTime);

}

void SDFShape::drawInspectorGui()
{
    std::vector<char*> display = {"Union","Intersection", "Subtraction"};
    auto currValue = shaderDataStruct.operationType;
    if (ImGui::CollapsingHeader("Basic Properties"))
    {
        ImGui::Text("Operation: ");
        ImGui::SameLine();
        if (ImGui::Combo("##Operation", &currValue, display.data(), display.size()))
        {
            shaderDataStruct.operationType = currValue;
        }
        ImGui::NewLine();
        ImGui::ColorPicker3("Surface Color", glm::value_ptr(shaderDataStruct.surfaceColor), ImGuiColorEditFlags_Float);
    }
}
