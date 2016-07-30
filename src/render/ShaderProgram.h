//
// Created by dar on 11/20/15.
//

#ifndef C003_CSHADERPROGRAM_H
#define C003_CSHADERPROGRAM_H
#pragma once

#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    void createProgram();
    bool addShaderToProgram(Shader *shader);
    bool linkProgram();
    void useProgram();
    GLuint getProgramID();
    // Setting vectors
    void setUniform(std::string name, glm::vec2 *vectors, int count = 1);
    void setUniform(std::string name, const glm::vec2 vector);
    void setUniform(std::string name, glm::vec3 *vectors, int count = 1);
    void setUniform(std::string name, const glm::vec3 vector);
    void setUniform(std::string name, glm::vec4 *vectors, int count = 1);
    void setUniform(std::string name, const glm::vec4 vector);
    // Setting floats
    void setUniform(std::string name, float *values, int count = 1);
    void setUniform(std::string name, const float value);
    // Setting 3x3 matrices
    void setUniform(std::string name, glm::mat3 *matrices, int count = 1);
    void setUniform(std::string name, const glm::mat3 matrix);
    // Setting 4x4 matrices
    void setUniform(std::string name, glm::mat4 *matrices, int count = 1);
    void setUniform(std::string name, const glm::mat4 matrix);
    // Setting integers
    void setUniform(std::string name, int *iValues, int count = 1);
    void setUniform(std::string name, const int iValue);

private:
    GLuint uiProgram;
    bool linked;
};


#endif //C003_CSHADERPROGRAM_H
