//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_shape.h"

#include <imgui.h>

SDFShaderDataStruct SDFShape::getDataStruct()
{
    shaderDataStruct.position = position;
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
    ImGui::Text("Operation: ");
    ImGui::SameLine();
    if (ImGui::Combo("##Operation", &currValue, display.data(), display.size()))
    {
        shaderDataStruct.operationType = currValue;
    }
}
