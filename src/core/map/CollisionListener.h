//
// Created by dar on 12/10/15.
//

#ifndef C003_COLLISIONLISTENER_H
#define C003_COLLISIONLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "../entity/Entity.h"

class CollisionListener : public b2ContactListener {

    void triggerContact(b2Contact *contact, char state) {
        IPositionable *bodyUserData = static_cast<IPositionable*>(contact->GetFixtureA()->GetBody()->GetUserData());
        IPositionable *body2UserData = static_cast<IPositionable*>(contact->GetFixtureB()->GetBody()->GetUserData());
        if (Entity *entity = dynamic_cast<Entity *>(bodyUserData)) {
            entity->onCollision(body2UserData, state);
        }
        if (Entity *entity = dynamic_cast<Entity *>(body2UserData)) {
            entity->onCollision(bodyUserData, state);
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
