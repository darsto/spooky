/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_GUI_GUIELEMENT_H
#define C003_GUI_GUIELEMENT_H

#include <string>

/**
 * Position flags for gui elements.
 *
 */
enum class GuiPos : uint8_t {
    LEFT   = 1,      /**< Horizontal position - left side of the screen */
    RIGHT  = 2,      /**< Horizontal position - right side of the screen */
    CENTER = 3,      /**< Horizontal position - center of the screen */
    TOP    = 4,      /**< Vertical position - top side of the screen */
    BOTTOM = 8,      /**< Vertical position - bottom side of the screen */
    MIDDLE = 12,     /**< Vertical position - middle of the screen */
};

class GuiElement {
public:
    GuiElement(const GuiElement *parent, GuiPos pos, double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    GuiElement(GuiPos pos, double x, double y, double width, double height, const std::string &tex, int color = 0xFFFFFFFF);
    bool contains(double coordX, double coordY);
    GuiPos pos() const;
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
    GuiPos m_pos;
    double m_x, m_y;
    double m_width, m_height;
    double m_angle;
    std::string m_tex;
    int m_color;
};

inline constexpr GuiPos operator|(GuiPos a, GuiPos b) {
    return static_cast<GuiPos>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline constexpr GuiPos operator&(GuiPos a, GuiPos b) {
    return static_cast<GuiPos>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

#endif //C003_GUI_GUIELEMENT_H
