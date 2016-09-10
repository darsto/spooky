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
#include <cstdlib>

#include "Atlas.h"
#include "TexData.h"
#include "util/collection.h"
#include "util/file.h"
#include "Resampler.h"
#include "util/Packer.h"
#include "exceptions.h"
#include "util/log.h"
#include "util/prof.h"

using namespace texture;

/**
 * The following state may not be available on some devices (e.g. OpenGL ES 2.0)
 */
#ifdef GL_TEXTURE_MAX_LEVEL
#define USES_MANUAL_MIPMAPS
#endif

#ifndef USES_MANUAL_MIPMAPS
#include <SOIL.h>
#endif

struct Atlas::impl {
    impl(std::vector<std::string> tiles)
        : m_tiles(util::collection::filter(tiles, FILE_EXTENSION_REGEX)) {

    }

    /**
     * OpenGL uses enum to determine a number (and type) of texture channels.
     * Since we don't handle different types of texture channels in Atlas class,
     * just a pure int number of channels is passed between methods.
     */
    GLenum getTexGLFormat(uint32_t channels) {
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

    void writeToCanvas(const TexData &inData, TexData &outBuffer, const std::pair<uint32_t, uint32_t> &pos, uint32_t level = 0) {
        uint32_t inWidth = inData.width();
        uint32_t inHeight = inData.height();
        uint32_t outWidth = m_packer.size().width() / (1u << level);
        uint32_t outChannels = std::min<uint32_t>(outBuffer.channels(), inData.channels());

        for (int yIn = 0; yIn < inHeight; ++yIn) {
            for (int xIn = 0; xIn < inWidth; ++xIn) {
                uint32_t inPixelPos = xIn + yIn * inWidth;
                uint32_t outPixelPos = pos.first + xIn + (pos.second + yIn) * outWidth;
                for (int channel = 0; channel < outChannels; ++channel) {
                    outBuffer[outBuffer.channels() * outPixelPos + channel] = inData[inData.channels() * inPixelPos + channel];
                }
            }
        }
    }

    void writeTexToGPU(TexData &tex, uint32_t level) {
        uint32_t width = tex.width() / (1u << level);
        uint32_t height = tex.height() / (1u << level);
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
            for (int i = 0; i < width * height; ++i) {
                tex[channels * i + 0] = (uint8_t) ((tex[channels * i + 0] * tex[channels * i + 3] + 128) >> 8);
                tex[channels * i + 1] = (uint8_t) ((tex[channels * i + 1] * tex[channels * i + 3] + 128) >> 8);
                tex[channels * i + 2] = (uint8_t) ((tex[channels * i + 2] * tex[channels * i + 3] + 128) >> 8);
            }
        }

        glTexImage2D(GL_TEXTURE_2D, level, getTexGLFormat(channels), width, height, 0, getTexGLFormat(channels), GL_UNSIGNED_BYTE, tex.get());
    }

    util::Packer m_packer;
    std::hash<std::string> m_hash;
    std::unordered_map<uint64_t, TexData> m_texData;

    std::vector<std::string> m_tiles;
    static const std::regex FILE_EXTENSION_REGEX;
};

const std::regex Atlas::impl::FILE_EXTENSION_REGEX = std::regex("(.*)(\\.(jpg|png|gif))", std::regex::ECMAScript | std::regex::icase);

Atlas::Atlas(const std::string &name)
    : Texture(name),
      m_impl(std::make_unique<Atlas::impl>(util::file::list(util::file::path<util::file::type::texture>(name).c_str()))) {

}

void Atlas::load() {
    PROF_START(load);
    for (const std::string &tile : m_impl->m_tiles) {
        loadTile(tile);
    }

    m_impl->m_packer.pack();

    m_width = m_impl->m_packer.size().width();
    m_height = m_impl->m_packer.size().height();
    m_channels = 4;

    Log::debug("Preparing the texture atlas \"%s\" took %f sec.", m_path.c_str(), PROF_DURATION_PREV(load));

    glGenTextures(1, &m_id);
    bindTexture();


    /**
     * Texture canvas for all mipmap levels of this atlas.
     * This is a temporary container, since all data gets uploaded to the GPU right away.
     */
    TexData buffer(width(), height(), channels());

    for (const util::Packer::Element &el : m_impl->m_packer.elements()) {
        const TexData &inTile = m_impl->m_texData.find(el.first)->second;
        m_impl->writeToCanvas(inTile, buffer, std::make_pair<uint32_t, uint32_t>(el.second.x(), el.second.y()));
    }

    m_impl->writeTexToGPU(buffer, 0);

    Log::debug("\tResampling of level 0 of the texture atlas \"%s\" took %f sec.", m_path.c_str(), PROF_DURATION_PREV(load));

#ifdef USES_MANUAL_MIPMAPS
    uint32_t mipmapLevels = (uint32_t) ceil(log(std::max(width(), height())) / log(2));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels - 1);

    for (uint8_t level = 1; level < mipmapLevels; ++level) {
        uint32_t downsample = 1u << level;

        //TODO it's totally unreadable
        for (const util::Packer::Element &el : m_impl->m_packer.elements()) {
            const TexData &inTile = m_impl->m_texData.find(el.first)->second;
            TexData resampledData = texture::Resampler::downsample(inTile, downsample);
            auto pos = std::make_pair<uint32_t, uint32_t>(el.second.x() / downsample, el.second.y() / downsample);
            m_impl->writeToCanvas(resampledData, buffer, pos, level);
        }

        Log::debug("\tResampling of level %d of the texture atlas \"%s\" took %f sec.", level, m_path.c_str(), PROF_DURATION_PREV(load));
        m_impl->writeTexToGPU(buffer, level);
    }
#else
    glGenerateMipmap(GL_TEXTURE_2D);
#endif

    Log::debug("Generating the texture atlas \"%s\" took %f sec.", m_path.c_str(), PROF_DURATION_START(load));
}

void Atlas::loadTile(const std::string &fileName) {
    TexData tex(m_path + util::file::file_separator_str + fileName);
    uint64_t id = m_impl->m_hash(fileName.substr(0, fileName.find_last_of('.')));

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
        snprintf(msg, sizeof(msg), "Trying to get inexistent element (\"%d\") from texture atlas.", name.c_str());
        throw invalid_texture_error(msg);
    }

    return it->second;
}

const uint64_t Atlas::getElementsNum() const {
    return m_impl->m_texData.size();
}

Atlas::~Atlas() {}