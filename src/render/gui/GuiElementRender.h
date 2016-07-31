//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENTRENDER_H
#define C003_GUIELEMENTRENDER_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "gui/GuiElement.h"
#include "render/opengl.h"
#include "render/ShaderProgram.h"
#include "render/Texture.h"

class GuiElementRender {
public:
    GuiElementRender() { };
    GuiElementRender(const std::string &textureFile, const std::string &shader);
    ~GuiElementRender();
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale);
protected:
    const unsigned int atlasSize = 8;
    float vertices[8];
    GLuint vbo[2];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    Texture texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    virtual int getTexPos(const GuiElement &element) const;

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;
};

#endif //C003_GUIELEMENTRENDER_H
