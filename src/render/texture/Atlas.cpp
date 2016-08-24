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
#include <regex>
#include <unordered_map>

#include "Atlas.h"
#include "Data.h"
#include "util/collection.h"
#include "util/file.h"
#include "Resampler.h"
#include "util/Packer.h"
#include "exceptions.h"

using namespace texture;

struct Atlas::impl {
    impl(std::vector<std::string> tiles)
        : m_tiles(util::collection::filter(tiles, FILE_EXTENSION_REGEX)) {

    }

    GLenum getTexGLFormat(uint32_t channels) {
        GLenum ret;

        switch (channels) {
            case 1:
                ret = GL_LUMINANCE;
                break;
            case 2:
                ret = GL_LUMINANCE_ALPHA;
                break;
            case 3:
                ret = GL_RGB;
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

    void writeTexToGPU(const Data &tex, uint32_t level) {
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
                tex.getData()[channels * i + 0] = (uint8_t) ((tex.getData()[channels * i + 0] * tex.getData()[channels * i + 3] + 128) >> 8);
                tex.getData()[channels * i + 1] = (uint8_t) ((tex.getData()[channels * i + 1] * tex.getData()[channels * i + 3] + 128) >> 8);
                tex.getData()[channels * i + 2] = (uint8_t) ((tex.getData()[channels * i + 2] * tex.getData()[channels * i + 3] + 128) >> 8);
            }
        }

        glTexImage2D(GL_TEXTURE_2D, level, tex.channels(), tex.width(), tex.height(), 0, getTexGLFormat(tex.channels()), GL_UNSIGNED_BYTE, tex.getData().get());
    }

    util::Packer m_packer;
    std::hash<std::string> m_hash;
    std::unordered_map<uint64_t, Data> m_texData;

    std::vector<std::string> m_tiles;
    static const std::regex FILE_EXTENSION_REGEX;
};

const std::regex Atlas::impl::FILE_EXTENSION_REGEX = std::regex("(.*)(\\.(jpg|png|gif))", std::regex::ECMAScript | std::regex::icase);

Atlas::Atlas(const std::string &name)
    : Texture(name),
      m_impl(std::make_unique<Atlas::impl>(util::file::list(util::file::path<util::file::type::texture>(name).c_str()))) {

}

void Atlas::load() {
    for (const std::string &tile : m_impl->m_tiles) {
        loadTile(tile);
    }

    m_impl->m_packer.pack();

    m_width = m_impl->m_packer.size().width();
    m_height = m_impl->m_packer.size().height();
    m_channels = 4;

    glGenTextures(1, &m_id);
    bindTexture();

    uint32_t mipmapLevels = (uint32_t) std::log2(std::max(width(), height()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels - 1);

    for (uint8_t level = 0; level < mipmapLevels; ++level) {
        uint32_t downsample = 1u << level;
        Data atlas(width() / downsample, height() / downsample, channels());

        for (auto &el : m_impl->m_packer.elements()) {
            Data &tile = m_impl->m_texData.find(el.first)->second;
            auto resampled = texture::Resampler::downsample(tile.getData().get(), tile.width(), tile.height(), tile.channels(), downsample);
            util::Rectangle rect(el.second.x() / downsample, el.second.y() / downsample, el.second.width() / downsample, el.second.height() / downsample);

            uint32_t inWidth = tile.width() / downsample;
            uint32_t inHeight = tile.height() / downsample;
            uint32_t outWidth = m_impl->m_packer.size().width() / downsample;

            for (int yIn = 0; yIn < inHeight; ++yIn) {
                for (int xIn = 0; xIn < inWidth; ++xIn) {
                    uint32_t inPixelPos = xIn + yIn * inWidth;
                    uint32_t outPixelPos = rect.x() + xIn + (rect.y() + yIn) * outWidth;
                    for (int channel = 0; channel < channels(); ++channel) {
                        atlas.getData()[4 * outPixelPos + channel] = resampled[channels() * inPixelPos + channel];
                    }
                }
            }
        }
        m_impl->writeTexToGPU(atlas, level);
    }
}

void Atlas::loadTile(const std::string &fileName) {
    Data tex(m_path + util::file::file_separator_str + fileName);
    uint64_t id = m_impl->m_hash(fileName);

    m_impl->m_packer.add({id, util::Rectangle(tex.width(), tex.height())});
    m_impl->m_texData.emplace(id, std::move(tex));
}

const util::Rectangle Atlas::element(const std::string &name) const {
    uint64_t id = m_impl->m_hash(name);
    auto elements = m_impl->m_packer.elements();

    auto it = std::find_if(elements.begin(), elements.end(), [id](const util::Packer::Element &element) {
        return element.first == id;
    });

    if (it == elements.end()) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Trying to get inexistent element (\"%d\") from texture atlas.", name);
        throw invalid_texture_error(msg);
    }

    return it->second;
}

const uint64_t Atlas::getElementsNum() const {
    return m_impl->m_texData.size();
}

Atlas::~Atlas() {}