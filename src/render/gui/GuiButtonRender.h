//
// Created by dar on 2/4/16.
//

#ifndef C003_GUIBUTTONRENDER_H
#define C003_GUIBUTTONRENDER_H

#include <gui/GuiButton.h>
#include "GuiElementRender.h"

class GuiButtonRender : public GuiElementRender {

public:
    GuiButtonRender(const string &textureFile, const string &shader) : GuiElementRender(textureFile, shader) { }

    void render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        if (element->isVisible()) {
            const GuiButton *const b = (const GuiButton *const) element;

            this->texture.bindTexture(0);
            this->shaderProgram.useProgram();
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            int color = element->getColor();
            float ca = (color & 0x000000FF) / 255.0f;
            float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
            float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
            float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

            if (!b->isEnabled()) {
                double mod = 0.75f;
                cr *= mod;
                cg *= mod;
                cb *= mod;
            }

            shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

            double ratio = b->getWidth()/b->getHeight();
            double singular_ratio = ratio - (int)ratio;
            if (singular_ratio - (int)singular_ratio == 0) singular_ratio++;
            singular_ratio = singular_ratio / ceil(singular_ratio);
            for (int i = 0; i < ratio; i++) {
                this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(-(element->getX() + element->getHeight() +  i * element->getHeight() * singular_ratio) * scale, -(element->getY() + element->getHeight()) * scale, 0.0f));
                this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(element->getHeight() * scale * singular_ratio, element->getHeight() * scale, 1.0f));
                this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

                shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
                int texXPos = i == 0 ? 0 : (i == (int)(ratio - 1) ? 2 : 1);
                float x = (float) ((this->getTexPos(element) + texXPos) % atlasSize);
                float y = (float) ((this->getTexPos(element) + texXPos) / atlasSize);
                shaderProgram.setUniform("texPosX", x / atlasSize + 0.5f / texture.getWidth());
                shaderProgram.setUniform("texPosY", y / atlasSize + 0.5f / texture.getHeight());

                glBindVertexArray(this->vao);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
    }

protected:
    virtual int getTexPos(const GuiElement *const element) override {
        if (const GuiButton *const b = dynamic_cast<const GuiButton *const>(element)) {
            return element->getTexPos(b->getTexturesNum() > 1 && b->isPressed());
        }
        return 0;
    }
};

#endif //C003_GUIBUTTONRENDER_H
