/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * TODO: Refactor this class using c++ operators
 */

#include "TexData.h"
#include "exceptions.h"
#include "util/file.h"
#include <SOIL.h>

using namespace texture;

TexData::TexData(uint32_t width, uint32_t height, uint32_t channels)
    : m_width(width),
      m_height(height),
      m_channels(channels),
      m_data(new uint8_t[width * height * channels]()) {

    if (width == 0 || height == 0 || channels == 0) {
        delete[] m_data;
        char msg[100];
        snprintf(msg, sizeof(msg), "Trying to create invalid texture (width:%d, height:%d, channels:%d).", width, height, channels);
        throw invalid_texture_error(msg);
    }
}

TexData::TexData(const std::string &fileName, int flags) {
    int width, height, channels;
    std::string path = util::file::path<util::file::type::texture>(fileName).c_str();
    std::unique_ptr<uint8_t[]> data(SOIL_load_image(path.c_str(), &width, &height, &channels, flags & 0x7)); // use mask of 3 LSB
    if (width > 0 && height > 0 && channels > 0) {
        m_width = (uint32_t) width;
        m_height = (uint32_t) height;
        m_channels = (uint32_t) channels;
        m_data = data.release();
    } else {
        char msg[150];
        snprintf(msg, sizeof(msg), "Trying to load invalid texture (path: %s, width:%d, height:%d, channels:%d).", path.c_str(), width, height, channels);
        throw invalid_texture_error(msg);
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

const uint8_t *TexData::getData() const {
    return m_data;
}

uint8_t *TexData::getData() {
    return m_data;
}

TexData::~TexData() {
    delete[] m_data;
}
