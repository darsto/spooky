//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENT_H
#define C003_GUIELEMENT_H

class GuiElement {
public:
    int getX() const {
        return x;
    }

    void setX(int x) {
        GuiElement::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        GuiElement::y = y;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        GuiElement::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        GuiElement::height = height;
    }

protected:
    int x, y;
    int width, height;
};

#endif //C003_GUIELEMENT_H
