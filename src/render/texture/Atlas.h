/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_TEXTURE_ATLAS_H
#define SPOOKY_RENDER_TEXTURE_ATLAS_H
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "TexData.h"
#include "util/Rectangle.h"
#include "util/Packer.h"

namespace texture {

    /**
     * Set of texture tiles packed together.
     * It doesn't provide integration with OpenGL textures,
     * for that, use the Texture class.
     * A slightest defect in input data will cause an invalid_texture_error.
     */
    class Atlas {
    public:
        /**
         * The constructor.
         * Creates texture atlas out of given directory relative to data/textures/ path.
         * All image files in that directory will be put in the atlas.
         * @param name name of the directory in data/textures/ containing texture tiles
         * @param extensions file extensions to filter files in given dir with, separated by | sign, by default "jpg|png|gif"
         */
        Atlas(const std::string &name, uint32_t channels, bool mipmaps, const std::string &extensions = "jpg|png|gif");

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
        const uint32_t getElementsNum() const;

        /**
         * Get a container of particular texture levels.
         * If mipmaps are disabled, there will be only a single level.
         * Mipmaps are indexed as the following:
         * atlasData()[n] is n'th mipmap level.
         * @return container of particular texture levels
         */
        const std::vector<TexData> &atlasData() const;

        /**
         * @overload Atlas::atlasData()
         */
        std::vector<TexData> &atlasData();

    private:
        /**
         * Load a single tile with given fileName (without any directory prefix).
         * @param fileName name of the file to load (without any directory prefix)
         */
        void loadTile(const std::string &fileName);

        void writeToCanvas(const TexData &inData, TexData &outBuffer, const std::pair<uint32_t, uint32_t> &pos, uint32_t level = 0) {
            uint32_t inWidth = inData.width();
            uint32_t inHeight = inData.height();
            uint32_t outWidth = m_packer.size().width() / (1u << level);
            uint32_t outChannels = std::min<uint32_t>(outBuffer.channels(), inData.channels());

            for (int yIn = 0; yIn < inHeight; ++yIn) {
                for (int xIn = 0; xIn < inWidth; ++xIn) {
                    uint32_t inPixelPos = xIn + yIn * inWidth;
                    uint32_t outPixelPos = pos.first + xIn + (pos.second + yIn) * outWidth;
                    for (int channel = 0; channel < outChannels; ++channel) {
                        outBuffer[outBuffer.channels() * outPixelPos + channel] = inData[inData.channels() * inPixelPos + channel];
                    }
                }
            }
        }

        std::string m_path;
        util::Packer m_packer;
        std::hash<std::string> m_hash;
        std::unordered_map<uint64_t, TexData> m_texData;
        std::vector<std::string> m_tileNames;
        std::vector<TexData> m_atlasData;
    };
}

#endif //SPOOKY_RENDER_TEXTURE_ATLAS_H
