//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_box.h"

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
