//
// Created by dar on 3/4/16.
//

#ifndef C003_ENTITYSTAIN_H
#define C003_ENTITYSTAIN_H

#include "Entity.h"
#include "EntityMachinery.h"

class EntityGlassDebris : public EntityMoving {

public:
    EntityGlassDebris(Map *map) : EntityMoving(map, 0.3, 0.2) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 0.25f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
        this->type = (char) (rand() % 2);
    }

    virtual void onCollision(IPositionable *object, char state) override {
        bool sensor = false;
        if (EntityHoover *h = dynamic_cast<EntityHoover *>(object)) {
            this->collidingEntity = state == 0 ? h : nullptr;
            if (state == 0 && h->getHost() != nullptr) {
                sensor = true;
            }
        }
        this->body->GetFixtureList()[0].SetSensor(sensor);
    }

    virtual void update(double deltaTime) override {
        Entity::update(0);
        if (this->collidingEntity != nullptr) {
            double dx = this->collidingEntity->getX() - this->collidingEntity->getWidth() / 2 - this->getX() + this->getWidth() / 2;
            double dy = this->collidingEntity->getY() - this->collidingEntity->getHeight() / 2 - this->getY() + this->getHeight() / 2;
            if (dx * dx + dy * dy < 0.06) {
                this->remove();
            }
        }
    }

    char getType() const {
        return type;
    }

private:
    char type = 0;
    EntityHoover *collidingEntity = nullptr;
};

#endif //C003_ENTITYSTAIN_H
