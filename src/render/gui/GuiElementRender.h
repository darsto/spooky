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
#include "render/texture/Texture.h"
#include "GuiRenderable.h"

class GuiElement;
class RenderContext;

class GuiElementRender : public GuiRenderable {
public:
    GuiElementRender(const RenderContext &context);
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
    ~GuiElementRender();

private:
    util::Rectangle getTexPos(const GuiElement &element) const;

    uint32_t m_atlasSize;
    GLuint m_vbo[2];
    GLuint m_vao;
    ShaderProgram m_shaderProgram;
    texture::Texture m_texture;
    glm::mat4 m_modelMatrix = glm::mat4(1.0);

    static texture::Atlas m_atlas;
};

#endif //C003_RENDER_GUI_GUIELEMENTRENDER_H
