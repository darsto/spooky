//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPERENDER_H
#define C003_SIMPLESHAPERENDER_H

#include <core/entity/SimpleShape.h>
#include "DefaultEntityRender.h"

class SimpleShapeRender : public DefaultEntityRender {
public:
    SimpleShapeRender() : DefaultEntityRender("shapes", "shader") { }

    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
            this->texture.bindTexture(0);
            this->shaderProgram.useProgram();
            this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
            this->shaderProgram.setUniform("gSampler", texture.getBoundId());

            this->tmpModelMatrix = glm::translate(this->modelMatrix,
                                                  glm::vec3(0.0f - (entity->getX() - entity->getWidth() / 2) * scale, 0.0f - (entity->getY() - entity->getHeight() / 2) * scale, 0.0f));
            this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));
            this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

            shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
            shaderProgram.setUniform("texPosX", (float) (((const SimpleShape *const) entity)->getTexPos() % atlasSize) / atlasSize);
            shaderProgram.setUniform("texPosY", (float) (((const SimpleShape *const) entity)->getTexPos() / atlasSize) / atlasSize);

            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
};

#endif //C003_SIMPLESHAPERENDER_H
