//
// Created by ssj5v on 07-03-2025.
//

#ifndef LIGHTING_SHADER_DATA_H
#define LIGHTING_SHADER_DATA_H
#include "glm/glm.hpp"

struct LightingShaderData
{
    alignas(16) glm::vec3 ambient;
    alignas(16) glm::vec3 sunDirection;
    alignas(16) glm::vec3 sunColor;

    unsigned int bufferIndex;
    unsigned int bufferObject;

    void init(unsigned int shaderId);
    void pushToShader() const;
};
#endif //LIGHTING_SHADER_DATA_H
