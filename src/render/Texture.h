//
// Created by dar on 11/21/15.
//

#ifndef C003_TEXTURE_H
#define C003_TEXTURE_H
#pragma once

#include <string>

#include "opengl.h"

enum ETextureFiltering
{
    TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
    TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
    TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
    TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
    TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_TRILINEAR_MIPMAP, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

class Texture
{
public:
    Texture();
    ~Texture();
    void createFromData(unsigned char* data);
    void loadTexture2D(const std::string &fileName, bool mipmaps = false);
    void bindTexture(int bindId = 0);
    void filtering(int filterMag, int filterMin);
    void samplerParameter(GLenum parameter, GLenum value);

    int minificationFilter() const;
    int magnificationFilter() const;
    int width() const;
    int height() const;
    int channels() const;
    int boundId() const;

private:
    int m_width;
    int m_height;
    int m_channels;
    GLuint m_id;
    bool m_mipmapEnabled;
    int m_boundId = -1;
    int m_filterMin, m_filterMag;
    std::string m_path;

    static int m_boundTexId;
    static int m_activeTexId;
};

#endif //C003_TEXTURE_H
