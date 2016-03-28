//
// Created by dar on 11/21/15.
//

#ifndef C003_TEXTURE_H
#define C003_TEXTURE_H
#pragma once

#include <string>
#include <map>
#include "opengl.h"

enum ETextureFiltering
{
    TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
    TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
    TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
    TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
    TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

class Texture
{
public:
    Texture();
    ~Texture();
    void createFromData(unsigned char* data);
    bool loadTexture2D(const std::string &path, bool mipmaps = false);
    void bindTexture(int id = 0);

    void setFiltering(int filterMag, int filterMin);

    void setSamplerParameter(GLenum parameter, GLenum value);

    int getMinificationFilter() const;
    int getMagnificationFilter() const;
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;

    int getBoundId() const;

private:
    int width, height, channels;
    GLuint id;
    bool mipmaps;
    int boundId = -1;
    int filterMin, filterMag;
    std::string path;

    static int boundTexId;
    static int activeTexId;
};

#endif //C003_TEXTURE_H
