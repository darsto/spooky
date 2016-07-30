//
// Created by dar on 11/21/15.
//

#include "Texture.h"
#include <SOIL.h>

int Texture::boundTexId = -1;
int Texture::activeTexId = -1;

Texture::Texture() { }

void Texture::createFromData(unsigned char *data) {
    this->id = SOIL_create_OGL_texture(data, this->width, this->height, this->channels, 0, SOIL_FLAG_MULTIPLY_ALPHA);

    if (this->mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

bool Texture::loadTexture2D(std::string path, bool mipmaps) {
    path = "data/textures/" + path;
#ifdef __ANDROID__
    path = "/sdcard/c003/" + path; //TODO Move files inside apk
#endif // __ANDROID__

    this->path = path;
    this->mipmaps = mipmaps;
    this->width = width;
    this->height = height;
    this->channels = channels;

    unsigned char *data_ptr = SOIL_load_image(this->path.c_str(), &this->width, &this->height, &this->channels, SOIL_LOAD_RGBA);
    createFromData(data_ptr);
    delete data_ptr;

    return true;
}

void Texture::setSamplerParameter(GLenum parameter, GLenum value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::setFiltering(int filterMag, int filterMin) {
    if (filterMag == TEXTURE_FILTER_MAG_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else if (filterMag == TEXTURE_FILTER_MAG_BILINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (filterMin == TEXTURE_FILTER_MIN_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_BILINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    else if (filterMin == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (filterMin == TEXTURE_FILTER_MIN_TRILINEAR_MIPMAP)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    this->filterMin = filterMin;
    this->filterMag = filterMag;
}

void Texture::bindTexture(int bindId) {
    this->boundId = bindId;
    if (Texture::boundTexId != bindId || Texture::activeTexId != bindId) {
        glActiveTexture(GL_TEXTURE0 + bindId);
        Texture::activeTexId = bindId;
    }
    if (Texture::boundTexId != this->id) {
        glBindTexture(GL_TEXTURE_2D, this->id);
        Texture::boundTexId = this->id;
    }
}

int Texture::getMinificationFilter() const {
    return filterMin;
}

int Texture::getMagnificationFilter() const {
    return filterMag;
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

int Texture::getChannels() const {
    return channels;
}

int Texture::getBoundId() const {
    return boundId;
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}
