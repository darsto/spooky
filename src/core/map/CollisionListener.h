//
// Created by dar on 12/10/15.
//

#ifndef C003_COLLISIONLISTENER_H
#define C003_COLLISIONLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "../entity/Entity.h"

class CollisionListener : public b2ContactListener {

    void triggerContact(b2Contact *contact, char state) {
        void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        void *body2UserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (Entity *entity = static_cast<Entity*>(bodyUserData)) {
            entity->onCollision(static_cast<IPositionable*>(body2UserData), state);
        }
        if (Entity *entity = static_cast<Entity*>(body2UserData)) {
            entity->onCollision(static_cast<IPositionable*>(bodyUserData), state);
        }
    }

    void BeginContact(b2Contact *contact) {
        triggerContact(contact, 0);
    }

    void EndContact(b2Contact *contact) {
        triggerContact(contact, 1);
    }
};

#endif //C003_COLLISIONLISTENER_H
