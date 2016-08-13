/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * NOTE: This class requires heavy exception handling.
 * If something goes wrong it would be a real hell to debug
 */

#include <memory>
#include <SOIL.h>

#include "Texture.h"
#include "files.h"
#include "render/texture/Resampler.h"
#include "util.h"

const std::regex Texture::FILE_EXTENSION_REGEX = std::regex("(.*)(\\.(jpg|png|gif))", std::regex::ECMAScript | std::regex::icase);
int Texture::m_boundTexId = 0;

Texture::Texture(const std::string &fileName)
    : m_path(files::getFilePath<files::Data::TEXTURE>(fileName)),
      m_tiles(util::filter(files::listdir(files::getFilePath<files::Data::TEXTURE>(fileName).c_str()), FILE_EXTENSION_REGEX)) {

    for (const std::string &tile : m_tiles) {
        loadTile(tile);
    }

    packer.pack();

    glGenTextures(1, &m_id);
    bindTexture();

    uint32_t mipmapLevels = (uint32_t) std::log2(std::max(width(), height()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels - 1);

    for (uint8_t level = 0; level < mipmapLevels; ++level) {
        uint32_t downsample = 1 << level;
        std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(packer.size().field() / downsample / downsample * channels());

        for (auto &el : packer.elements()) {
            TexData &tex = m_texData.find(el.first)->second;
            auto resampled = util::Resampler::downsample(tex.getData().get(), tex.width(), tex.height(), tex.channels(), downsample);
            util::Rectangle rect(el.second.x() / downsample, el.second.y() / downsample, el.second.width() / downsample, el.second.height() / downsample);

            uint32_t inWidth = tex.width() / downsample;
            uint32_t inHeight = tex.height() / downsample;
            uint32_t outWidth = packer.size().width() / downsample;

            for (int yIn = 0; yIn < inHeight; ++yIn) {
                for (int xIn = 0; xIn < inWidth; ++xIn) {
                    uint32_t inPixelPos = xIn + yIn * inWidth;
                    uint32_t outPixelPos = rect.x() + xIn + (rect.y() + yIn) * outWidth;
                    for (int channel = 0; channel < channels(); ++channel) {
                        data[4 * outPixelPos + channel] = resampled[channels() * inPixelPos + channel];
                    }
                }
            }
        }
        writeTexToGPU(std::move(data), level);
    }
}

void Texture::writeTexToGPU(std::unique_ptr<uint8_t[]> data, uint32_t level) {
    GLsizei w = (GLsizei) (width() / (1 << level));
    GLsizei h = (GLsizei) (height() / (1 << level));

    if (channels() == 4) {
        // burn alpha into RGB channels
        for (int i = 0; i < w * h; ++i) {
            data[channels() * i + 0] = (uint8_t) ((data[channels() * i + 0] * data[channels() * i + 3] + 128) >> 8);
            data[channels() * i + 1] = (uint8_t) ((data[channels() * i + 1] * data[channels() * i + 3] + 128) >> 8);
            data[channels() * i + 2] = (uint8_t) ((data[channels() * i + 2] * data[channels() * i + 3] + 128) >> 8);
        }
    }

#ifdef DBG_COLORMIPMAPS
    // color mipmaps in scheme: red (biggest) -> yellow (smallest)
    if (channels >= 3) {
        for (int i = 0; i < w * h; ++i) {
            resampled[channels()*i + 0] = 255 - level * 40;
            resampled[channels()*i + 1] = level * 40;
            resampled[channels()*i + 2] = 0;
            if (channels == 4) {
                resampled[channels()*i + 3] = 255;
            }
        }
    }
#endif // DBG_COLORMIPMAPS

    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
}

void Texture::samplerParameter(GLenum parameter, GLenum value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::filtering(MagFilter filterMag, MinFilter filterMin) {
    samplerParameter(GL_TEXTURE_MAG_FILTER, static_cast<std::underlying_type_t<MagFilter>>(filterMag));
    samplerParameter(GL_TEXTURE_MIN_FILTER, static_cast<std::underlying_type_t<MinFilter>>(filterMin));

    m_filterMin = filterMin;
    m_filterMag = filterMag;
}

void Texture::bindTexture() {
    if (Texture::m_boundTexId != m_id) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id);
        Texture::m_boundTexId = m_id;
    }
}

Texture::MinFilter Texture::minificationFilter() const {
    return m_filterMin;
}

Texture::MagFilter Texture::magnificationFilter() const {
    return m_filterMag;
}

int Texture::width() const {
    return packer.size().width();
}

int Texture::height() const {
    return packer.size().height();
}

int Texture::channels() const {
    return 4;
}

int Texture::boundId() const {
    return 0; // TODO currently unused, we always set GL_TEXTURE0 as active texture
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

void Texture::loadTile(const std::string &path) {
    int32_t width, height, channels;
    auto bytes = std::unique_ptr<uint8_t[]>(SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO));

    if (width > 0 && height > 0 && channels > 0) {
        uint64_t id = packer.add(util::Rectangle((uint32_t) width, (const uint32_t) height));
        TexData tex((uint32_t) width, (uint32_t) height, (uint32_t) channels, std::move(bytes));
        m_texData.emplace(id, std::move(tex));
    } else {
        char msg[90];
        snprintf(msg, sizeof(msg), "Trying to load invalid texture (width:%d, height:%d, channels:%d).", width, height, channels);
        throw invalid_texture_error(msg);
    }
}

const uint64_t Texture::getElementsNum() const {
    return m_texData.size();
}

TexData::TexData(uint32_t width, uint32_t height, uint32_t channels, std::unique_ptr<uint8_t[]> data)
    : m_width(width),
      m_height(height),
      m_channels(channels),
      data(std::move(data)) {

}

uint32_t TexData::width() const {
    return m_width;
}

uint32_t TexData::height() const {
    return m_height;
}

uint32_t TexData::channels() const {
    return m_channels;
}

const std::unique_ptr<uint8_t[], std::default_delete<uint8_t[]>> &TexData::getData() const {
    return data;
}

std::unique_ptr<uint8_t[]> &TexData::getData() {
    return data;
}
