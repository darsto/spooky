//
// Created by dar on 2/11/16.
//

#include "TextRender.h"
#include <gui/GuiText.h>

TextRender::TextRender() : GuiElementRender("font", "font") { }

void TextRender::render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    if (element.visible()) {
        const GuiText &text = (const GuiText &) element;
        texture.bindTexture(0);
        this->shaderProgram.useProgram();
        this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniform("gSampler", texture.boundId());

        int color = element.color();
        float ca = (color & 0x000000FF) / 255.0f;
        float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
        float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
        float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

        shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

        scale *= text.scale();

        double x = text.x();
        double y = text.y();
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
            this->tmpModelMatrix = glm::translate(this->modelMatrix, -glm::vec3(x, y, 0.0f));
            this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));

            shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

            int texX = texId % atlasSize, texY = texId / atlasSize;
            shaderProgram.setUniform("texPosX", (float) texX / atlasSize);
            shaderProgram.setUniform("texPosY", (float) texY / atlasSize);

            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            x += (text.getGlyphSize(texId) + text.TEXT_SPACING) * scale;
        }
    }
}