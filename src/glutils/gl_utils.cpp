//
// Created by ssj5v on 06-03-2025.
//

#include "gl_utils.h"
#include <iostream>

bool ShaderCompileSuccess(GLuint shader, ShaderType type)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << (type == ShaderType::VERTEX_SHADER?"Vertex" : "Fragment") << "\n"
                  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
    return success;
}

bool ShaderLinkSuccess(GLuint shader)
{
    GLint success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n"
                  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
    return success;
}

bool CheckOpenGLError()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::string errorStr;
        switch (error) {
        case GL_INVALID_ENUM:
            errorStr = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorStr = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorStr = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            errorStr = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            errorStr = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            errorStr = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            errorStr = "UNKNOWN_ERROR";
            break;
        }
        std::cerr << "OpenGL Error: " << errorStr << std::endl;
    }
    return error == GL_NO_ERROR;
}
