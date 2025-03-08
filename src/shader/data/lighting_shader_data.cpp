//
// Created by ssj5v on 07-03-2025.
//
#include "glad/glad.h"
#include "lighting_shader_data.h"

#include <iostream>

#include "glutils/gl_utils.h"

void LightingShaderData::init(unsigned int shaderId)
{
    bufferIndex = glGetUniformBlockIndex(shaderId, "Lighting");
    glUniformBlockBinding(shaderId, bufferIndex, 1);
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightingShaderData), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, bufferObject);

    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at Init (LightingShaderData)" << std::endl;
    }
}

void LightingShaderData::pushToShader() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightingShaderData), this);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at PushToShader (LightingShaderData)" << std::endl;
    }

    glFinish();
}