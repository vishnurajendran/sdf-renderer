//
// Created by ssj5v on 06-03-2025.
//

#include "Shader.h"
#include <iostream>
#include <utils/fileio.h>
#include <glutils/gl_utils.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    //nothing here for now
    shaderProgram = 0;
    compile(vertexPath, fragmentPath);
}

bool Shader::compile(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    if (!readFile(vertexPath, vertexCode))
    {
        std::cout << "Shader::CANNOT READ " << vertexPath << std::endl;
        return false;
    }
    if (!readFile(fragmentPath, fragmentCode))
    {
        std::cout << "Shader::CANNOT READ " << fragmentPath << std::endl;
        return false;
    }

    auto vertCharArr = vertexCode.c_str();
    auto fragCharArr = fragmentCode.c_str();
    GLuint vertexId, fragmentId;

    //Compile Vertex
    std::cout<<"Shader::Compiling Vertex Program"<<std::endl;
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertCharArr, nullptr);
    glCompileShader(vertexId);
    if (!ShaderCompileSuccess(vertexId, ShaderType::VERTEX_SHADER))
        return false;

    std::cout<<"Shader::Compiling Fragment Program"<<std::endl;
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragCharArr, nullptr);
    glCompileShader(fragmentId);
    if (!ShaderCompileSuccess(fragmentId, ShaderType::FRAGMENT_SHADER))
        return false;

    std::cout<<"Shader::Linking Shader Program"<<std::endl;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexId);
    glAttachShader(shaderProgram, fragmentId);
    glLinkProgram(shaderProgram);
    if (!ShaderLinkSuccess(shaderProgram))
        return false;

    std::cout << "Shader::Successfully compiled shader program" << std::endl;
    return true;
}

GLuint Shader::getId() const
{
    return shaderProgram;
}
