//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITY_H
#define C003_ENTITY_H

class Map;

class Entity {
public:
    Entity(Map *map, double width, double height) : map(map) { }

    double getX() const {
        return x;
    }

    void setX(double x) {
        Entity::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Entity::y = y;
    }

    virtual void update() { }

    virtual ~Entity() { }

protected:
    Map *map;
    double x = 0, y = 0;
};

#endif //C003_ENTITY_H
