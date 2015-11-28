//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCK_H
#define C003_BLOCK_H

#define generalScale 1
#define blockSize 50.0f

class Block {

public:
    Block(int x, int y) {
        this->x = x;
        this->y = y;
    };

    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    void update() { }

    virtual ~Block() {}

private:
    int x, y;
};


#endif //C003_BLOCK_H
