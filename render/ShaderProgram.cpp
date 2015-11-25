//
// Created by dar on 11/20/15.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    linked = false;
}

void ShaderProgram::createProgram() {
    uiProgram = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(Shader *shader) {
    if (!shader->isLoaded()) return false;
    glAttachShader(uiProgram, shader->getID());
    return true;
}

bool ShaderProgram::linkProgram() {
    glLinkProgram(uiProgram);
    int linkStatus;
    glGetProgramiv(uiProgram, GL_LINK_STATUS, &linkStatus);
    this->linked = linkStatus == GL_TRUE;
    return this->linked;
}

void ShaderProgram::deleteProgram() {
    if (!this->linked) return;
    glDeleteProgram(uiProgram);
}

void ShaderProgram::useProgram() {
    if (linked) glUseProgram(uiProgram);
}

void ShaderProgram::setUniform(string name, float *values, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform1fv(loc, count, values);
}

void ShaderProgram::setUniform(string name, const float value) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform1fv(loc, 1, &value);
}

// Setting vectors
void ShaderProgram::setUniform(string name, glm::vec2 *vVectors, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform2fv(loc, count, (GLfloat *) vVectors);
}

void ShaderProgram::setUniform(string name, const glm::vec2 vVector) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform2fv(loc, 1, (GLfloat *) &vVector);
}

void ShaderProgram::setUniform(string name, glm::vec3 *vVectors, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform3fv(loc, count, (GLfloat *) vVectors);
}

void ShaderProgram::setUniform(string name, const glm::vec3 vVector) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform3fv(loc, 1, (GLfloat *) &vVector);
}

void ShaderProgram::setUniform(string name, glm::vec4 *vVectors, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform4fv(loc, count, (GLfloat *) vVectors);
}

void ShaderProgram::setUniform(string name, const glm::vec4 vVector) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform4fv(loc, 1, (GLfloat *) &vVector);
}

// Setting 3x3 matrices
void ShaderProgram::setUniform(string name, glm::mat3 *matrices, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniformMatrix3fv(loc, count, false, (GLfloat *) matrices);
}

void ShaderProgram::setUniform(string name, const glm::mat3 matrix) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniformMatrix3fv(loc, 1, false, (GLfloat *) &matrix);
}

// Setting 4x4 matrices
void ShaderProgram::setUniform(string name, glm::mat4 *matrices, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniformMatrix4fv(loc, count, false, (GLfloat *) matrices);
}

void ShaderProgram::setUniform(string name, const glm::mat4 matrix) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniformMatrix4fv(loc, 1, false, (GLfloat *) &matrix);
}

// Setting integers
void ShaderProgram::setUniform(string name, int *values, int count) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform1iv(loc, count, values);
}

void ShaderProgram::setUniform(string name, const int value) {
    int loc = glGetUniformLocation(uiProgram, name.c_str());
    glUniform1i(loc, value);
}

GLuint ShaderProgram::getProgramID() {
    return uiProgram;
}
