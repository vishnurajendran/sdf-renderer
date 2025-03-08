//
// Created by ssj5v on 07-03-2025.
//

#ifndef GENERIC_SHADER_DATA_H
#define GENERIC_SHADER_DATA_H
#include "glm/glm.hpp"

struct GenericShaderData
{
    alignas(8) glm::vec2 resolution;
    alignas(4) float time;

    unsigned int bufferIndx;
    unsigned int bufferObject;

    void init(unsigned int shaderId);
    void pushToShader() const;
};

#endif //GENERIC_SHADER_DATA_H
