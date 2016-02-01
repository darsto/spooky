//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENT_H
#define C003_GUIELEMENT_H

#define GUI_TOP_LEFT 0
#define GUI_TOP_CENTER 1
#define GUI_TOP_RIGHT 2
#define GUI_MIDDLE_LEFT 3
#define GUI_MIDDLE_CENTER 4
#define GUI_MIDDLE_RIGHT 5
#define GUI_BOTTOM_RIGHT 6
#define GUI_BOTTOM_CENTER 7
#define GUI_BOTTOM_LEFT 8

class GuiElement {
public:
    char getPositionFlag() const {
        return positionFlag;
    }

    void setPositionFlag(char positionFlag) {
        GuiElement::positionFlag = positionFlag;
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        GuiElement::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        GuiElement::y = y;
    }

    double getWidth() const {
        return width;
    }

    void setWidth(double width) {
        GuiElement::width = width;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double height) {
        GuiElement::height = height;
    }

    bool isVisible() const {
        return this->visible;
    }

    void setVisible(bool visible) {
        GuiElement::visible = visible;
    }

    virtual int getTexPos() const = 0;

    virtual void setTexPos(int texturePos) = 0;

    virtual ~GuiElement() { };

protected:
    char positionFlag;
    double x, y;
    double width, height;
    bool visible = true;
};

#endif //C003_GUIELEMENT_H
