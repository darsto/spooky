/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * NOTE: This class requires heavy exception handling.
 * If something goes wrong it would be a real hell to debug
 */

#include <memory>
#include <regex>
#include <cstdlib>
#include <cmath>

#include "Atlas.h"
#include "util/collection.h"
#include "util/file.h"
#include "Resampler.h"
#include "util/log.h"
#include "util/prof.h"

using namespace texture;

Atlas::Atlas(const std::string &name, uint32_t channels, bool mipmaps, const std::string &extensions)
    : m_path(name),
      m_tileNames(util::collection::filter(util::file::list(util::file::path<util::file::type::texture>(name).c_str()), std::regex("(.*)(\\.(" + extensions + "))", std::regex::ECMAScript | std::regex::icase))) {

    PROF_START(load);
    for (const std::string &tile : m_tileNames) {
        loadTile(tile);
    }

    m_packer.pack();

    Log::debug("Preparing the texture atlas \"%s\" took %f sec.", name.c_str(), PROF_DURATION_PREV(load));

    TexData orgBuffer(m_packer.size().width(), m_packer.size().height(), channels);

    for (const util::Packer::Element &el : m_packer.elements()) {
        const TexData &inTile = m_texData.find(el.first)->second;
        writeToCanvas(inTile, orgBuffer, std::make_pair<uint32_t, uint32_t>(el.second.x(), el.second.y()));
    }

    m_atlasData.emplace_back(std::move(orgBuffer));

    Log::debug("\tResampling level 0 of the texture atlas \"%s\" took %f sec.", name.c_str(), PROF_DURATION_PREV(load));

    if (mipmaps) {
        uint32_t mipmapLevels = (uint32_t) std::ceil(std::log(std::max<uint32_t>(m_packer.size().width(), m_packer.size().height())) / std::log(2));

        for (uint8_t level = 1; level < mipmapLevels; ++level) {
            uint32_t downsample = 1u << level;

            TexData buffer(m_packer.size().width() / downsample, m_packer.size().height() / downsample, channels);
            for (const util::Packer::Element &el : m_packer.elements()) {
                const TexData &inTile = m_texData.find(el.first)->second;
                TexData resampledData = texture::Resampler::downsample(inTile, downsample);
                auto pos = std::make_pair<uint32_t, uint32_t>(el.second.x() / downsample, el.second.y() / downsample);
                writeToCanvas(resampledData, buffer, pos, level);
            }

            m_atlasData.emplace_back(std::move(buffer));
            Log::debug("\tResampling level %d of the texture atlas \"%s\" took %f sec.", level, name.c_str(), PROF_DURATION_PREV(load));
        }
    }

    Log::debug("Generating the texture atlas \"%s\" took %f sec.", name.c_str(), PROF_DURATION_START(load));
}

void Atlas::loadTile(const std::string &fileName) {
    TexData tex(m_path + util::file::file_separator_str + fileName);
    //TODO check for channels num mismatch
    uint64_t id = m_hash(fileName.substr(0, fileName.find_last_of('.')));

    m_packer.add({id, util::Rectangle(tex.width(), tex.height())});
    m_texData.emplace(id, std::move(tex));
}

const util::Rectangle Atlas::element(const std::string &name) const {
    uint64_t id = m_hash(name);
    auto elements = m_packer.elements();

    auto it = std::find_if(elements.begin(), elements.end(), [id](const util::Packer::Element &element) {
        return element.first == id;
    });

    if (it == elements.end()) {
        throw std::runtime_error("Trying to get inexistent element \"" + name + "\" from texture atlas \"" + m_path + "\".");
    }

    return it->second;
}

uint32_t Atlas::getElementsNum() const {
    return m_texData.size();
}

const std::vector<TexData> &Atlas::atlasData() const {
    return m_atlasData;
}

std::vector<TexData> &Atlas::atlasData() {
    return m_atlasData;
}