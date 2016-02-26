//
// Created by dar on 2/11/16.
//

#include "TextRender.h"
#include <gui/GuiText.h>

TextRender::TextRender() : GuiElementRender("font", "font") { }

void TextRender::render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    const GuiText *const text = (const GuiText *const) element;
    texture.bindTexture(0);
    this->shaderProgram.useProgram();
    this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
    this->shaderProgram.setUniform("gSampler", texture.getBoundId());

    scale *= text->getScale();

    double x = text->getX();
    for (int i = 0; i < text->getString().length(); i++) {
        int texId = text->getTexPos(i);
        if (texId == -1) {
            x += text->TEXT_SPACESIZE * scale + text->SPACING_PX;
            continue;
        }
        this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(-(x + scale), -(text->getY() + scale), 0.0f));
        this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));

        shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

        int texX = texId % atlasSize,  texY = texId / atlasSize;
        shaderProgram.setUniform("texPosX", 0.5f / texture.getWidth() + (float) texX / atlasSize);
        shaderProgram.setUniform("texPosY", 0.5f / texture.getHeight() + (float) texY / atlasSize);

        int color = text->getColor();
        float r = ((color & 0xFF000000) >> 24) / 255.0f;
        float g = ((color & 0x00FF0000) >> 16) / 255.0f;
        float b = ((color & 0x0000FF00) >> 8) / 255.0f;
        float a = (color & 0x000000FF) / 255.0f;

        shaderProgram.setUniform("colorMod", glm::vec4(r, g, b, a));

        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x += text->getGlyphSize(texId) * scale + text->SPACING_PX;
    }
}