//
// Created by dar on 2/26/16.
//

#include <gui/GuiTextBubble.h>
#include "GuiElementRender.h"

#ifndef C003_GUIBUBBLERENDER_H
#define C003_GUIBUBBLERENDER_H

class GuiTextBubbleRender : public GuiElementRender {

public:

    GuiTextBubbleRender(const string &textureFile, const string &shader) : GuiElementRender(textureFile, shader) { }

    virtual void render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        if (element->isVisible()) {
            const GuiTextBubble *const b = (const GuiTextBubble *const) element;

            this->texture.bindTexture(0);
            this->shaderProgram.useProgram();
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            int color = element->getColor();
            float cr = ((color & 0xFF000000) >> 24) / 255.0f;
            float cg = ((color & 0x00FF0000) >> 16) / 255.0f;
            float cb = ((color & 0x0000FF00) >> 8) / 255.0f;
            float ca = (color & 0x000000FF) / 255.0f;

            shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

            if (ca != 1.0f) {
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            double xPieces = b->getWidth() / b->resolution;
            double yPieces = b->getHeight() / b->resolution;

            double singularWidth = xPieces / ceil(xPieces);
            double singularHeight = yPieces / ceil(yPieces);

            xPieces = (int) ceil(xPieces);
            yPieces = (int) ceil(yPieces);

            for (int y = 0; y < yPieces; y++) {
                for (int x = 0; x < xPieces; x++) {
                    this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(-(element->getX() + b->resolution * singularWidth + x * b->resolution * singularWidth) * scale,
                                                                                       -(element->getY() + b->resolution * singularHeight + y * b->resolution * singularHeight) * scale, 0.0f));
                    this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale * b->resolution * singularWidth, scale * b->resolution * singularHeight, 1.0f));

                    shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
                    int texId = 0;
                    if (y == 0 && x == 0) texId = 0;
                    else if (y == 0 && x == (int) xPieces - 1) texId = 2;
                    else if (y == 0) texId = 1;
                    else if (y == (int) yPieces - 1 && x == 0) texId = 16;
                    else if (y == (int) yPieces - 1 && x == (int) xPieces - 1) texId = 18;
                    else if (y == (int) yPieces - 1) texId = 17;
                    else if (x == 0) texId = 8;
                    else if (x == (int) xPieces - 1) texId = 10;
                    else texId = 9;

                    float texX = (float) ((this->getTexPos(b) + texId + 20) % atlasSize);
                    float texY = (float) ((this->getTexPos(b) + texId + 20) / atlasSize);
                    shaderProgram.setUniform("texPosX", texX / atlasSize + 0.5f / texture.getWidth());
                    shaderProgram.setUniform("texPosY", texY / atlasSize + 0.5f / texture.getHeight());

                    glBindVertexArray(this->vao);
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                }
            }

            if (ca != 1.0f) {
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            }
        }
    }
};

#endif //C003_GUIBUBBLERENDER_H
