//
// Created by dar on 3/3/16.
//

#ifndef C003_ENTITYTABLERENDER_H
#define C003_ENTITYTABLERENDER_H

#include "DefaultEntityRender.h"

class EntityWideRender : public DefaultEntityRender {

public:
    EntityWideRender(int texId = 0) : DefaultEntityRender("furniture", "shader", texId) {
        /* initializing square's vertices */
        this->vertices[0] = -1.0f;
        this->vertices[1] = 1.0f;

        this->vertices[2] = -1.0f;
        this->vertices[3] = 0.0f;

        this->vertices[4] = 2.0f;
        this->vertices[5] = 1.0f;

        this->vertices[6] = 2.0f;
        this->vertices[7] = 0.0f;

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]); /* vertices vbo */
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), this->vertices, GL_STATIC_DRAW);

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

protected:
    virtual int getTexPos(const Entity *const entity) override {
        int texPos = -1;
        if (dynamic_cast<const EntityTable *const>(entity)) texPos = 4;
        if (dynamic_cast<const EntityCoffeeTable *const>(entity)) texPos = 8;
        if (dynamic_cast<const EntityCouch *const>(entity)) texPos = 13;
        return texPos;
    }

};

#endif //C003_ENTITYTABLERENDER_H
