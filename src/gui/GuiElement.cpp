/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "GuiElement.h"
#include "EmptyGuiElement.h"
#include <core/input/TouchPoint.h>

constexpr const unsigned int GuiElement::TYPE;

GuiElement::GuiElement(const GuiElement *parent, GuiPos pos, double x, double y, double width, double height, const std::string &tex, int color)
    : m_parent(parent),
      m_pos(pos),
      m_x(x),
      m_y(y),
      m_width(width),
      m_height(height),
      m_tex(tex),
      m_color(color),
      m_angle(0) {

}

GuiElement::GuiElement(GuiPos pos, double x, double y, double width, double height, const std::string &tex, int color)
    : GuiElement(&EmptyGuiElement::instance(), pos, x, y, width, height, tex, color) {

}

bool GuiElement::contains(double coordX, double coordY) {
    return coordX >= x() && coordY >= y() && coordX <= x() + width() && coordY < y() + height();
}

GuiPos GuiElement::pos() const {
    return m_pos;
}

double GuiElement::x() const {
    return m_parent->x() + m_x;
}

void GuiElement::x(double x) {
    m_x = x;
}

double GuiElement::y() const {
    return m_parent->y() + m_y;
}

void GuiElement::y(double y) {
    m_y = y;
}

double GuiElement::width() const {
    return m_width;
}

void GuiElement::width(double width) {
    GuiElement::m_width = width;
}

double GuiElement::height() const {
    return m_height;
}

void GuiElement::height(double height) {
    GuiElement::m_height = height;
}

double GuiElement::angle() const {
    return m_angle;
}

const std::string & GuiElement::texPos() const {
    return m_tex;
}

int GuiElement::color() const {
    return m_color;
}

GuiElement::~GuiElement() {}