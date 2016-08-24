/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_ATLAS_H
#define C003_RENDER_TEXTURE_ATLAS_H
#pragma once

#include <string>
#include <memory>

#include "Texture.h"
#include "util/Rectangle.h"

namespace texture {

    /**
     * Set of texture tiles packed together.
     * Provides easy integration with OpenGL textures.
     * Use with caution, this class has direct access to the GPU.
     * A slightest defect in input data will cause an invalid_texture_error.
     */
    class Atlas : public Texture {
    public:
        /**
         * The constructor.
         * Creates texture atlas out of given directory relative to data/textures/ path.
         * All image files in that directory will be put in the atlas.
         * Note that due to OpenGL general-state context creation, this class requires two-step initialization.
         * Actual loading happens inside the load() method.
         * @param name name of the directory in data/textures/ containing texture tiles
         */
        Atlas(const std::string &name);

        /**
         * Actual texture loading.
         */
        virtual void load() override;

        /**
         * Get subelement of this atlas with given filename.
         * @param name filename of the element to get (without any directory prefix)
         * @return rectangle with position & size of subelement in this atlas
         */
        const util::Rectangle element(const std::string &name) const;

        /**
         * Get number of tiles in this atlas.
         * @return number of tiles in this atlas
         */
        const uint64_t getElementsNum() const;

        /**
         * The destructor. Deletes OpenGL texture.
         */
        virtual ~Atlas();

    private:
        /**
         * Load a single tile with given fileName (without any directory prefix).
         * @param fileName name of the file to load (without any directory prefix)
         */
        void loadTile(const std::string &fileName);

        /**
         * PIMPL. Actual atlas creation doesn't need any external API.
         */
        struct impl;

        /**
         * PIMPL. Actual atlas creation doesn't need any external API.
         */
        std::unique_ptr<impl> m_impl;
    };

}

#endif //C003_RENDER_TEXTURE_ATLAS_H
