/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_TEXTURE_H
#define C003_RENDER_TEXTURE_TEXTURE_H
#pragma once

#include <string>
#include <memory>

#include "render/opengl.h"
#include "util/Rectangle.h"

namespace texture {

    /**
     * Set of texture tiles packed together.
     * Provides easy integration with OpenGL textures.
     * Use with caution, this class has direct access to the GPU.
     * A slightest defect in input data will cause an invalid_texture_error.
     */
    class Atlas {
    public:
        /**
         * Magnification filter
         * (Mode of texture upscaling)
         */
        enum class MagFilter : GLenum {
            NEAREST = GL_NEAREST,                           /**< Nearest criterion for magnification */
            BILINEAR = GL_LINEAR,                           /**< Bilinear criterion for magnification */
        };

        /**
         * Minifaction filter.
         * (Mode of texture downscaling)
         */
        enum class MinFilter : GLenum {
            NEAREST = GL_NEAREST,                           /**< Nearest criterion for minification */
            BILINEAR = GL_LINEAR,                           /**< Bilinear criterion for minification */
            NEAREST_MIPMAP = GL_NEAREST_MIPMAP_NEAREST,     /**< Nearest criterion for minification, but on closest mipmap */
            BILINEAR_MIPMAP = GL_LINEAR_MIPMAP_NEAREST,     /**< Bilinear criterion for minification, but on closest mipmap */
            TRILINEAR_MIPMAP = GL_LINEAR_MIPMAP_LINEAR,     /**< Bilinear criterion for minification on two closest mipmaps, then averaged */
        };

        /**
         * The constructor.
         * Creates texture atlas out of given directory relative to data/textures/ path.
         * @param name name of the directory in data/textures/ containing texture tiles
         */
        Atlas(const std::string &name);

        /**
         * Bind the texture atlas as OpenGL texture.
         */
        void bindTexture();

        /**
         * Set OpenGL filters.
         * @param filterMag magnification filter
         * @param filterMin minification filter
         */
        void filtering(MagFilter filterMag, MinFilter filterMin);

        /**
         * Set given OpenGL sampler parameter.
         * @param parameter OpenGL parameter to set
         * @param value value to set
         */
        void samplerParameter(GLenum parameter, GLint value);

        /**
         * Get current minification filter.
         * @return minification filter
         */
        MinFilter minFilter() const;

        /**
         * Get current magnification filter.
         * @return magnification filter
         */
        MagFilter magFilter() const;

        /**
         * Get width of the complete atlas.
         * @return width of the complete atlas
         */
        int width() const;

        /**
         * Get height of the complete atlas.
         * @return height of the complete atlas
         */
        int height() const;

        /**
         * Get number of channels in this atlas.
         * @return number of channels in this atlas
         */
        int channels() const;

        /**
         * Get currently active OpenGL texture id.
         * @return currently active OpenGL texture id
         */
        int activeTex() const;

        const util::Rectangle element(const std::string &name) const;

        /**
         * Get number of tiles in this atlas.
         * @return number of tiles in this atlas
         */
        const uint64_t getElementsNum() const;

        /**
         * The destructor. Deletes OpenGL texture.
         */
        ~Atlas();

    private:
        void loadTile(const std::string &fileName);

        GLuint m_id;
        MinFilter m_minFilter;
        MagFilter m_magFilter;
        std::string m_path;

        struct impl;
        std::unique_ptr<impl> m_impl;

        static int m_boundTexId;
    };

}

#endif //C003_RENDER_TEXTURE_TEXTURE_H
