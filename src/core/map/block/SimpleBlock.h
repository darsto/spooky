//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCK_H
#define C003_SIMPLEBLOCK_H
#pragma once

#include "Block.h"

class SimpleBlock : public Block {

public:
    SimpleBlock(Map *map, int texPos, int x, int y) : Block(map, x, y), texPos(texPos) {
        shape.SetAsBox(0.5, 0.5);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.isSensor = texPos >= 13 * 16;
        body->CreateFixture(&fixDef);
    };

    int getTexPos() const {
        return texPos;
    }

    virtual void setX(int x) override {
        Block::setX(x);
        this->markToRedraw();
    }

    virtual void setY(int y) override {
        Block::setY(y);
        this->markToRedraw();
    }

    virtual bool toBeRedrawn() const override {
        return this->redraw;
    }

    virtual void markToRedraw() override {
        this->redraw = true;
    }

    //TODO call this after each render cycle on all the objects
    virtual void setRedrawn() override {
        this->redraw = false;
    }

private:
    int texPos;
    bool redraw = true;
};

#endif //C003_SIMPLEBLOCK_H