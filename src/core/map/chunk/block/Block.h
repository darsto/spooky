//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCK_H
#define C003_BLOCK_H
#pragma once

#include "core/IPositionable.h"

class Map;

class Block : public IPositionable {

public:
    Block(Map *map, int x, int y);

    virtual double getX() const;

    virtual void setX(int x);

    virtual double getY() const override {
        return y;
    }

    virtual void setY(int y);

    virtual bool doesCollide(IPositionable *obj);;

    virtual double getWidth() const override {
        return 1;
    }

    virtual double getHeight() const override {
        return 1;
    }

    virtual ~Block() { }

protected:
    Map *map;
    int x, y;
};

#endif //C003_BLOCK_H
