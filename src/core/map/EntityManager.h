//
// Created by dar on 5/4/16.
//

#ifndef C003_ENTITYMANAGER_H
#define C003_ENTITYMANAGER_H

#include <core/map/entity/Entity.h>

class EntityManager {

public:
    EntityManager(LevelContext &levelContext);
    std::string saveEntity(const Entity *const e) const;
    Entity *loadEntity(const std::string &data) const;
    void registerEntityTypes(kaguya::State &state);
private:
    LevelContext &levelContext;
};

#endif //C003_ENTITYMANAGER_H
