//
// Created by ssj5v on 11-03-2025.
//

#ifndef SDFSHADERDATASTRUCT_H
#define SDFSHADERDATASTRUCT_H
#include "glm/glm.hpp"

struct alignas(16) SDFShaderDataStruct {
    //basic
    alignas(16) int shapeType=0;
    alignas(16) int operationType=0;
    alignas(16) glm::vec3 position;
    //shape specifics
    alignas(16) float radius=0.5f;
    alignas(16) glm::vec3 halfExtents;
};



#endif //SDFSHADERDATASTRUCT_H
