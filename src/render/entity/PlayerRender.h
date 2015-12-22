//
// Created by dar on 12/22/15.
//

#ifndef C003_PLAYERRENDER_H
#define C003_PLAYERRENDER_H

#include "DefaultEntityRender.h"
#include "../../core/entity/Player.h"

class PlayerRender : public DefaultEntityRender {
public:
    PlayerRender() : DefaultEntityRender("player", "shader") { }

    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        if (((const Player* const) entity)->getToy() == nullptr) {
            this->texture.bindTexture(0);
            this->shaderProgram.useProgram();
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            this->tmpModelMatrix = glm::translate(this->modelMatrix,
                                                  glm::vec3(0.0f - (entity->getX() - entity->getWidth() / 2) * scale, 0.0f - (entity->getY() - entity->getHeight() / 2) * scale, 0.0f));
            this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));
            this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

            shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
            shaderProgram.setUniform("texPosX", (float) (this->getTexPos() % atlasSize) / atlasSize);
            shaderProgram.setUniform("texPosY", (float) (this->getTexPos() / atlasSize) / atlasSize);

            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }


};

#endif //C003_PLAYERRENDER_H
