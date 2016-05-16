//
// Created by dar on 11/29/15.
//

#include <files.h>
#include "Entity.h"
#include "core/map/Map.h"
#include "EntityPlayer.h"
#include <core/LevelContext.h>

Entity::Entity(LevelContext &levelContext, double width, double height) : id(Entity::getNextEntityId()), levelContext(levelContext) {
    this->width = width - 0.025;
    this->height = height - 0.025;
    bodyDef.type = b2_staticBody;
    body = this->getMap()->getWorld()->CreateBody(&bodyDef);
    body->SetUserData(this);
    body->SetAngularDamping(30.0);
    body->SetLinearDamping(30.0);

    this->levelContext.initState(this->script.state);
}

void Entity::update(double deltaTime) {
    double newX = body->GetPosition().x + this->width * 0.5;
    double newY = body->GetPosition().y + this->height * 0.5;

    if (newX != this->x || newY != this->y) {
        this->getBody()->SetAwake(true);
        if (this->script.move.loaded) {
            this->script.move.function();
        }
    }

    this->x = newX;
    this->y = newY;

    if (this->script.update.loaded) {
        this->script.update.function();
    }
}

void Entity::onCollision(IPositionable *object, char state) {
    if (this->script.collision.loaded) {
        this->script.collision.function();
    }
}

void Entity::setY(double y) {
    body->SetTransform(b2Vec2(body->GetPosition().x, (float32) (y - this->height * 0.5)), body->GetAngle());
}

void Entity::setX(double x) {
    body->SetTransform(b2Vec2((float32) (x - this->width * 0.5), body->GetPosition().y), body->GetAngle());
}

template<int type>
void Entity::setScript(std::string file) {
    file = getFilePath("data/scripts/levels/" + this->getMap()->getLevelName() + "/" + file + ".lua");
    Script::Handler *handler = nullptr;
    switch (type) {
        case 0:
            handler = &this->script.init;
            break;
        case 1:
            handler = &this->script.update;
            break;
        case 2:
            handler = &this->script.move;
            break;
        case 3:
            handler = &this->script.collision;
            break;
        case 4:
            handler = &this->script.death;
            break;
        default:
            return;
    }
    handler->function = this->script.state.loadfile(file);
    handler->loaded = true;
}

template void Entity::setScript<0>(std::string);
template void Entity::setScript<1>(std::string);
template void Entity::setScript<2>(std::string);
template void Entity::setScript<3>(std::string);
template void Entity::setScript<4>(std::string);

void Entity::remove() {
    if (this->script.death.loaded) {
        this->script.death.function();
    }
    this->toBeDeleted = true;
}

Entity::~Entity() {
    this->getMap()->getWorld()->DestroyBody(this->body);
}

unsigned int Entity::maxEntityId = 0;

unsigned int Entity::getNextEntityId() {
    Entity::maxEntityId++;
    return Entity::maxEntityId;
};

Map *Entity::getMap() const {
    return this->levelContext.getMap();
}

void Entity::callInitScript() {
    if (this->script.init.loaded) {
        this->script.init.function();
        this->script.init.loaded = false;
    }
}