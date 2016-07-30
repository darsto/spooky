//
// Created by dar on 11/21/15.
//

#include <SOIL.h>
#include <memory>

#include "Texture.h"
#include "src/files.h"

int Texture::m_boundTexId = -1;
int Texture::m_activeTexId = -1;

Texture::Texture() {}

void Texture::createFromData(unsigned char *data) {
    m_id = SOIL_create_OGL_texture(data, m_width, m_height, m_channels, 0, SOIL_FLAG_MULTIPLY_ALPHA);

    if (m_mipmapEnabled) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture::loadTexture2D(const std::string &fileName, bool mipmaps) {
    m_path = IO::getFilePath<IO::Data::TEXTURE>(fileName);
    m_mipmapEnabled = mipmaps;

    int width, height, channels;
    auto data_ptr = std::unique_ptr<unsigned char[]>(SOIL_load_image(m_path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA));

    m_width = width;
    m_height = height;
    m_channels = channels;

    createFromData(data_ptr.get());
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
