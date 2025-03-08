//
// Created by ssj5v on 07-03-2025.
//
#include "glad/glad.h"
#include "glutils/gl_utils.h"
#include "ray_shader_data.h"

#include <iostream>
#include <ostream>

void RayShaderData::init(unsigned int shaderId)
{
    bufferIndx = glGetUniformBlockIndex(shaderId, "Ray");
    glUniformBlockBinding(shaderId, bufferIndx, 2);
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(RayShaderData), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, bufferObject);
    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at Init (RayShaderData)" << std::endl;
    }
}

void  RayShaderData::pushToShader() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(RayShaderData), this);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at PushToShader (RayShaderData)" << std::endl;
    }

    glFinish();
}
