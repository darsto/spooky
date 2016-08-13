/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/*
 * TODO: refactor this class using c++ operators (?)
 */

#ifndef C003_RECTANGLE_H
#define C003_RECTANGLE_H

#include <cstdint>

namespace texture {

    /**
     * Rectangle class providing various transform operations.
     */
    class Rectangle {
    public:
        /**
         * Full constructor, specifies all variables.
         * @param x starting position X coordinate
         * @param y starting position Y coordinate
         * @param width width of the rectangle
         * @param height height of the rectangle
         */
        Rectangle(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);

        /**
         * Partial constructor, initializes starting point as (0, 0).
         * @param width width of the rectangle
         * @param height height of the rectangle
         */
        Rectangle(const uint32_t width, const uint32_t height);

        /**
         * Get X coordinate of the starting point.
         * @return x coord of the starting point
         */
        const uint32_t x() const;

        /**
         * Get Y coordinate of the starting point.
         * @return y coord of the starting point
         */
        const uint32_t y() const;

        /**
         * Get width of the rectangle.
         * @return width of the rectangle
         */
        const uint32_t width() const;

        /**
         * Get height of the rectangle.
         * @return height of the rectangle
         */
        const uint32_t height() const;

        /**
         * Get field of this rectangle.
         * This is equivalent to width() * height()
         * @return field of this rectangle
         */
        const uint32_t field() const;

        /**
         * Check if given rectangle is fully contained inside current one.
         * @param other rectangle to be contained
         * @return if given rectangle is fully contained inside current one
         */
        bool fits(const Rectangle &other) const;

        /**
         * Add offset to the starting point.
         * This modifies both the starting point, and the rectangle's dimensions.
         * The end point is untouched.
         * @param padX units to move starting point's x coordinate by
         * @param padY units to move starting point's y coordinate by
         * @return new Rectangle with applied changes
         */
        Rectangle pad(uint32_t padX, uint32_t padY) const;

        /**
         * Add offset to the starting point.
         * This modifies both the starting point, and the rectangle's dimensions.
         * The end point is untouched.
         * @param padX units to move starting point's x coordinate by
         * @return new Rectangle with applied changes
         */
        Rectangle padX(uint32_t padX) const;

        /**
         * Add offset to the starting point.
         * This modifies both the starting point, and the rectangle's dimensions.
         * The end point is untouched.
         * @param padY units to move starting point's y coordinate by
         * @return new Rectangle with applied changes
         */
        Rectangle padY(uint32_t padY) const;

        /**
         * Move the whole rectangle by given offset.
         * This modifies the starting point, but not the rectangle's dimensions.
         * @param offX x compoment of the offset to move this rectangle by
         * @param offY y compoment of the offset to move this rectangle by
         * @return new Rectangle with applied changes
         */
        Rectangle offset(uint32_t offX, uint32_t offY) const;

        /**
         * Move the whole rectangle by given offset.
         * This modifies the starting point, but not the rectangle's dimensions.
         * @param offX x compoment of the offset to move this rectangle by
         * @return new Rectangle with applied changes
         */
        Rectangle offsetX(uint32_t offX) const;

        /**
         * Move the whole rectangle by given offset.
         * This modifies the starting point, but not the rectangle's dimensions.
         * @param offY y compoment of the offset to move this rectangle by
         * @return new Rectangle with applied changes
         */
        Rectangle offsetY(uint32_t offY) const;

        /**
         * Position the rectangle so that it's starting point is the same as given one's.
         * This modifies the starting point, but not the rectangle's dimensions.
         * @param other rectangle to be positioned to
         * @return new Rectangle with applied changes
         */
        Rectangle position(const Rectangle &other);

        /**
         * Move the starting point to given coordinates.
         * This modifies both the starting point, and the rectangle's dimensions.
         * @param x x component of the new starting point
         * @param y y component of the new starting point
         * @return new Rectangle with applied changes
         */
        Rectangle beginAt(uint32_t x, uint32_t y);

        /**
         * Move the starting point so that it's the same as the one of the given rectangle.
         * This modifies both the starting point, and the rectangle's dimensions.
         * @param x x component of the new starting point
         * @param y y component of the new starting point
         * @return new Rectangle with applied changes
         */
        Rectangle beginAt(const Rectangle &other);

        /**
         * Set given width & height
         * This modifies the rectangle's dimensions, but not the starting point.
         * @param width new width of the rectangle
         * @param height new height of the rectangle
         * @return new Rectangle with applied changes
         */
        Rectangle cut(uint32_t width, uint32_t height) const;

        /**
         * Set given width
         * This modifies the rectangle's dimensions, but not the starting point.
         * @param width new width of the rectangle
         * @return new Rectangle with applied changes
         */
        Rectangle cutX(uint32_t width) const;

        /**
         * Set given height
         * This modifies the rectangle's dimensions, but not the starting point.
         * @param height new height of the rectangle
         * @return new Rectangle with applied changes
         */
        Rectangle cutY(uint32_t height) const;

        /**
         * Increase rectangle's dimensions.
         * This method does not modify the starting point.
         * @param x extra width to be added
         * @param y extra height to be added
         * @return new Rectangle with applied changes
         */
        Rectangle expand(uint32_t x, uint32_t y) const;

        /**
         * Increase rectangle's dimensions.
         * This method does not modify the starting point.
         * @param x extra width to be added
         * @return new Rectangle with applied changes
         */
        Rectangle expandX(uint32_t x) const;

        /**
         * Increase rectangle's dimensions.
         * This method does not modify the starting point.
         * @param y extra height to be added
         * @return new Rectangle with applied changes
         */
        Rectangle expandY(uint32_t y) const;

        /**
         * Scales both the coordinates and size of the rectangle
         * @param scale modifier to scale by; newVal = oldVal * scale
         * @return new Rectangle with applied changes
         */
        Rectangle scale(double scale) const;

    private:
        uint32_t m_x, m_y;
        uint32_t m_width, m_height;
    };
}

#endif //C003_RECTANGLE_H
