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

    double getRelativeAngle(double angle1, double angle2, double dmg_x, double dmg_y) {
        while (angle1 > M_PI_2) { angle1 -= M_PI_2; }
        while (angle2 > M_PI_2) { angle2 -= M_PI_2; }
        while (angle1 < -M_PI_2) { angle1 += M_PI_2; }
        while (angle2 < -M_PI_2) { angle2 += M_PI_2; }
        double angle = angle1 - angle2;
        if (angle < 0) angle *= -1;
        if ((std::abs(dmg_x) < std::abs(dmg_y) && (dmg_y > 0)) ||
            ((std::abs(dmg_x) > std::abs(dmg_y)) && (dmg_x < 0)))
            angle = M_PI_2 - angle;
        return angle;
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
                double angle2 = 0;
                if (Entity *t = dynamic_cast<Entity *>(i == 0 ? body2UserData : bodyUserData)) {
                    angle2 = t->getAngle();
                }
                if (t->getHost() != nullptr && getRelativeAngle(atan2(dmg_y, dmg_x), angle2, dmg_x, dmg_y) < M_PI_4 / 3) {
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
