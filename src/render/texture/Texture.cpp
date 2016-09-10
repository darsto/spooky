/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <type_traits>
#include <SOIL.h>

#include "Texture.h"
#include "TexData.h"
#include "util/file.h"

using namespace texture;

int Texture::s_boundTexId = 0;

Texture::Texture(const std::string &filename)
    : m_path(filename),
      m_minFilter(MinFilter::NEAREST),
      m_magFilter(MagFilter::NEAREST) {

}

void Texture::load() {
    TexData data(m_path);
    m_id = SOIL_create_OGL_texture(data.get(), m_width, m_height, m_channels, 0, SOIL_FLAG_MULTIPLY_ALPHA);
    //TODO validate dimensions
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::samplerParameter(GLenum parameter, GLint value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::filtering(MagFilter filterMag, MinFilter filterMin) {
    samplerParameter(GL_TEXTURE_MAG_FILTER, static_cast<std::underlying_type_t<MagFilter>>(filterMag));
    samplerParameter(GL_TEXTURE_MIN_FILTER, static_cast<std::underlying_type_t<MinFilter>>(filterMin));

    m_minFilter = filterMin;
    m_magFilter = filterMag;
}

void Texture::bindTexture() {
    if (Texture::s_boundTexId != m_id) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id);
        Texture::s_boundTexId = m_id;
    }
}

Texture::MinFilter Texture::minFilter() const {
    return m_minFilter;
}

Texture::MagFilter Texture::magFilter() const {
    return m_magFilter;
}

int Texture::width() const {
    return m_width;
}

int Texture::height() const {
    return m_height;
}

int Texture::channels() const {
    return m_channels;
}

int Texture::activeTex() const {
    return 0; // TODO currently unused, we always set GL_TEXTURE0 as active texture
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}
