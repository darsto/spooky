//
// Created by dar on 3/5/16.
//

#ifndef C003_VOIDRENDER_H
#define C003_VOIDRENDER_H

#include "../Texture.h"
#include "../Shader.h"
#include "../ShaderProgram.h"

class VoidRender{

public:
    VoidRender();
    ~VoidRender();
    virtual void render(double x, double y, double width, double height, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.65f);
private:
    float vertices[12];
    GLuint vbo[1];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;

};

#endif //C003_VOIDRENDER_H
