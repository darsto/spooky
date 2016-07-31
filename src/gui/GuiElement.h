//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENT_H
#define C003_GUIELEMENT_H

class GuiElement {
public:
    enum class PositionFlag {
        TOP_LEFT = 0,
        TOP_CENTER = 1,
        TOP_RIGHT = 2,
        MIDDLE_LEFT = 3,
        MIDDLE_CENTER = 4,
        MIDDLE_RIGHT = 5,
        BOTTOM_RIGHT = 6,
        BOTTOM_CENTER = 7,
        BOTTOM_LEFT = 8
    };

    GuiElement(PositionFlag positionFlag, double x, double y, double width, double height, int texturePos, int color = 0xFFFFFFFF);
    bool contains(double x, double y);
    virtual void reinit(unsigned int windowWidth, unsigned int windowHeight);
    PositionFlag positionFlag() const;
    void positionFlag(PositionFlag positionFlag);
    double offsetX() const;
    double x() const;
    void x(double x);
    double offsetY() const;
    double y() const;
    void y(double y);
    double width() const;
    void width(double width);
    double height() const;
    void height(double height);
    bool visible() const;
    void visible(bool visible);
    double angle() const;
    void angle(double angle);
    virtual int texPos() const;
    virtual void texPos(int texturePos);
    int color() const;
    void color(int color);
    virtual ~GuiElement();

    static const unsigned int TYPE = 0;

    virtual const unsigned int type() const {
        return TYPE;
    }

protected:
    PositionFlag m_positionFlag;
    double m_offsetX, m_offsetY;
    double m_x, m_y;
    double m_width, m_height;
    double m_angle;
    bool m_visible = true;
    int m_texturePos;
    int m_color;
};

#endif //C003_GUIELEMENT_H
