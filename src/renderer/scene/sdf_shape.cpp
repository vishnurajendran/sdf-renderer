//
// Created by ssj5v on 11-03-2025.
//

#include "sdf_shape.h"

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
