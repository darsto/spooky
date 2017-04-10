/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <algorithm>
#include <cmath>

#include "Packer.h"

using namespace util;

Packer::Packer()
    : m_size(0, 0) {
}

void Packer::add(Packer::Element element) {
    if (m_built) {
        throw std::runtime_error("Trying to add an element into an already built packer.");
    }

    m_rectangles.push_back(std::move(element));
}

void Packer::pack() {
    if (m_built) {
        throw std::runtime_error("Trying to pack an already built packer.");
    }

    m_built = true;
    calculateSize();
    growTree();
}

const std::vector<Packer::Element> Packer::elements() const {
    std::vector<Packer::Element> vec;
    buildPackedVec(m_topNode.get(), vec);
    return vec;
}



const Rectangle &Packer::size() const {
    return m_size;
}

const Packer::Node *Packer::nodes() const {
    return m_topNode.get();
}

void Packer::calculateSize() {
    uint32_t field = 0;

    for (auto &t : m_rectangles) {
        field += t.second.field();
    }

    uint32_t edge = (uint32_t) std::ceil(std::sqrt(field));

    m_size = Rectangle(edge, edge);
}

void Packer::growTree() {
    // expecting m_textures.size() > 0
    std::sort(m_rectangles.begin(), m_rectangles.end(), [](const Element &lhs, const Element &rhs) {
        return lhs.second.field() < rhs.second.field();
    });

    while (!m_rectangles.empty()) {
        positionObject(std::move(m_rectangles.back()), m_topNode.get());
        m_rectangles.pop_back();
    }
}

bool Packer::positionObject(Element obj, Packer::Node *node) {
    if (m_topNode.get() == nullptr) { //first node
        m_topNode = std::make_unique<Node>(obj.first, std::move(obj.second), m_size);
        return true;
    } else if (node == nullptr) {
        return false;
    } else {
        bool right = positionObject(std::move(obj), node->right());
        bool down = right || positionObject(std::move(obj), node->down());

        if (right || down) {
            return true;
        } else {
            if (node->right() == nullptr
                && node->rectRight().fits(obj.second.position(node->rectRight()))) {

                node->right(std::make_unique<Node>(obj.first, obj.second.position(node->rectRight()), node->rectRight()));
                return true;
            } else if (node->down() == nullptr
                       && node->rectDown().fits(obj.second.position(node->rectDown()))) {

                node->down(std::make_unique<Node>(obj.first, obj.second.position(node->rectDown()), node->rectDown()));
                return true;
            }
        }
    }
}

void Packer::buildPackedVec(const Packer::Node *node, std::vector<Packer::Element> &vec) const {
    if (node == nullptr) return;
    vec.push_back(Element(node->id(), node->rectangle()));
    buildPackedVec(node->right(), vec);
    buildPackedVec(node->down(), vec);
}

// ===== Node =====

Packer::Node::Node(uint64_t id, Rectangle rect, Rectangle unused)
    : m_id(id),
      m_occupied(std::move(rect)),
      m_rectRight(Rectangle(unused.x() + rect.width(), unused.y(), unused.width() - rect.width(), rect.height())),
      m_rectDown(Rectangle(unused.x(), unused.y() + rect.height(), unused.width(), unused.height() - rect.height())) {
}

const uint64_t Packer::Node::id() const {
    return m_id;
}

const Rectangle &Packer::Node::rectangle() const {
    return m_occupied;
}

const Packer::Node *Packer::Node::right() const {
    return m_right.get();
}

const Packer::Node *Packer::Node::down() const {
    return m_down.get();
}

Packer::Node *Packer::Node::right() {
    return m_right.get();
}

Packer::Node *Packer::Node::down() {
    return m_down.get();
}

const Rectangle &Packer::Node::rectRight() const {
    return m_rectRight;
}

const Rectangle &Packer::Node::rectDown() const {
    return m_rectDown;
}

void Packer::Node::right(std::unique_ptr<Packer::Node> right) {
    m_right = std::move(right);
}

void Packer::Node::down(std::unique_ptr<Packer::Node> down) {
    m_down = std::move(down);
}