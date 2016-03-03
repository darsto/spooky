//
// Created by dar on 3/3/16.
//

#ifndef C003_ENTITYTABLERENDER_H
#define C003_ENTITYTABLERENDER_H

#include "DefaultEntityRender.h"

class EntityTableRender : public DefaultEntityRender {

public:
    EntityTableRender() : DefaultEntityRender("furniture", "shader") {
        /* initializing square's vertices */
        this->vertices[0] = -1.0f;
        this->vertices[1] = 1.0f;

        this->vertices[3] = -1.0f;
        this->vertices[4] = 0.0f;

        this->vertices[6] = 2.0f;
        this->vertices[7] = 1.0f;

        this->vertices[9] = 2.0f;
        this->vertices[10] = 0.0f;

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]); /* vertices vbo */
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), this->vertices, GL_STATIC_DRAW);

        float width = (float) (3.0 - (atlasSize + 1.5) / texture.getWidth()) / atlasSize;
        float height = (float) (1.0 - (atlasSize + 1.5) / texture.getWidth()) / atlasSize;
        float tCoords[] = {
            width, 0.0f,
            width, height,
            0.0f, 0.0f,
            0.0f, height,
        };

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]); /* texture coords vbo */
        glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tCoords, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override {
        DefaultEntityRender::render(entity, projectionMatrix, viewMatrix, scale);
    }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        return 4;
    }

};

#endif //C003_ENTITYTABLERENDER_H
