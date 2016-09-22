/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "GuiElementRender.h"
#include "gui/GuiElement.h"
#include "Config.h"
#include "render/RenderContext.h"

GuiElementRender::GuiElementRender(const RenderContext &context, const std::string &textureFile, const std::string &shader, glm::mat4 projectionMatrix)
    : m_renderContext(context),
      m_atlas(textureFile, 4, true),
      m_shaderProgram() {

    std::vector<texture::TexData> &texMipmaps = m_atlas.atlasData();

    m_texture.bindTexture();
    m_texture.samplerParameter(GL_TEXTURE_MAX_LEVEL, texMipmaps.size() - 1);

    for (int level = 0; level < texMipmaps.size(); ++level) {
        m_texture.loadTex(texMipmaps[level], level);
    }

    m_texture.filtering(texture::Texture::MagFilter::BILINEAR, texture::Texture::MinFilter::BILINEAR_MIPMAP);
    m_atlasSize = std::sqrt<uint32_t>(m_atlas.getElementsNum());

    Shader vertShader(shader + ".vert", GL_VERTEX_SHADER);
    Shader fragShader(shader + ".frag", GL_FRAGMENT_SHADER);

    m_shaderProgram.addShader(vertShader);
    m_shaderProgram.addShader(fragShader);

    /** square's vertices */
    float vertices[8];
    float texCoords[8];

    float texWidth = 1.0f / m_atlasSize - 1.0f / texMipmaps[0].width();
    float texHeight = 1.0f / m_atlasSize - 1.0f / texMipmaps[0].height();

    /** bottom-left vertex */
    vertices[0] = 0.0f, vertices[1] = -1.0f;
    texCoords[0] = 0.0f, texCoords[1] = texHeight;

    /** bottom-right vertex*/
    vertices[2] = -1.0f, vertices[3] = -1.0f;
    texCoords[2] = texWidth, texCoords[3] = texHeight;

    /** top-left vertex */
    vertices[4] = 0.0f, vertices[5] = 0.0f;
    texCoords[4] = 0.0f, texCoords[5] = 0.0f;

    /** top-right vertex */
    vertices[6] = -1.0f, vertices[7] = 0.0f;
    texCoords[6] = texWidth, texCoords[7] = 0.0f;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(2, m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindAttribLocation(m_shaderProgram.id(), 0, "inPosition");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]); /* texture coords vbo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glBindAttribLocation(m_shaderProgram.id(), 1, "inCoord");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_shaderProgram.linkProgram();
    m_shaderProgram.useProgram();
    m_shaderProgram.setUniform("projectionMatrix", projectionMatrix);
    m_shaderProgram.setUniform("gSampler", m_texture.activeTex());
}

void GuiElementRender::render(const GuiElement &element, glm::mat4 viewMatrix, double scale) {
    int color = element.color();
    float ca = (color & 0x000000FF) / 255.0f;

    if (ca > 0.0f) {
        m_texture.bindTexture();
        m_shaderProgram.useProgram();

        float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
        float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
        float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

        m_shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

        auto pos = getAbsolutePos(element);
        glm::mat4 tmpModelMatrix = glm::translate(m_modelMatrix, glm::vec3(- (int32_t) pos.first * scale, (int32_t) m_renderContext.windowHeight() - pos.second * scale, 0.0f));

        tmpModelMatrix = glm::translate(tmpModelMatrix, glm::vec3(0.5 * element.width() * scale, 0.5 * element.height() * scale, 0.0)); // Translate to the middle of the entity
        tmpModelMatrix = glm::rotate(tmpModelMatrix, (const float) element.angle(), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
        tmpModelMatrix = glm::translate(tmpModelMatrix, glm::vec3(-0.5 * element.width() * scale, -0.5 * element.height() * scale, 0.0)); // Translate back to the origin

        tmpModelMatrix = glm::scale(tmpModelMatrix, glm::vec3(element.width() * scale, element.height() * scale, 1.0f));

        m_shaderProgram.setUniform("modelViewMatrix", viewMatrix * tmpModelMatrix);

        util::Rectangle tex = getTexPos(element);

        float x = (float) tex.x() / m_texture.width();
        float y = (float) tex.y() / m_texture.height();

        m_shaderProgram.setUniform("texPosX", x + 0.5f / m_texture.width());
        m_shaderProgram.setUniform("texPosY", y + 0.5f / m_texture.height());

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
}

std::pair<uint32_t, uint32_t> GuiElementRender::getAbsolutePos(const GuiElement &element) {
    double px = element.x();
    double py = element.y();

    int windowWidth = m_renderContext.windowWidth();
    int windowHeight = m_renderContext.windowHeight();

    uint8_t pos = static_cast<uint8_t>(element.pos());

    switch (static_cast<GuiPos>(pos & 0x03)) {
        case GuiPos::RIGHT:
            px = windowWidth - px - element.width();
            break;
        case GuiPos::CENTER:
            px += -element.width() / 2 + windowWidth / 2;
            break;
    }

    switch (static_cast<GuiPos>(pos & 0x0c)) {
        case GuiPos::BOTTOM:
            py = windowHeight - py - element.height();
            break;
        case GuiPos::MIDDLE:
            py += -element.height() / 2 + windowHeight / 2;
            break;
    }

    return std::pair<uint32_t, uint32_t>(px, py);
}

util::Rectangle GuiElementRender::getTexPos(const GuiElement &element) const {
    return m_atlas.element(element.texPos());
}

GuiElementRender::~GuiElementRender() {
    glDeleteBuffers(2, m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
