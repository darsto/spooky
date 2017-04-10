/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_TEXTURE_TEXTUREDATA_H
#define SPOOKY_RENDER_TEXTURE_TEXTUREDATA_H

#include <cstdint>

namespace texture {

    /**
     * Simple wrapper of texture data.
     * Provides simple interface to load image from disk.
     */
    class TexData {
    public:
        /**
         * Flags to mark special behaviour during image loading.
         * Some of these are proxies of SOIL force_channels flags.
         */
        enum LoadFlag {
            LOAD_NORMAL = 0,     /**< leaves the image in whatever format it was found */
            LOAD_FORCE_L = 1,    /**< forces the image to load as Luminous (greyscale) */
            LOAD_FORCE_LA = 2,   /**< forces the image to load as Luminous with Alpha */
            LOAD_FORCE_RGB = 3,  /**< forces the image to load as Red Green Blue */
            LOAD_FORCE_RGBA = 4  /**< forces the image to load as Red Green Blue Alpha */
        };

    public:
        /**
         * The constructor. Creates texture with garbage data of given dimensions.
         * @param width width of the texture
         * @param height height of the texture
         * @param channels channels of the texture (preferrably 1-4)
         * @return texture of given dimensions (all bytes are random)
         */
        TexData(uint32_t width, uint32_t height, uint32_t channels);

        /**
         * The constructor. Loads texture from image on the physical drive.
         * @param fileName to the file, relative to data/textures/
         * @param flags flags to use during image read
         */
        TexData(const std::string &fileName, int flags = LoadFlag::LOAD_NORMAL);

        /**
         * Copy operator. Deleted.
         * Texture data shouldn't be copied.
         * It contains huge amounts of data, copying would result in major slowdowns.
         */
        TexData(const TexData &other) = delete;

        /**
         * Copy assignment operator. Deleted.
         * Texture data shouldn't be copied.
         * It contains huge amounts of data, copying would result in major slowdowns.
         */
        TexData& operator=(const TexData &other) = delete;

        /**
         * Move constructor.
         * Given texture's dimension variables remain the same,
         * only the pixel data gets moved.
         */
        TexData(TexData &&other);

        /**
         * Move constructor.
         * Given texture's dimension variables remain the same,
         * only the pixel data gets moved.
         */
        TexData& operator=(TexData &&other);

        /**
         * Get width of the texture.
         * @return width of the texture
         */
        uint32_t width() const;

        /**
         * Get height of the texture.
         * @return height of the texture
         */
        uint32_t height() const;

        /**
         * Get number of channels of the texture.
         * @return number of channels of the texture
         */
        uint32_t channels() const;

        /**
         * Get bytes of this texture in basic BMP RGBA format.
         * @return bytes of this texture in basic BMP RGBA format
         */
        const uint8_t* get() const;

        /**
         * Get bytes of this texture in basic BMP RGBA format.
         * @return bytes of this texture in basic BMP RGBA format
         */
        uint8_t *get();

        /**
         * Get image's byte at given index.
         * To get channel n of pixel at pos x:y, you want to use:
         * operator[channels_num * (y * texture_width + x) + n]
         * Note that channel n must be in range [0, channels_num -  1].
         */
        uint8_t &operator[] (uint32_t index);

        /**
         * @overload TexData::operator[] (uint32_t index)
         */
        const uint8_t &operator[] (uint32_t index) const;

        /**
         * The destructor.
         * Deallocates texture data.
         */
        ~TexData();

    private:
        uint32_t m_width, m_height, m_channels;
        uint8_t *m_data;
    };

}

#endif //SPOOKY_RENDER_TEXTURE_TEXTUREDATA_H
