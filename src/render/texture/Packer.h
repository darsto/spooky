/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_PACKER_H
#define C003_PACKER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>

#include "Rectangle.h"

namespace texture {

    /**
     * 2D binary packer.
     * Provides generic interface for packing any Rectangle shapes into a square area of dynamic size.
     */
    class Packer {
    public:
        /**
         * A node representing single element in generated binary tree.
         */
        class Node {
        public:
            /**
             * The constructor.
             * @param rect area of this node
             * @param unused unused surrounding area of this node (must contain rect). This is used to calculate if other textures can fit next to this one.
             */
            Node(Rectangle rect, Rectangle unused);

            /**
             * Get the area of this node.
             * @return area of this node
             */
            const Rectangle &rectangle() const;

            /**
             * Get the right neighbour of this node (nullptr if none).
             * @return right neighbour of this node (nullptr if none)
             */
            const Node *right() const;

            /**
             * Get the bottom neighbour of this node (nullptr if none).
             * @return bottom neighbour of this node (nullptr if none)
             */
            const Node *down() const;

            /**
             * Get the right neighbour of this node (nullptr if none).
             * @return right neighbour of this node (nullptr if none)
             */
            Node *right();

            /**
             * Get the bottom neighbour of this node (nullptr if none).
             * @return bottom neighbour of this node (nullptr if none)
             */
            Node *down();

            /**
             * Set the right neighbour of this node.
             * @param right right neighbour of this node to be set
             */
            void right(std::unique_ptr<Node> right);

            /**
             * Set the bottom neighbour of this node.
             * @param down bottom neighbour of this node to be set
             */
            void down(std::unique_ptr<Node> down);

            /**
             * Get the unused area on the right of this rectangle that can be used to place a neighbour.
             * @return unused area on the right of this rectangle that can be used to place a neighbour
             */
            const Rectangle &rectRight() const;

            /**
             * Get the unused area on the bottom of this rectangle that can be used to place a neighbour.
             * @return unused area on the bottom of this rectangle that can be used to place a neighbour
             */
            const Rectangle &rectDown() const;

        private:
            const Rectangle m_occupied;
            const Rectangle m_rectRight;
            const Rectangle m_rectDown;

            std::unique_ptr<Node> m_right = nullptr;
            std::unique_ptr<Node> m_down = nullptr;
        };

    public:
        /**
         * The constructor.
         */
        Packer();

        /**
         * Adds given rectangle to the internal container.
         * @param rectangle rectangle to be packed
         */
        void add(Rectangle rectangle);

        /**
         * Pack all the stored rectangles and return the generated tree.
         * This method clears the internal rectangles container.
         * @return generated tree containing all the stored rectangles
         */
        const Node *pack();

        /**
         * Get the (possible) size of the area containing packed rectangles.
         * If called before pack() method, it will return an empty rectangle of 0-size.
         * @return (possible) size of the area containing packed rectangles
         */
        const Rectangle &size() const;

    private:
        std::vector<Rectangle> m_rectangles;
        Rectangle m_size;
        std::unique_ptr<Node> m_topNode = nullptr;

        void calculateSize();
        void growTree();
        bool insertTex(Rectangle tex, Node *node);;
    };

}

#endif //C003_PACKER_H
