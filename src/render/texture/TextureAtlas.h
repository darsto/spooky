/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_TEXTUREATLAS_H
#define C003_TEXTUREATLAS_H

#include "Texture.h"
#include "files.h"

namespace texture {

    class TextureAtlas {
    public:
        TextureAtlas(const std::string &name);
        ~TextureAtlas();
        uint32_t id() const;
        void bind();

    private:
        class impl;

        uint32_t m_id;
        std::vector<std::string> m_tiles;
        std::unique_ptr<TextureAtlas::impl> m_impl;

        static uint32_t s_boundId;
    };
}

#endif //C003_TEXTUREATLAS_H
