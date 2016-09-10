/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_GUI_GUIELEMENTRENDER_H
#define C003_RENDER_GUI_GUIELEMENTRENDER_H

#include <glm/glm.hpp>

#include "render/opengl.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "render/texture/Atlas.h"

class GuiElement;

class GuiElementRender {
public:
    GuiElementRender(const std::string &textureFile, const std::string &shader);
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale);
    ~GuiElementRender();

protected:
    util::Rectangle getTexPos(const GuiElement &element) const;

    unsigned int atlasSize;
    float vertices[8];
    GLuint vbo[2];
    GLuint vao;
    ShaderProgram shaderProgram;
    texture::Atlas texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);
};

#endif //C003_RENDER_GUI_GUIELEMENTRENDER_H
