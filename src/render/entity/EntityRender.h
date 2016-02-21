//
// Created by dar on 11/28/15.
//

#ifndef C003_RENDERENTITY_H
#define C003_RENDERENTITY_H
#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <core/map/entity/Entity.h>

class EntityRender {
public:
    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) = 0;
};

#endif //C003_RENDERENTITY_H
