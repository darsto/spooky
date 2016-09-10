/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_RESAMPLER_H
#define C003_RENDER_TEXTURE_RESAMPLER_H

#include <cstdint>
#include <memory>

#include "TexData.h"

namespace texture {

    class Resampler {
    public:
        static TexData downsample(const TexData &inData, uint32_t downscaleRate);

    private:
        static double weight(double dist);
        static uint8_t clamp(int32_t value);
    };

}

#endif //C003_RENDER_TEXTURE_RESAMPLER_H
