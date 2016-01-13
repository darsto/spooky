//
// Created by dar on 11/21/15.
//

#include "Texture.h"
#include <SOIL.h>

Texture::Texture() {
    bMipMapsGenerated = false;
}

void Texture::createFromData(unsigned char *bData, int a_iWidth, int a_iHeight, int a_iBPP, GLenum format, bool bGenerateMipMaps) {
    glGenTextures(1, &uiTexture);
    glBindTexture(GL_TEXTURE_2D, uiTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, a_iWidth, a_iHeight, 0, format, GL_UNSIGNED_BYTE, bData);
    if (bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);

    sPath = "";
    bMipMapsGenerated = bGenerateMipMaps;
    iWidth = a_iWidth;
    iHeight = a_iHeight;
    iBPP = a_iBPP;
}

bool Texture::loadTexture2D(string a_sPath, bool bGenerateMipMaps) {

    int width, height;
    unsigned char *data_ptr = SOIL_load_image(a_sPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    createFromData(data_ptr, width, height, 4, GL_RGBA, bGenerateMipMaps);

    sPath = a_sPath;

    return true;
}

void Texture::setSamplerParameter(GLenum parameter, GLenum value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture::setFiltering(int a_tfMagnification, int a_tfMinification) {
    if (a_tfMagnification == TEXTURE_FILTER_MAG_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else if (a_tfMagnification == TEXTURE_FILTER_MAG_BILINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_TRILINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    tfMinification = a_tfMinification;
    tfMagnification = a_tfMagnification;
}

void Texture::bindTexture(int iTextureUnit) {
    this->boundId = iTextureUnit;
    glActiveTexture(GL_TEXTURE0 + iTextureUnit);
    glBindTexture(GL_TEXTURE_2D, uiTexture);
}

int Texture::getMinificationFilter() {
    return tfMinification;
}

int Texture::getMagnificationFilter() {
    return tfMagnification;
}

int Texture::getWidth() {
    return iWidth;
}

int Texture::getHeight() {
    return iHeight;
}

int Texture::getBPP() {
    return iBPP;
}

int Texture::getBoundId() const {
    return boundId;
}

Texture::~Texture() {
    glDeleteTextures(1, &uiTexture);
}
