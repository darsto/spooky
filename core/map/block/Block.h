//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCK_H
#define C003_BLOCK_H

#include <Box2D/Box2D.h>

#define generalScale 1
#define blockSize 50.0f

class Map;

class Block {

public:
    Block(Map *map, int x, int y);

    int getX() const {
        return x;
    }

    void setX(int x);

    int getY() const {
        return y;
    }

    void setY(int y);

    void update() { }

    bool isCollidable() { return true; }; //TODO

    virtual ~Block() { }

protected:
    Map *map;
    int x, y;
    b2BodyDef bodyDef;
    b2Body *body;
    b2PolygonShape shape;

};

#endif //C003_BLOCK_H
