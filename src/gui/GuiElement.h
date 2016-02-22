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
    GuiElement(char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum);

    GuiElement(char positionFlag, double x, double y, double width, double height, int texturePos) : GuiElement(positionFlag, x, y, width, height, new int[1]{texturePos}, 1) { };

    char getPositionFlag() const {
        return positionFlag;
    }

    void setPositionFlag(char positionFlag) {
        GuiElement::positionFlag = positionFlag;
    }

    double getRawX() const {
        return rawX;
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        this->x = this->rawX = x;
    }

    double getRawY() const {
        return rawY;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        this->y = this->rawY = y;
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

    virtual void reinit(unsigned int windowWidth, unsigned int windowHeight) {
        double px = rawX;
        double py = rawY;
        switch (this->positionFlag) {
            default:
            case GUI_TOP_LEFT:
                break;
            case GUI_TOP_CENTER:
                px += -this->width / 2 + windowWidth / 2;
                break;
            case GUI_TOP_RIGHT:
                px = windowWidth - px - this->width;
                break;
            case GUI_MIDDLE_LEFT:
                py += -this->height / 2 + windowHeight / 2;
                break;
            case GUI_MIDDLE_CENTER:
                px += -this->width / 2 + windowWidth / 2;
                py += -this->height / 2 + windowHeight / 2;
                break;
            case GUI_MIDDLE_RIGHT:
                px = windowWidth - px - this->width;
                py += -this->height / 2 + windowHeight / 2;
                break;
            case GUI_BOTTOM_LEFT:
                py = windowHeight - py - this->height;
                break;
            case GUI_BOTTOM_CENTER:
                px += -this->width / 2 + windowWidth / 2;
                py = windowHeight - py - this->height;
                break;
            case GUI_BOTTOM_RIGHT:
                px = windowWidth - px - this->width;
                py = windowHeight - py - this->height;
                break;
        }
        this->x = px;
        this->y = py;
    }

    virtual int getTexPos(int i) const {
        if (i < 0 || i >= this->texturesNum) return -1;
        return this->texturePos[i];
    }

    virtual void setTexPos(int i, int texturePos) {
        this->texturePos[i] = texturePos;
    }

    virtual ~GuiElement() { };

protected:
    char positionFlag;
    double rawX, rawY;
    double x, y;
    double width, height;
    bool visible = true;
    int texturesNum;
    int *texturePos;
};

#endif //C003_GUIELEMENT_H
