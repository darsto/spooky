/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <type_traits>

#include "Texture.h"
#include "util/file.h"
#include "util/log.h"

using namespace texture;

int Texture::s_boundTexId = 0;

static bool validateChannelNum(uint32_t channels) {
    return channels > 0 && channels < 5;
}

Texture::Texture()
    : m_minFilter(MinFilter::NEAREST),
      m_magFilter(MagFilter::NEAREST) {

    glGenTextures(1, &m_id);
}

int Texture::loadTex(TexData &tex, uint32_t level) {
    if (level == 0) {
        m_width = tex.width();
        m_height = tex.height();
        m_channels = tex.channels();
    }
    
    uint32_t channels = tex.channels();
    if (!validateChannelNum(channels)) {
        Log::error("Trying to write to GPU a texture with invalid amount of channels (%d).", channels);
        return -1;
    }

    glTexImage2D((GLenum) GL_TEXTURE_2D, (GLint) level, (GLint) getTexGLFormat(channels), (GLint) tex.width(), (GLint) tex.height(), 0, (GLenum) getTexGLFormat(channels), (GLenum) GL_UNSIGNED_BYTE, tex.get());
    return 0;
}

void Texture::samplerParameter(GLenum parameter, GLint value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::filtering(MagFilter filterMag, MinFilter filterMin) {
    samplerParameter(GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filterMag));
    samplerParameter(GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filterMin));

    m_minFilter = filterMin;
    m_magFilter = filterMag;
}

void Texture::bindTexture() {
    if (Texture::s_boundTexId != (int) m_id) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id);
        Texture::s_boundTexId = (int) m_id;
    }
}

Texture::MinFilter Texture::minFilter() const {
    return m_minFilter;
}

Texture::MagFilter Texture::magFilter() const {
    return m_magFilter;
}

int Texture::width() const {
    return (int) m_width;
}

int Texture::height() const {
    return (int) m_height;
}

int Texture::channels() const {
    return (int) m_channels;
}

int Texture::activeTex() const {
    return 0; // TODO currently unused, we always set GL_TEXTURE0 as active texture
}

GLenum Texture::getTexGLFormat(uint32_t channels) {
    GLenum ret;

    switch (channels) {
        case 1:
            ret = GL_LUMINANCE; /**< If L was converted into RGBA, it would be R=L, G=L, B=L, A=1 */
            break;
        case 2:
            ret = GL_LUMINANCE_ALPHA; /**< If LA' was converted into RGBA, it would be R=L, G=L, B=L, A=A' */
            break;
        case 3:
            ret = GL_RGB; /**< A=1 */
            break;
        case 4:
            ret = GL_RGBA;
            break;
        default:
            ret = GL_INVALID_ENUM;
            break;
    }

    return ret;
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}
