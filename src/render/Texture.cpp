//
// Created by dar on 11/21/15.
//

#include <memory>
#include <SOIL.h>

#include "Texture.h"
#include "files.h"
#include "render/texture/Resampler.h"

int Texture::m_boundTexId = -1;
int Texture::m_activeTexId = -1;

Texture::Texture() {}

void Texture::createFromData(std::unique_ptr<unsigned char[]> data, size_t width, size_t height, uint8_t channels) {
    m_width = width;
    m_height = height;
    m_channels = channels;

    glGenTextures(1, &m_id);
    bindTexture(0);

    if (m_mipmapEnabled) {
        size_t mipmapLevels = std::log2(std::max(m_width, m_height));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels - 1);

        for (uint8_t level = 0; level < mipmapLevels; ++level) {
            auto resampled = texture::Resampler::downsample(data.get(), width, height, channels, 1 << level);

            GLsizei w = (GLsizei) (m_width / (1 << level));
            GLsizei h = (GLsizei) (m_height / (1 << level));

            for (int i = 0; i < 4 * w * h; i += 4) {
                resampled[i + 0] = (uint8_t) ((resampled[i + 0] * resampled[i + 3] + 128) >> 8);
                resampled[i + 1] = (uint8_t) ((resampled[i + 1] * resampled[i + 3] + 128) >> 8);
                resampled[i + 2] = (uint8_t) ((resampled[i + 2] * resampled[i + 3] + 128) >> 8);
            }

#ifdef DBG_COLORMIPMAPS
            for (int i = 0; i < w * h; ++i) {
                resampled[4*i + 0] = 255 - level * 40;
                resampled[4*i + 1] = level * 40;
                resampled[4*i + 2] = 0;
                resampled[4*i + 3] = 255;
            }
#endif // DBG_COLORMIPMAPS

            glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampled.get());
        }
    }
}

void Texture::loadTexture2D(const std::string &fileName, bool mipmaps) {
    m_path = IO::getFilePath<IO::Data::TEXTURE>(fileName);
    m_mipmapEnabled = mipmaps;

    int width, height, channels;
    auto bytes = std::unique_ptr<unsigned char[]>(SOIL_load_image(m_path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA));

    createFromData(std::move(bytes), (size_t) width, (size_t) height, (uint8_t) channels);
}

void Texture::samplerParameter(GLenum parameter, GLenum value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::filtering(int filterMag, int filterMin) {
    if (filterMag == TEXTURE_FILTER_MAG_NEAREST)
        samplerParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else if (filterMag == TEXTURE_FILTER_MAG_BILINEAR)
        samplerParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (filterMin == TEXTURE_FILTER_MIN_NEAREST)
        samplerParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_BILINEAR)
        samplerParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    else if (filterMin == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
        samplerParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
        samplerParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_TRILINEAR_MIPMAP)
        samplerParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    m_filterMin = filterMin;
    m_filterMag = filterMag;
}

void Texture::bindTexture(int bindId) {
    m_boundId = bindId;
    if (Texture::m_boundTexId != bindId || Texture::m_activeTexId != bindId) {
        glActiveTexture(GL_TEXTURE0 + bindId);
        Texture::m_activeTexId = bindId;
    }
    if (Texture::m_boundTexId != m_id) {
        glBindTexture(GL_TEXTURE_2D, m_id);
        Texture::m_boundTexId = m_id;
    }
}

int Texture::minificationFilter() const {
    return m_filterMin;
}

int Texture::magnificationFilter() const {
    return m_filterMag;
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

int Texture::boundId() const {
    return m_boundId;
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}
