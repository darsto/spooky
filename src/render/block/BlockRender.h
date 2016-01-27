//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCKRENDER_H
#define C003_BLOCKRENDER_H
#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "../../core/map/block/Block.h"
#include "../Texture.h"

class BlockRender {
public:
    virtual void render(const Block *const block, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) = 0;
};


#endif //C003_BLOCKRENDER_H
