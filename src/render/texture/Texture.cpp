/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <type_traits>
#include <SOIL2.h>

#include "Texture.h"
#include "exceptions.h"
#include "util/file.h"

using namespace texture;

int Texture::s_boundTexId = 0;

Texture::Texture()
    : m_minFilter(MinFilter::NEAREST),
      m_magFilter(MagFilter::NEAREST) {

    glGenTextures(1, &m_id);
}

void Texture::loadTex(TexData &tex, uint32_t level) {
    if (level == 0) {
        m_width = tex.width();
        m_height = tex.height();
    }
    
    uint32_t channels = tex.channels();

    if (channels < 1 || channels > 4) {
        char msg[90];
        snprintf(msg, sizeof(msg), "Trying to write to GPU texture with invalid amount of channels (channels:%d).", channels);
        throw invalid_texture_error(msg);
    }

#ifdef DBG_COLORMIPMAPS
    // color mipmaps in scheme: red (biggest) -> yellow (smallest)
        if (channels >= 3) {
            for (int i = 0; i < tex.width() * tex.height(); ++i) {
                resampled[channels * i + 0] = 255 - level * 40;
                resampled[channels * i + 1] = level * 40;
                resampled[channels * i + 2] = 0;
                if (channels >= 4) {
                    resampled[channels * i + 3] = 255;
                }
            }
        }
#endif // DBG_COLORMIPMAPS

    if (channels == 4) {
        // burn alpha into RGB channels
        for (int i = 0; i < tex.width() * tex.height(); ++i) {
            tex[channels * i + 0] = (uint8_t) ((tex[channels * i + 0] * tex[channels * i + 3] + 128) >> 8);
            tex[channels * i + 1] = (uint8_t) ((tex[channels * i + 1] * tex[channels * i + 3] + 128) >> 8);
            tex[channels * i + 2] = (uint8_t) ((tex[channels * i + 2] * tex[channels * i + 3] + 128) >> 8);
        }
    }

    glTexImage2D(GL_TEXTURE_2D, level, getTexGLFormat(channels), tex.width(), tex.height(), 0, getTexGLFormat(channels), GL_UNSIGNED_BYTE, tex.get());
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
            char msg[100];
            snprintf(msg, sizeof(msg), "Trying to convert invalid channel number into an OpenGL texture format (channels:%d).", channels);
            throw invalid_texture_error(msg);
    }

    return ret;
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}
