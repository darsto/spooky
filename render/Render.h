//
// Created by dar on 11/25/15.
//

#ifndef C003_RENDER_H
#define C003_RENDER_H
#pragma once

#include <typeinfo>
#include <map>
#include <string>
#include <memory>
#include "../core/map/block/SimpleBlock.h"
#include "block/BlockRender.h"
#include "block/SimpleBlockRender.h"
#include "entity/EntityRender.h"
#include "../core/entity/Player.h"
#include "entity/PlayerRender.h"
#include "../core/entity/EntityBullet.h"

static std::map<const char *, BlockRender *> blockRenders;
static std::map<const char *, EntityRender *> entityRenders;

inline BlockRender *getBlockRender(const Block *const block) {
    return blockRenders[typeid(*block).name()];
}

inline EntityRender *getEntityRender(const Entity *const entity) {
    return entityRenders[typeid(*entity).name()];
}

inline void initRenderers() {
    blockRenders.insert(std::make_pair(typeid(SimpleBlock).name(), new SimpleBlockRender()));
    entityRenders.insert(std::make_pair(typeid(Player).name(), new PlayerRender()));
    entityRenders.insert(std::make_pair(typeid(EntityBullet).name(), new PlayerRender()));
}

#endif //C003_RENDER_H
