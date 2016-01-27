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
#include <gui/GuiElement.h>
#include <gui/GuiButton.h>
#include "../core/entity/EntityToy.h"
#include "../core/entity/EntityPlayer.h"
#include "../render/entity/PlayerRender.h"
#include "../render/entity/SimpleShapeRender.h"
#include "../core/map/block/SimpleBlock.h"
#include "block/BlockRender.h"
#include "block/SimpleBlockRender.h"
#include "entity/EntityRender.h"
#include "entity/DefaultEntityRender.h"
#include "../core/entity/EntityBullet.h"
#include "../core/entity/SimpleShape.h"
#include "gui/GuiElementRender.h"

static std::map<const char *, BlockRender *> blockRenders;
static std::map<const char *, EntityRender *> entityRenders;
static std::map<const char *, GuiElementRender *> guiRenders;

inline BlockRender *getBlockRender(const Block *const block) {
    return blockRenders[typeid(*block).name()];
}

inline EntityRender *getEntityRender(const Entity *const entity) {
    return entityRenders[typeid(*entity).name()];
}

inline GuiElementRender *getGuiElementRender(const GuiElement *const element) {
    GuiElementRender *render = guiRenders[typeid(*element).name()];
    if (render == nullptr) render = guiRenders[typeid(GuiElement).name()];
    return render;
}

inline void initRenderers() {
    blockRenders.insert(std::make_pair(typeid(SimpleBlock).name(), new SimpleBlockRender()));
    entityRenders.insert(std::make_pair(typeid(Player).name(), new PlayerRender()));
    entityRenders.insert(std::make_pair(typeid(EntityToy).name(), new DefaultEntityRender("ghost", "shader")));
    entityRenders.insert(std::make_pair(typeid(EntityBullet).name(), new DefaultEntityRender("bullet", "shader")));
    entityRenders.insert(std::make_pair(typeid(SimpleShape).name(), new SimpleShapeRender()));
    guiRenders.insert(std::make_pair(typeid(GuiElement).name(), new GuiElementRender("gui", "shader")));
}

#endif //C003_RENDER_H
