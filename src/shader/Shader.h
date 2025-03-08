//
// Created by ssj5v on 06-03-2025.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "glad/glad.h"

class Shader {
private:
    unsigned int shaderProgram;
public:
    Shader() = default;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    bool compile(const std::string& vertexPath, const std::string& fragmentPath);
    [[nodiscard]] GLuint getId() const;
    [[nodiscard]] bool isValid() const {return  shaderProgram != 0;}
};


#endif //SHADER_H
