/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_FONT_TEXTRENDER_H
#define C003_RENDER_FONT_TEXTRENDER_H

#include "render/gui/GuiElementRender.h"
#include "render/gui/GuiRenderable.h"

class TextRender : public GuiRenderable {
public:
    TextRender(const ApplicationContext &applicationContext, const RenderContext &context);
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
    ~TextRender();

private:
    uint32_t m_atlasSize = 8;
    GLuint m_vbo[2];
    GLuint m_vao;
    ShaderProgram m_shaderProgram;
    texture::Texture m_texture;
    glm::mat4 m_modelMatrix = glm::mat4(1.0);

    static texture::TexData m_texData;
};

#endif //C003_RENDER_FONT_TEXTRENDER_H
