//
// Created by dar on 11/20/15.
//

#ifndef C003_CSHADERPROGRAM_H
#define C003_CSHADERPROGRAM_H

#include "Shader.h"

using namespace std;
using namespace glm;

class ShaderProgram {
public:
    ShaderProgram();

    void createProgram();

    void deleteProgram();

    bool addShaderToProgram(Shader *shShader);

    bool linkProgram();

    void useProgram();

    GLuint getProgramID();

    // Setting vectors
    void setUniform(string sName, glm::vec2 *vVectors, int iCount = 1);

    void setUniform(string sName, const glm::vec2 vVector);

    void setUniform(string sName, glm::vec3 *vVectors, int iCount = 1);

    void setUniform(string sName, const glm::vec3 vVector);

    void setUniform(string sName, glm::vec4 *vVectors, int iCount = 1);

    void setUniform(string sName, const glm::vec4 vVector);

    // Setting floats
    void setUniform(string sName, float *fValues, int iCount = 1);

    void setUniform(string sName, const float fValue);

    // Setting 3x3 matrices
    void setUniform(string sName, glm::mat3 *mMatrices, int iCount = 1);

    void setUniform(string sName, const glm::mat3 mMatrix);

    // Setting 4x4 matrices
    void setUniform(string sName, glm::mat4 *mMatrices, int iCount = 1);

    void setUniform(string sName, const glm::mat4 mMatrix);

    // Setting integers
    void setUniform(string sName, int *iValues, int iCount = 1);

    void setUniform(string sName, const int iValue);

private:
    GLuint uiProgram; // ID of program
    bool bLinked; // Whether program was linked and is ready to use
};


#endif //C003_CSHADERPROGRAM_H
