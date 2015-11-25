//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCKRENDER_H
#define C003_BLOCKRENDER_H


#include <glm/detail/type_mat.hpp>
#include "../../core/block/Block.h"

class BlockRender {
public:
    virtual void render(const Block *const block, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) = 0;
};


#endif //C003_BLOCKRENDER_H
