/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_TEXTUREDATA_H
#define C003_RENDER_TEXTURE_TEXTUREDATA_H

#include <cstdint>
#include <memory>

namespace texture {

    /**
     * Simple wrapper of texture data.
     * Provides simple interface to load image from disk.
     */
    class Data {
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
         * The constructor. Creates plain texture of given specification.
         * @param width width of the texture
         * @param height height of the texture
         * @param channels channels of the texture (preferrably 1-4)
         * @return plain texture of given specification (all bytes are zeros)
         */
        Data(uint32_t width, uint32_t height, uint32_t channels);

        /**
         * The constructor. Loads texture from image on the physical drive.
         * @param fileName to the file, relative to data/textures/
         * @param flags
         * @return
         */
        Data(const std::string &fileName, int flags = LoadFlag::LOAD_NORMAL);

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
        const std::unique_ptr<uint8_t[]> &getData() const;

        /**
         * Get bytes of this texture in basic BMP RGBA format.
         * @return bytes of this texture in basic BMP RGBA format
         */
        std::unique_ptr<uint8_t[]> &getData();

    private:
        uint32_t m_width, m_height, m_channels;
        std::unique_ptr<uint8_t[]> m_data;
    };

}

#endif //C003_RENDER_TEXTURE_TEXTUREDATA_H
