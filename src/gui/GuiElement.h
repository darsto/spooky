//
// Created by dar on 1/27/16.
//

#ifndef C003_GUIELEMENT_H
#define C003_GUIELEMENT_H

#include <string>

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

    GuiElement(PositionFlag positionFlag, double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    GuiElement(int positionFlag, double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    bool contains(double x, double y);
    virtual void reinit(unsigned int windowWidth, unsigned int windowHeight);
    double x() const;
    void x(double x);
    double y() const;
    void y(double y);
    double width() const;
    void width(double width);
    double height() const;
    void height(double height);
    double angle() const;
    virtual const std::string & texPos() const;
    int color() const;
    virtual ~GuiElement();

    static constexpr const unsigned int TYPE = 0;

    virtual const unsigned int type() const {
        return TYPE;
    }

protected:
    PositionFlag m_positionFlag;
    double m_offsetX, m_offsetY;
    double m_x, m_y;
    double m_width, m_height;
    double m_angle;
    std::string m_tex;
    int m_color;
};

#endif //C003_GUIELEMENT_H
