//
// Created by ssj5v on 07-03-2025.
//

#ifndef RAY_SHADER_DATA_H
#define RAY_SHADER_DATA_H
#include "glm/glm.hpp"
struct RayShaderData
{
    alignas(16) glm::vec3 origin;
    alignas(16) glm::vec3 forward;
    alignas(16) glm::vec3 right;
    alignas(16) glm::vec3 up;

    unsigned int bufferIndx;
    unsigned int bufferObject;

    void init(unsigned int shaderId);
    void pushToShader() const;
};

#endif //RAY_SHADER_DATA_H
