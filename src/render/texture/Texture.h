/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_TEXTURE_H
#define C003_TEXTURE_H
#pragma once

#include <string>
#include <memory>
#include <map>
#include <regex>
#include <unordered_map>

#include "render/opengl.h"
#include "Packer.h"

class invalid_texture_error : public std::runtime_error {
public:
    invalid_texture_error(const char *msg) : std::runtime_error(msg) {}
};

class TexData {
public:
    TexData(uint32_t width, uint32_t height, uint32_t channels, std::unique_ptr<uint8_t[]> data);

    uint32_t width() const;
    uint32_t height() const;
    uint32_t channels() const;
    const std::unique_ptr<uint8_t[]> &getData() const;
    std::unique_ptr<uint8_t[]> &getData();
private:
    uint32_t m_width, m_height, m_channels;
    std::unique_ptr<uint8_t[]> data;
};

class Texture {
public:
    enum class MagFilter : GLenum {
        NEAREST = GL_NEAREST, // Nearest criterion for magnification
        BILINEAR = GL_LINEAR, // Bilinear criterion for magnification
    };

    enum class MinFilter : GLenum {
        NEAREST = GL_NEAREST, // Nearest criterion for minification
        BILINEAR = GL_LINEAR, // Bilinear criterion for minification
        NEAREST_MIPMAP = GL_NEAREST_MIPMAP_NEAREST, // Nearest criterion for minification, but on closest mipmap
        BILINEAR_MIPMAP = GL_LINEAR_MIPMAP_NEAREST, // Bilinear criterion for minification, but on closest mipmap
        TRILINEAR_MIPMAP = GL_LINEAR_MIPMAP_LINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
    };

    Texture(const std::string &fileName);
    ~Texture();
    void bindTexture();

    void filtering(MagFilter filterMag, MinFilter filterMin);
    void samplerParameter(GLenum parameter, GLenum value);

    MinFilter minificationFilter() const;
    MagFilter magnificationFilter() const;
    int width() const;
    int height() const;
    int channels() const;
    int boundId() const;
    const uint64_t getElementsNum() const;

private:
    void loadTile(const std::string &path);
    void writeTexToGPU(std::unique_ptr<uint8_t[]> data, uint32_t level);

    GLuint m_id;
    MinFilter m_filterMin;
    MagFilter m_filterMag;
    std::string m_path;

    texture::Packer packer;
    std::unordered_map<uint64_t, TexData> m_texData;

    std::vector<std::string> m_tiles;

    static int m_boundTexId;
    static const std::regex FILE_EXTENSION_REGEX;
};

#endif //C003_TEXTURE_H
