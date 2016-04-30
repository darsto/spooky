//
// Created by dar on 3/3/16.
//

#ifndef C003_ENTITYWALLRENDER_H
#define C003_ENTITYWALLRENDER_H

#include "DefaultEntityRender.h"

class EntityWallRender : public DefaultEntityRender {

public:
    EntityWallRender() : DefaultEntityRender("furniture", "wall") { }

    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        this->shaderProgram.useProgram();

        Cache *cache = nullptr;

        if (entity->getId() < tmpCacheSize) {
            cache = matrixCache[entity->getId()];
            if (cache == nullptr) {
                cache = addToCache(new Cache(), entity);
            }
        } else {
            cache = addToCache(new Cache(), entity);
        }

        if (cache == nullptr || entity->toBeRedrawn() || cache->scale != scale) {
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            glm::mat4x4 tmpModelMatrixVal;
            //Walls are scaled to their dimensions, so they need different render positioning
            tmpModelMatrixVal = glm::translate(this->modelMatrix, glm::vec3(0.0f - (entity->getX() - 0.5) * scale, 0.0f - (entity->getY() - 0.5) * scale, 0.0f));

            tmpModelMatrixVal = glm::scale(tmpModelMatrixVal, glm::vec3((entity->getWidth()) * scale, (entity->getHeight()) * scale, 1.0f));
            this->tmpModelMatrix = &tmpModelMatrixVal;

            cache->readyModelMatrix = *this->tmpModelMatrix;
            cache->scale = scale;
        } else {
            this->tmpModelMatrix = &cache->readyModelMatrix;
        }

        shaderProgram.setUniform("modelViewMatrix", viewMatrix * *this->tmpModelMatrix);

        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

};

#endif //C003_ENTITYWALLRENDER_H
