//
// Created by dar on 12/7/15.
//

#ifndef C003_IPOSITIONABLE_H
#define C003_IPOSITIONABLE_H

class IPositionable {

public:
    virtual double getX() const = 0;

    virtual double getY() const = 0;

    virtual double getWidth() const = 0;

    virtual double getHeight() const = 0;
    
    virtual bool doesCollide(IPositionable *obj) = 0;
};

#endif //C003_IPOSITIONABLE_H
