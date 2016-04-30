//
// Created by dar on 11/29/15.
//

#include <files.h>
#include "Entity.h"
#include "core/map/Map.h"
#include "EntityPlayer.h"

Entity::Entity(Map *map, double width, double height) : id(Entity::getNextEntityId()), map(map) {
    this->width = width - 0.025;
    this->height = height - 0.025;
    bodyDef.type = b2_staticBody;
    body = this->map->getWorld()->CreateBody(&bodyDef);
    body->SetUserData(this);
    body->SetAngularDamping(30.0);
    body->SetLinearDamping(30.0);

    this->script.state["Entity"].setClass(kaguya::ClassMetatable<Entity>()
                                              .addConstructor<Map *, double, double>()
                                              .addMember("getId", &Entity::getId)
                                              .addMember("getX", &Entity::getX)
                                              .addMember("getY", &Entity::getY)
                                              .addMember("getAngle", &Entity::getAngle)
                                              .addMember("getWidth", &Entity::getWidth)
                                              .addMember("getHeight", &Entity::getHeight)
                                              .addMember("setX", &Entity::setX)
                                              .addMember("setY", &Entity::setY)
                                              .addMember("setAngle", &Entity::setAngle)
                                              .addMember("getBody", &Entity::getBody)
                                              .addMember("doesCollide", &Entity::doesCollide)
                                              .addMember("setOnUpdateScript", &Entity::setScript<0>)
                                              .addMember("setOnMoveScript", &Entity::setScript<1>)
                                              .addMember("setOnCollisionScript", &Entity::setScript<2>)
                                              .addMember("setOnDeathScript", &Entity::setScript<3>)
                                              .addMember("remove", &Entity::remove)
    );

    this->script.state["EntityMoving"].setClass(kaguya::ClassMetatable<EntityMoving, Entity>()
                                                    .addConstructor<Map *, double, double>()
                                                    .addMember("setBodyType", &EntityMoving::setBodyType)
                                                    .addMember("applyForce", &EntityMoving::applyForce)
                                                    .addMember("applyImpulse", &EntityMoving::applyImpulse)
    );

    this->script.state["EntityPlayer"].setClass(kaguya::ClassMetatable<EntityPlayer, EntityMoving>()
                                                    .addMember("getColorfulness", &EntityPlayer::getColorfulness)
                                                    .addMember("getDamagedToy", &EntityPlayer::getDamagedToy)
                                                    .addMember("getEjectTime", &EntityPlayer::getEjectTime)
                                                    .addMember("getToyToMerge", &EntityPlayer::getToyToMerge)
                                                    .addMember("getTailAnimation", &EntityPlayer::getTailAnimation)
    );

    this->script.state["Map"].setClass(kaguya::ClassMetatable<Map>()
                                           .addMember("getWidth", &Map::getWidth)
                                           .addMember("getHeight", &Map::getHeight)
                                           .addMember("getBlock", &Map::getBlock)
                                           .addMember("getEntities", &Map::getEntities)
                                           .addMember("getEntity", &Map::getEntity<>)
                                           .addMember("getEntityPlayer", &Map::getEntity<EntityPlayer>)
                                           .addMember("getEntityAt", &Map::getEntityAt<Entity>)
                                           .addMember("getWorldTime", &Map::getWorldTime)
    );

    this->script.state["map"] = this->map;
    this->script.state["this"] = this;
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
    file = getFilePath("scripts/levels/" + this->map->getLevelName() + "/" + file + ".lua");
    Script::Handler *handler = nullptr;
    switch (type) {
        case 0:
            handler = &this->script.update;
            break;
        case 1:
            handler = &this->script.move;
            break;
        case 2:
            handler = &this->script.collision;
            break;
        case 3:
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

void Entity::remove() {
    if (this->script.death.loaded) {
        this->script.death.function();
    }
    this->toBeDeleted = true;
}

Entity::~Entity() {
    this->map->getWorld()->DestroyBody(this->body);
}

unsigned int Entity::maxEntityId = 0;

unsigned int Entity::getNextEntityId() {
    Entity::maxEntityId++;
    return Entity::maxEntityId;
};