/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_TEXTURE_H
#define C003_RENDER_TEXTURE_TEXTURE_H

#include <string>

#include "render/opengl.h"
#include "TexData.h"

namespace texture {

    /**
     * A single OpenGL-compatible texture.
     * Use with caution, this class has direct access to the GPU.
     * A slightest defect in input data will cause an invalid_texture_error.
     */
    class Texture {
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
         * Note that due to OpenGL general-state context creation, this class requires two-step initialization.
         * Actual loading happens inside the load() method.
         * @param filename name of the file to load texture from
         */
        Texture();

        /**
         * Writing given texture to the GPU.
         */
        void loadTex(texture::TexData &tex, uint32_t level);

        /**
         * Bind this texture as OpenGL texture.
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
         * Get width of the texture
         * @return width of the texture
         */
        int width() const;

        /**
         * Get height of the texture.
         * @return height of the texture
         */
        int height() const;

        /**
         * Get number of channels.
         * This is equivalent to the number of bytes per pixel.
         * @return number of channels
         */
        int channels() const;

        /**
         * Get currently active OpenGL texture id.
         * @return currently active OpenGL texture id
         */
        int activeTex() const;

        /**
         * The destructor. Deletes OpenGL texture.
         */
        virtual ~Texture();

    protected:
        /**
         * OpenGL uses enum to determine a number (and type) of texture channels.
         * Since we don't handle different types of texture channels in Atlas class,
         * just a pure int number of channels is passed between methods.
         */
        GLenum getTexGLFormat(uint32_t channels);

        /**
         * Unique texture identifier assigned by OpenGL.
         */
        GLuint m_id;

        /**
         * Dimensions of the texture.
         */
        uint32_t m_width = 0, m_height = 0;

        /**
         * Number of channels.
         * This is equivalent to the number of bytes per pixel.
         */
        uint32_t m_channels = 0;

        /**
         * Minification filter
         */
        MinFilter m_minFilter;

        /**
         * Magnification filter
         */
        MagFilter m_magFilter;

        /**
         * Currently bound texture id.
         * Used by texture binding methods to check if actual binding is really required atm.
         */
        static int s_boundTexId;
    };
}

#endif //C003_RENDER_TEXTURE_TEXTURE_H
