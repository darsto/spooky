//
// Created by dar on 12/22/15.
//

#ifndef C003_CONTACTFILTER_H
#define C003_CONTACTFILTER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../map/entity/Entity.h"

class ContactFilter : public b2ContactFilter {

    bool doesCollide(void *a, void *b) {
        bool collisionAwithB = true, collisionBwithA = true;
        if (Entity *entity = reinterpret_cast<Entity *>(a)) {
            collisionAwithB = entity->doesCollide(reinterpret_cast<IPositionable *>(b));
        }
        if (Entity *entity = reinterpret_cast<Entity *>(b)) {
            collisionBwithA = entity->doesCollide(reinterpret_cast<IPositionable *>(a));
        }
        return collisionAwithB && collisionBwithA;
    }

    virtual bool ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB) override {
        void *bodyDataA = fixtureA->GetBody()->GetUserData();
        void *bodyDataB = fixtureB->GetBody()->GetUserData();
        return doesCollide(bodyDataA, bodyDataB);
    }

};

#endif //C003_CONTACTFILTER_H
