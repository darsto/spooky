/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <memory>
#include <SOIL2.h>

#include "TexData.h"
#include "util/file.h"
#include "util/log.h"

using namespace texture;

TexData::TexData(uint32_t width, uint32_t height, uint32_t channels)
    : m_width(width),
      m_height(height),
      m_channels(channels),
      m_data(new uint8_t[width * height * channels]()) {

    if (width == 0 || height == 0 || channels == 0) {
        Log::error("Trying to create invalid texture (width:%d, height:%d, channels:%d).", width, height, channels);
    }
}

TexData::TexData(const std::string &fileName, int flags) {
    int width, height, channels;
    std::string path = util::file::path<util::file::type::texture>(fileName).c_str();
    uint8_t* data = SOIL_load_image(path.c_str(), &width, &height, &channels, flags & 0x7); // use mask of 3 LSB

    m_width = (uint32_t) width;
    m_height = (uint32_t) height;
    m_channels = (uint32_t) channels;
    m_data = data;

    if (width <= 0 || height <= 0 || channels <= 0) {
        Log::error("Trying to load invalid texture (path: %s, width:%d, height:%d, channels:%d).", path.c_str(), width, height, channels);
        return;
    }
    
    if (flags & LOAD_BURN_ALPHA) {
        for (uint32_t i = 0; i < m_width * m_height; ++i) {
            for (uint32_t channel = 0; channel < m_channels - 1; ++channel) {
                m_data[m_channels * i + channel] = (uint8_t) ((m_data[m_channels * i + channel] * m_data[m_channels * i + m_channels - 1] + 128) >> 8);
            }
        }
    }
}

TexData::TexData(TexData &&other)
    : m_width(other.m_width),
      m_height(other.m_height),
      m_channels(other.m_channels),
      m_data(other.m_data) {

    other.m_data = nullptr;
}

TexData &TexData::operator=(TexData &&other) {
    delete[] m_data;
    m_width = other.m_width;
    m_height = other.m_height;
    m_channels = other.m_channels;
    m_data = other.m_data;
    other.m_data = nullptr;

    return *this;
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

const uint8_t *TexData::get() const {
    return m_data;
}

uint8_t *TexData::get() {
    return m_data;
}

uint8_t &TexData::operator[](uint32_t index) {
    return m_data[index];
}

const uint8_t &TexData::operator[](uint32_t index) const {
    return m_data[index];
}

TexData::~TexData() {
    SOIL_free_image_data(m_data);
}
