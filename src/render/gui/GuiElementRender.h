//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENTRENDER_H
#define C003_GUIELEMENTRENDER_H

#define GLM_FORCE_RADIANS
#include "../../gui/GuiElement.h"
#include "../opengl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../ShaderProgram.h"
#include "../Texture.h"

class GuiElementRender {
public:
    GuiElementRender() { };
    GuiElementRender(const string &textureFile, const string &shader);
    ~GuiElementRender();
    virtual void render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale);
protected:
    const unsigned int atlasSize = 8;
    float vertices[12];
    GLuint vbo[2];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    Texture texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    virtual int getTexPos(const GuiElement *const element);

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;
};

#endif //C003_GUIELEMENTRENDER_H
