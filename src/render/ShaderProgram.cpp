//
// Created by dar on 11/20/15.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    linked = false;
}

ShaderProgram::~ShaderProgram() {
    if (!this->linked)return;
    this->linked = false;
    glDeleteProgram(uiProgram);
}


void ShaderProgram::createProgram() {
    uiProgram = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(Shader *shader) {
    if (!shader->isLoaded())return false;

    glAttachShader(uiProgram, shader->getID());

    return true;
}

bool ShaderProgram::linkProgram() {
    glLinkProgram(uiProgram);
    int iLinkStatus;
    glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
    linked = iLinkStatus == GL_TRUE;
    return linked;
}

void ShaderProgram::useProgram() {
    if (linked) glUseProgram(uiProgram);
}

void ShaderProgram::setUniform(string sName, float* fValues, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::setUniform(string sName, const float fValue)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::setUniform(string sName, glm::vec2* vVectors, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(string sName, const glm::vec2 vVector)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(string sName, glm::vec3* vVectors, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(string sName, const glm::vec3 vVector)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(string sName, glm::vec4* vVectors, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(string sName, const glm::vec4 vVector)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void ShaderProgram::setUniform(string sName, glm::mat3* mMatrices, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix3fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(string sName, const glm::mat3 mMatrix)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix3fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(string sName, glm::mat4* mMatrices, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix4fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(string sName, const glm::mat4 mMatrix)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix4fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting integers

void ShaderProgram::setUniform(string sName, int* iValues, int iCount)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::setUniform(string sName, const int iValue)
{
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1i(iLoc, iValue);
}

GLuint ShaderProgram::getProgramID() {
    return uiProgram;
}