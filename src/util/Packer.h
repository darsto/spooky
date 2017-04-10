/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * TODO: implement iterator for the binary tree
 */

#ifndef SPOOKY_UTIL_PACKER_H
#define SPOOKY_UTIL_PACKER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <atomic>

#include "Rectangle.h"

namespace util {

    /**
     * 2D binary packer.
     * Provides generic interface for packing any Rectangle shapes into a square area of dynamic size.
     */
    class Packer {
    protected:
        /**
         * A node representing single element in generated binary tree.
         */
        class Node {
        public:
            /**
             * The constructor.
             * @param id unique id to be associated with this node
             * @param rect area of this node
             * @param unused unused surrounding area of this node (must contain rect). This is used to calculate if other textures can fit next to this one.
             */
            Node(uint64_t id, Rectangle rect, Rectangle unused);

            /**
             * Get the unique id associated with this node
             * @return unique id associated with this node
             */
            uint64_t id() const;

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
            /**
             * Fancy image presenting Node's internals:
             * o--------------o-----------------------o
             * |              |                       |
             * |              |                       |
             * |  m_occupied  |      m_rectRight      |
             * |              |                       |
             * |              |                       |
             * o--------------o-----------------------o
             * |              |                       |
             * |              |                       |
             * |              |                       |
             * |              |                       |
             * |  m_rectDown  |                       |
             * |              |                       |
             * |              |                       |
             * |              |                       |
             * |              |                       |
             * |              |            The canvas |
             * o--------------o-----------------------o
             */

            /**
             * Unique id of the node.
             */
            const uint64_t m_id;

            /**
             * The rectangle occupied by this node.
             */
            const Rectangle m_occupied;

            /**
             * The free space on the right of the rectangle occupied by this node.
             */
            const Rectangle m_rectRight;

            /**
             * The free space on the bottom of the rectangle occupied by this node.
             */
            const Rectangle m_rectDown;

            /**
             * Node on the right
             */
            std::unique_ptr<Node> m_right = nullptr;

            /**
             * Node on the bottom
             */
            std::unique_ptr<Node> m_down = nullptr;
        };

    public:
        /**
         * Basic type of objects leaving scope of this class.
         * Consists of a single Rectangle object and it's corresponding id.
         */
        using Element = std::pair<uint64_t, Rectangle>;

        /**
         * The constructor.
         */
        Packer();

        /**
         * Adds given element to the internal container.
         * @param element element to be packed
         */
        void add(Element element);

        /**
         * Pack all the stored rectangles.
         * Once this method is called, it's no longer possible to add shapes into the same packer.
         */
        void pack();

        /**
         * Get all the stored rectangles
         * @return container of all the stored rectangles
         */
        const std::vector<Element> elements() const;

        /**
         * Get the (possible) size of the area containing packed rectangles.
         * If called before pack() method, it will return an empty rectangle of 0-size.
         * @return (possible) size of the area containing packed rectangles
         */
        const Rectangle &size() const;

    protected:
        /**
         * Get internal binary tree of packed rectangles.
         * @return internal binary tree of packed rectangles
         */
        const Node *nodes() const;

    private:
        /**
         * Calculate the approximate size of the canvas (the one all rectangles are packed into).
         */
        void calculateSize();

        /**
         * Build internal binary tree of packed rectangles.
         */
        void growTree();

        /**
         * Put given Element onto the canvas. (via binary tree)
         * @param obj element to put on the canvas
         * @param node node to try to put the element to
         * @return if element could fit at given position
         */
        bool positionObject(Element obj, Node *node);

        /**
         * Put given binary tree to the given vector.
         * @param node binary tree of packed elements
         * @param vec vector to insert elements into
         */
        void buildPackedVec(const Node *node, std::vector<Element> &vec) const;

        /**
         * Whether or not pack() method has been called already.
         */
        bool m_built = false;

        /**
         * Unpacked elements.
         */
        std::vector<Element> m_rectangles;

        /**
         * The canvas.
         */
        Rectangle m_size;

        /**
         * Binary tree of packed elements
         */
        std::unique_ptr<Node> m_topNode = nullptr;
    };

}

#endif //SPOOKY_UTIL_PACKER_H
