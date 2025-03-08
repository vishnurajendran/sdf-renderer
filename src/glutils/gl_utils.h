//
// Created by ssj5v on 06-03-2025.
//

#ifndef GL_UTILS_H
#define GL_UTILS_H
#include "glad/glad.h"

enum ShaderType
{
    VERTEX_SHADER,
    FRAGMENT_SHADER,
};

bool ShaderCompileSuccess(GLuint shader, ShaderType type);
bool ShaderLinkSuccess(GLuint shader);
bool CheckOpenGLError();

#endif //GL_UTILS_H
