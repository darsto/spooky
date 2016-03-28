//
// Created by dar on 12/22/15.
//

#ifndef C003_PLAYERRENDER_H
#define C003_PLAYERRENDER_H

#include "DefaultEntityRender.h"
#include <core/map/entity/EntityPlayer.h>
#include <core/map/Map.h>

class PlayerRender : public DefaultEntityRender {
public:
    PlayerRender() : DefaultEntityRender("player", "shader") { }

    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        const EntityPlayer *const player = ((const EntityPlayer *const) entity);
        if (player->getToy() == nullptr || player->getEjectTime() > 0.0) {
            this->texture.bindTexture(0);
            this->shaderProgram.useProgram();
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            this->tmpModelMatrix = glm::translate(this->modelMatrix,
                                                  glm::vec3(0.0f - (entity->getX() - entity->getWidth() / 2) * scale, 0.0f - (entity->getY() - entity->getHeight() / 2) * scale, 0.0f));

            this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(0.5 * scale, 0.5 * scale, 0.0)); // Translate to the middle of the entity
            this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, (const float) entity->getAngle(), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
            this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(-0.5 * scale, -0.5 * scale, 0.0)); // Translate back to the origin


            double oldScale = scale;
            scale *= player->getEjectTime() >= 0.0 ? 1.0 - player->getEjectTime() : -player->getEjectTime();

            this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));

            this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(0.5 * (oldScale - scale) / scale, 0.5 * (oldScale - scale) / scale, 0.0)); // Translate to the center of scaling

            shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
            shaderProgram.setUniform("texPosX", 1.0f / this->texture.getWidth() + (float) (this->getTexPos(entity) % atlasSize) / atlasSize);
            shaderProgram.setUniform("texPosY", 1.0f / this->texture.getWidth() + (float) (this->getTexPos(entity) / atlasSize) / atlasSize);

            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        const EntityPlayer *const player = ((const EntityPlayer *const) entity);
        return (int) std::fmod((sin(player->getTailAnimation()) + 1.0) * 8, 16.0);
    }

};

#endif //C003_PLAYERRENDER_H
