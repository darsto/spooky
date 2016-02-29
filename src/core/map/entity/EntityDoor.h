//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYDOOR_H
#define C003_ENTITYDOOR_H

#include "EntityMoving.h"
#include <core/map/Map.h>

class EntityDoor : public EntityMoving {

public:
    EntityDoor(Map *map);

    virtual void setY(double y) override {
        Entity::setY(y);
        this->hinge->SetTransform(b2Vec2(this->hinge->GetPosition().x, (float32) (y - this->height * 0.5 - 0.125/*TODO +-*/)), this->hinge->GetAngle());
    }

    virtual void setX(double x) override {
        Entity::setX(x);
        this->hinge->SetTransform(b2Vec2((float32) (x - this->width * 0.5 - 0.375), this->hinge->GetPosition().y), this->hinge->GetAngle());
    }

    virtual void onCollision(IPositionable *object, char state) override {
        Entity::onCollision(object, state);
    }

    virtual ~EntityDoor() override {
        this->map->getWorld()->DestroyBody(this->body);
    }

private:
    b2Body *hinge;
};

#endif //C003_ENTITYDOOR_H
