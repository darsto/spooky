/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_UTIL_PACKER_H
#define C003_UTIL_PACKER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>
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
            const uint64_t id() const;

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
            const uint64_t m_id;
            const Rectangle m_occupied;
            const Rectangle m_rectRight;
            const Rectangle m_rectDown;

            std::unique_ptr<Node> m_right = nullptr;
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
         * Adds given rectangle to the internal container.
         * @param rectangle rectangle to be packed
         * @return unique id assigned to just-created internal node
         */
        uint64_t add(Rectangle rectangle);

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
        const Node *nodes() const;

    private:
        void calculateSize();
        void growTree();
        bool positionObject(std::pair<uint64_t, Rectangle> obj, Node *node);
        void buildPackedVec(const Node *node, std::vector<Element> &vec) const;

        bool m_built = false;
        std::vector<std::pair<uint64_t, Rectangle>> m_rectangles;
        Rectangle m_size;
        std::unique_ptr<Node> m_topNode = nullptr;

        static std::atomic<uint64_t> s_idCounter;
    };

}

#endif //C003_UTIL_PACKER_H
