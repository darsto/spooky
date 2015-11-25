//
// Created by dar on 11/21/15.
//

#include <GLES3/gl3.h>
#include <SOIL.h>
#include <GL/gl.h>
#include "Texture.h"

Texture::Texture() {
    bMipMapsGenerated = false;
}

/*-----------------------------------------------

Name:		createFromData

Params:	a_sPath - path to the texture
				format - format of data
				bGenerateMipMaps - whether to create mipmaps

Result:	Creates texture from provided data.

/*---------------------------------------------*/

void Texture::createFromData(unsigned char *bData, int a_iWidth, int a_iHeight, int a_iBPP, GLenum format, bool bGenerateMipMaps) {
    // Generate an OpenGL texture ID for this texture
    glGenTextures(1, &uiTexture);
    glBindTexture(GL_TEXTURE_2D, uiTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, a_iWidth, a_iHeight, 0, format, GL_UNSIGNED_BYTE, bData);
    if (bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);

    glGenSamplers(1, &uiSampler);

    sPath = "";
    bMipMapsGenerated = bGenerateMipMaps;
    iWidth = a_iWidth;
    iHeight = a_iHeight;
    iBPP = a_iBPP;
}

/*-----------------------------------------------

Name:		loadTexture2D

Params:	a_sPath - path to the texture
				bGenerateMipMaps - whether to create mipmaps

Result:	Loads texture from a file, supports most
			graphics formats.

/*---------------------------------------------*/

bool Texture::loadTexture2D(string a_sPath, bool bGenerateMipMaps) {

    int width, height;
    unsigned char *data_ptr = SOIL_load_image(a_sPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    createFromData(data_ptr, width, height, 4, GL_RGBA, bGenerateMipMaps);

    sPath = a_sPath;

    return true; // Success
}

void Texture::setSamplerParameter(GLenum parameter, GLenum value) {
    glSamplerParameteri(uiSampler, parameter, value);
}

/*-----------------------------------------------

Name:		setFiltering

Params:	tfMagnification - mag. filter, must be from
									ETextureFiltering enum
			tfMinification - min. filter, must be from
									ETextureFiltering enum

Result:	Sets magnification and minification
			texture filter.

/*---------------------------------------------*/

void Texture::setFiltering(int a_tfMagnification, int a_tfMinification) {
    // Set magnification filter
    if (a_tfMagnification == TEXTURE_FILTER_MAG_NEAREST)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else if (a_tfMagnification == TEXTURE_FILTER_MAG_BILINEAR)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set minification filter
    if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (a_tfMinification == TEXTURE_FILTER_MIN_TRILINEAR)
        glSamplerParameteri(uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    tfMinification = a_tfMinification;
    tfMagnification = a_tfMagnification;
}

/*-----------------------------------------------

Name:		bindTexture

Params:	iTextureUnit - texture unit to bind texture to

Result:	Guess what it does :)

/*---------------------------------------------*/

void Texture::bindTexture(int iTextureUnit) {
    glActiveTexture(GL_TEXTURE0 + iTextureUnit);
    glBindTexture(GL_TEXTURE_2D, uiTexture);
    glBindSampler(iTextureUnit, uiSampler);
}

/*-----------------------------------------------

Name:		releaseTexture

Params:	none

Result:	Frees all memory used by texture.

/*---------------------------------------------*/

void Texture::releaseTexture() {
    glDeleteSamplers(1, &uiSampler);
    glDeleteTextures(1, &uiTexture);
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