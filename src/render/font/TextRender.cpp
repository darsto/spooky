/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "TextRender.h"
#include "gui/GuiText.h"
#include "render/RenderContext.h"

TextRender::TextRender(const RenderContext &context)
    : GuiElementRender(context, "font", "font") {

    m_atlasSize = 8;

    // TODO dirty hack, remove

    const texture::TexData &texData = m_atlas.atlasData()[0];
    float texWidth = 1.0f / m_atlasSize - 1.0f / texData.width();
    float texHeight = 1.0f / m_atlasSize - 1.0f / texData.height();

    /* square's vertices */
    float texCoords[8];

    /* bottom-left vertex */
    texCoords[0] = 0.0f, texCoords[1] = texHeight;

    /* bottom-right vertex*/
    texCoords[2] = texWidth, texCoords[3] = texHeight;

    /* top-left vertex */
    texCoords[4] = 0.0f, texCoords[5] = 0.0f;

    /* top-right vertex */
    texCoords[6] = texWidth, texCoords[7] = 0.0f;

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]); /* texture coords vbo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void TextRender::render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    int color = element.color();
    float ca = (color & 0x000000FF) / 255.0f;

    if (ca > 0.0f) {
        const GuiText &text = (const GuiText &) element;
        m_texture.bindTexture();
        m_shaderProgram.useProgram();

        float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
        float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
        float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

        m_shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

        scale *= text.scale();

        auto pos = getAbsolutePos(element);
        double x = pos.first;
        double y = pos.second;
        for (int i = 0; i < text.text().length(); i++) {
            if (text.text().at(i) == '\n') {
                x = text.x();
                y += (0.61 + 2 * text.TEXT_SPACING) * scale;
                continue;
            }
            int texId = text.texPos(i);
            if (texId == -1) {
                x += (text.TEXT_SPACESIZE + text.TEXT_SPACING) * scale;
                continue;
            }
            glm::mat4 tmpModelMatrix = glm::translate(m_modelMatrix, glm::vec3(-x, (int32_t) m_renderContext.windowHeight() - y, 0.0f));
            tmpModelMatrix = glm::scale(tmpModelMatrix, glm::vec3(scale, scale, 1.0f));

            m_shaderProgram.setUniform("modelViewMatrix", viewMatrix * tmpModelMatrix);
            m_shaderProgram.setUniform("projectionMatrix", projectionMatrix);

            int texX = texId % m_atlasSize, texY = texId / m_atlasSize;
            m_shaderProgram.setUniform("texPosX", (float) texX / m_atlasSize);
            m_shaderProgram.setUniform("texPosY", (float) texY / m_atlasSize);

            glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            x += (text.getGlyphSize(texId) + text.TEXT_SPACING) * scale;
        }
    }
}