/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_GUI_GUIELEMENT_H
#define C003_GUI_GUIELEMENT_H

#include <string>

class GuiElement {
public:
    GuiElement(const GuiElement *parent, double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    GuiElement(double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    bool contains(double coordX, double coordY);
    virtual double x() const;
    void x(double x);
    virtual double y() const;
    void y(double y);
    double width() const;
    void width(double width);
    double height() const;
    void height(double height);
    double angle() const;
    virtual const std::string &texPos() const;
    int color() const;
    virtual ~GuiElement();

    static constexpr const unsigned int TYPE = 0;

    virtual const unsigned int type() const {
        return TYPE;
    }

protected:
    const GuiElement *const m_parent;
    double m_x, m_y;
    double m_width, m_height;
    double m_angle;
    std::string m_tex;
    int m_color;
};

#endif //C003_GUI_GUIELEMENT_H
