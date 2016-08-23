//
// Created by dar on 2/22/16.
//

#include "GuiElement.h"
#include <core/input/TouchPoint.h>

GuiElement::GuiElement(PositionFlag positionFlag, double x, double y, double width, double height, const std::string &tex, int color)
    : m_positionFlag(positionFlag),
      m_offsetX(x),
      m_offsetY(y),
      m_width(width),
      m_height(height),
      m_tex(tex),
      m_color(color),
      m_angle(0) {

}

GuiElement::GuiElement(int positionFlag, double x, double y, double width, double height, const std::string &tex, int color)
    : GuiElement(static_cast<PositionFlag>(positionFlag), x, y, width, height, tex, color) {

}

void GuiElement::reinit(unsigned int windowWidth, unsigned int windowHeight) {
    double px = m_offsetX;
    double py = m_offsetY;
    switch (m_positionFlag) {
        default:
        case PositionFlag::TOP_LEFT:
            break;
        case PositionFlag::TOP_CENTER:
            px += -m_width / 2 + windowWidth / 2;
            break;
        case PositionFlag::TOP_RIGHT:
            px = windowWidth - px - m_width;
            break;
        case PositionFlag::MIDDLE_LEFT:
            py += -m_height / 2 + windowHeight / 2;
            break;
        case PositionFlag::MIDDLE_CENTER:
            px += -m_width / 2 + windowWidth / 2;
            py += -m_height / 2 + windowHeight / 2;
            break;
        case PositionFlag::MIDDLE_RIGHT:
            px = windowWidth - px - m_width;
            py += -m_height / 2 + windowHeight / 2;
            break;
        case PositionFlag::BOTTOM_LEFT:
            py = windowHeight - py - m_height;
            break;
        case PositionFlag::BOTTOM_CENTER:
            px += -m_width / 2 + windowWidth / 2;
            py = windowHeight - py - m_height;
            break;
        case PositionFlag::BOTTOM_RIGHT:
            px = windowWidth - px - m_width;
            py = windowHeight - py - m_height;
            break;
    }
    m_x = px;
    m_y = py;
}

bool GuiElement::contains(double x, double y) {
    return x >= m_x && y >= m_y && x <= m_x + m_width && y < m_y + m_height;
}

GuiElement::PositionFlag GuiElement::positionFlag() const {
    return m_positionFlag;
}

void GuiElement::positionFlag(PositionFlag positionFlag) {
    GuiElement::m_positionFlag = positionFlag;
}

double GuiElement::offsetX() const {
    return m_offsetX;
}

double GuiElement::x() const {
    return m_x;
}

void GuiElement::x(double x) {
    m_x = m_offsetX = x;
}

double GuiElement::offsetY() const {
    return m_offsetY;
}

double GuiElement::y() const {
    return m_y;
}

void GuiElement::y(double y) {
    m_y = m_offsetY = y;
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

bool GuiElement::visible() const {
    return m_visible;
}

void GuiElement::visible(bool visible) {
    GuiElement::m_visible = visible;
}

double GuiElement::angle() const {
    return m_angle;
}

void GuiElement::angle(double angle) {
    m_angle = angle;
}

const std::string & GuiElement::texPos() const {
    return m_tex;
}

void GuiElement::texPos(int texturePos) {
    m_tex = texturePos;
}

int GuiElement::color() const {
    return m_color;
}

void GuiElement::color(int color) {
    m_color = color;
}

GuiElement::~GuiElement() {}