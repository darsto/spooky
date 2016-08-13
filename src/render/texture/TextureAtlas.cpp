/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <map>
#include <regex>
#include <SOIL.h>
#include <iostream>

#include "TextureAtlas.h"
#include "util.h"
#include "Packer.h"
#include "Resampler.h"

using namespace texture;

class TextureAtlas::impl {
public:
    void loadTex2D(const std::string &path) {
        int32_t width, height, channels;
        auto bytes = std::unique_ptr<uint8_t[]>(SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO));

        if (width > 0 && height > 0 && channels > 0) {
            uint64_t id = packer.add(Rectangle((uint32_t) width, (const uint32_t) height));
            TexData tex((uint32_t) width, (uint32_t) height, (uint32_t) channels, std::move(bytes));
            m_texData.emplace(id, std::move(tex));
        } else {
            char msg[90];
            snprintf(msg, sizeof(msg), "Trying to load invalid texture (width:%d, height:%d, channels:%d).", width, height, channels);
            throw invalid_texture_error(msg);
        }
    }

    void generateTextures() {
        packer.pack();
        const Packer::Element *node = nullptr;

        size_t mipmapLevels = std::log2(std::max(packer.size().width(), packer.size().height()));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels - 1);

        for (uint32_t level = 0, downsample = 1; level < mipmapLevels; ++level, downsample <<= 1) {
            uint8_t *pixelData = new uint8_t[4 * packer.size().field() / downsample / downsample];
            uint32_t w = packer.size().width() / downsample;
            uint32_t h = packer.size().height() / downsample;
            /*TexData texData(packer.size().width(), packer.size().height(), 4, std::move(pixelData));
            writeNode(node, texData, downsample);*/
            for (int i = 0; i < 4 * w * h; ++i) {
                pixelData[i] = 255;
            }
            glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        }
    }

private:
    void writeToBinaryImg(const TexData &texIn, TexData &texOut, const Rectangle &rectTo, uint32_t downsample) {
        if (texIn.channels() != texOut.channels()) {
            char msg[80];
            snprintf(msg, sizeof(msg), "Trying to write %d-channel image into %d-channel image.", texIn.channels(), texOut.channels());
            throw invalid_texture_error(msg);
        } else if (rectTo.x() + rectTo.width() > texOut.width() || rectTo.y() + rectTo.height() > texOut.height()) {
            throw invalid_texture_error("Trying to write data into an image beyond it's borders.");
        }

        auto resampled = texture::Resampler::downsample(texIn.getData().get(), texIn.width(), texIn.height(), texIn.channels(), downsample);

        for (int yIn = 0; yIn < texIn.height() / downsample; ++yIn) {
            for (int xIn = 0; xIn < texIn.width() / downsample; ++xIn) {
                uint32_t outPixelPos = rectTo.x() / downsample + xIn + (rectTo.y() / downsample + yIn) * texOut.width() / downsample;
                uint32_t inPixelPos = xIn + yIn * texIn.width() / downsample;
                for (int channel = 0; channel < texOut.channels(); ++channel) {
                    texOut.getData()[texOut.channels() * outPixelPos + channel] = resampled[texOut.channels() * inPixelPos + channel];
                }
            }
        }
    }

    Packer packer;
    std::map<uint64_t, TexData> m_texData;

public:
    static const std::regex FILE_EXTENSION_REGEX;
};

const std::regex TextureAtlas::impl::FILE_EXTENSION_REGEX = std::regex("(.*)(\\.(jpg|png|gif))", std::regex::ECMAScript | std::regex::icase);

uint32_t TextureAtlas::s_boundId = 0;

TextureAtlas::TextureAtlas(const std::string &name)
    : m_impl(std::make_unique<TextureAtlas::impl>()),
      m_tiles(util::filter(files::listdir(files::getFilePath<files::Data::TEXTURE>(name).c_str()), m_impl->FILE_EXTENSION_REGEX)) {

    glGenTextures(1, &m_id);
    bind();

    for (const std::string &s : m_tiles) {
        m_impl->loadTex2D(files::getFilePath<files::Data::TEXTURE>(name) + "/" + s);
    }
    m_impl->generateTextures();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

uint32_t TextureAtlas::id() const {
    return m_id;
}

void TextureAtlas::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);

    s_boundId = m_id;
}

TextureAtlas::~TextureAtlas() {}
