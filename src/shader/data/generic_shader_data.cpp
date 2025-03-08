//
// Created by ssj5v on 07-03-2025.
//
#include "glad/glad.h"
#include "generic_shader_data.h"

#include <iostream>

#include "glutils/gl_utils.h"

void GenericShaderData::init(unsigned int shaderId)
{
    bufferIndx = glGetUniformBlockIndex(shaderId, "Generic");
    glUniformBlockBinding(shaderId, bufferIndx, 0);
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(GenericShaderData), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferObject);

    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at Init (GenericShaderData)" << std::endl;
    }
}

void GenericShaderData::pushToShader() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GenericShaderData), this);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at PushToShader (GenericShaderData)" << std::endl;
    }

    glFinish();
}
