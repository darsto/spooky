//
// Created by dar on 12/10/15.
//

#ifndef C003_COLLISIONLISTENER_H
#define C003_COLLISIONLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <core/map/entity/Entity.h>
#include <core/map/entity/EntityToy.h>

class CollisionListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) {
        triggerContact(contact, 0);
    }

    void EndContact(b2Contact *contact) {
        triggerContact(contact, 1);
    }

    virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override {
        b2ContactListener::PreSolve(contact, oldManifold);
        IPositionable *bodyUserData = static_cast<IPositionable *>(contact->GetFixtureA()->GetBody()->GetUserData());
        IPositionable *body2UserData = static_cast<IPositionable *>(contact->GetFixtureB()->GetBody()->GetUserData());
        IPositionable *d = bodyUserData;
        for (int i = 0; i < 2; i++, d = body2UserData) {
            if (EntityToy *t = dynamic_cast<EntityToy *>(d)) {
                double dmg_x = t->getBody()->GetLinearVelocity().x;
                double dmg_y = t->getBody()->GetLinearVelocity().y;
                double dmg = sqrt(dmg_x * dmg_x + dmg_y * dmg_y) * 0.5;
                if (t->getHost() != nullptr) {
                    t->damage(dmg);
                    t->resetMovingTime();
                }
            }
        }
    }

private:
    void triggerContact(b2Contact *contact, char state) {
        IPositionable *bodyUserData = static_cast<IPositionable *>(contact->GetFixtureA()->GetBody()->GetUserData());
        IPositionable *body2UserData = static_cast<IPositionable *>(contact->GetFixtureB()->GetBody()->GetUserData());
        if (Entity *entity = dynamic_cast<Entity *>(bodyUserData)) {
            entity->onCollision(body2UserData, state);
        }
        if (Entity *entity = dynamic_cast<Entity *>(body2UserData)) {
            entity->onCollision(bodyUserData, state);
        }
    }
};

#endif //C003_COLLISIONLISTENER_H
