/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Rectangle.h"

using namespace util;

Rectangle::Rectangle(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height) {

}

Rectangle::Rectangle(const uint32_t width, const uint32_t height)
    : m_x(0),
      m_y(0),
      m_width(width),
      m_height(height) {

}

uint32_t Rectangle::x() const {
    return m_x;
}

uint32_t Rectangle::y() const {
    return m_y;
}

uint32_t Rectangle::width() const {
    return m_width;
}

uint32_t Rectangle::height() const {
    return m_height;
}

uint32_t Rectangle::field() const {
    return m_width * m_height;
}

bool Rectangle::fits(const Rectangle &other) const {
    return other.m_x >= m_x
           && other.m_y >= m_y
           && other.m_x + other.m_width <= m_x + m_width
           && other.m_y + other.m_height <= m_y + m_height;
}

Rectangle Rectangle::pad(uint32_t padX, uint32_t padY) const {
    if (padX > m_width) padX = m_width;
    if (padY > m_height) padY = m_height;
    return Rectangle(m_x + padX, m_y + padY, m_width - padX, m_height - padY);
}

Rectangle Rectangle::padX(uint32_t padX) const {
    return pad(padX, 0);
}

Rectangle Rectangle::padY(uint32_t padY) const {
    return pad(0, padY);
}

Rectangle Rectangle::offset(uint32_t offX, uint32_t offY) const {
    return Rectangle(m_x + offX, m_y + offY, m_width, m_height);
}

Rectangle Rectangle::offsetX(uint32_t offX) const {
    return offset(offX, 0);
}

Rectangle Rectangle::offsetY(uint32_t offY) const {
    return offset(0, offY);
}

Rectangle Rectangle::position(const Rectangle &other) {
    return offset(other.x(), other.y());
}

Rectangle Rectangle::beginAt(uint32_t x, uint32_t y) {
    return Rectangle(x, y, m_width - x + m_x, m_height - y + m_y);
}

Rectangle Rectangle::beginAt(const Rectangle &other) {
    return beginAt(other.x(), other.y());
}

Rectangle Rectangle::cut(uint32_t width, uint32_t height) const {
    return Rectangle(m_x, m_y, width, height);
}

Rectangle Rectangle::cutX(uint32_t width) const {
    return cut(width, m_height);
}

Rectangle Rectangle::cutY(uint32_t height) const {
    return cut(m_width, height);
}

Rectangle Rectangle::expand(uint32_t x, uint32_t y) const {
    return Rectangle(m_x, m_y, m_width + x, m_height + y);
}

Rectangle Rectangle::expandX(uint32_t x) const {
    return expand(x, 0);
}

Rectangle Rectangle::expandY(uint32_t y) const {
    return expand(0, y);
}

Rectangle Rectangle::scale(double scale) const {
    return Rectangle((uint32_t) (m_x * scale), (uint32_t) (m_y * scale), (uint32_t) (m_width * scale), (uint32_t) (m_height * scale));
}
