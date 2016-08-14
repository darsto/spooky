//
// Created by dar on 8/3/16.
//

#ifndef C003_RENDER_TEXTURE_RESAMPLER_H
#define C003_RENDER_TEXTURE_RESAMPLER_H

#include <cstdint>
#include <memory>
#include <cmath>

namespace util {

    class Resampler {
    public:
        static std::unique_ptr<uint8_t[]> downsample(uint8_t *inData, size_t inWidth, size_t inHeight, size_t channels, size_t downscaleRate);

    private:
        static double weight(double dist);

        static uint8_t clamp(int32_t value);
    };

}

#endif //C003_RENDER_TEXTURE_RESAMPLER_H
