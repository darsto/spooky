/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Packer.h"

using namespace texture;

Packer::Packer()
    : m_size(0, 0) {
}

void Packer::add(Rectangle rectangle) {
    m_rectangles.push_back(std::move(rectangle));
}

const Packer::Node *Packer::pack() {
    calculateSize();
    growTree();
    return m_topNode.get();
}

const Rectangle &Packer::size() const {
    return m_size;
}

void Packer::calculateSize() {
    uint32_t field = 0;

    for (const Rectangle &t : m_rectangles) {
        field += t.field();
    }

    uint32_t edge = (uint32_t) std::ceil(std::sqrt(field));

    m_size = Rectangle(0, 0, edge, edge);
}

void Packer::growTree() {
    // expecting m_textures.size() > 0
    std::sort(m_rectangles.begin(), m_rectangles.end());

    while (!m_rectangles.empty()) {
        insertTex(std::move(m_rectangles.back()), m_topNode.get());
        m_rectangles.pop_back();
    }
}

bool Packer::insertTex(Rectangle tex, Packer::Node *node) {
    if (m_topNode.get() == nullptr) { //first node
        m_topNode = std::make_unique<Node>(tex, m_size);
        return true;
    } else if (node == nullptr) {
        return false;
    } else {
        bool right = insertTex(std::move(tex), node->right());
        bool down = right || insertTex(std::move(tex), node->down());

        if (right || down) {
            return true;
        } else {
            if (node->right() == nullptr
                && node->rectRight().fits(tex.position(node->rectRight()))) {

                node->right(std::make_unique<Node>(tex.position(node->rectRight()), node->rectRight()));
                return true;
            } else if (node->down() == nullptr
                       && node->rectDown().fits(tex.position(node->rectDown()))) {

                node->down(std::make_unique<Node>(tex.position(node->rectDown()), node->rectDown()));
                return true;
            }
        }
    }
}

// ===== Node =====

Packer::Node::Node(Rectangle rect, Rectangle unused)
    : m_occupied(std::move(rect)),
      m_rectRight(Rectangle(unused.x() + rect.width(), unused.y(), unused.width() - rect.width(), rect.height())),
      m_rectDown(Rectangle(unused.x(), unused.y() + rect.height(), unused.width(), unused.height() - rect.height())) {
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