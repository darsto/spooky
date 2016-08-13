//
// Created by dar on 8/3/16.
//

#include "Resampler.h"

using namespace util;

std::unique_ptr<uint8_t[]> Resampler::downsample(uint8_t *inData, size_t inWidth, size_t inHeight, size_t channels, size_t downscaleRate) {
    size_t outWidth = inWidth / downscaleRate;
    size_t outHeight = inHeight / downscaleRate;
    auto outData = std::make_unique<uint8_t[]>(outWidth * outHeight * channels);
    for (int i = 0; i < outWidth * outHeight * channels; ++i) {
        outData[i] = 0;
    }

    int64_t samples = downscaleRate;
    for (int y = 0; y < outHeight; ++y) {
        for (int x = 0; x < outWidth; ++x) {
            double tmp[4]{};
            double weightSum = 0.0;
            for (int s = 0; s < samples; ++s) {
                double weight = Resampler::weight(s - (downscaleRate - 1) / 2);
                for (int j = 0; j < 4; ++j) {
                    tmp[j] += inData[4 * ((y * inWidth + x) * downscaleRate + s) + j] * weight;
                }
                weightSum += weight;
            }
            for (int j = 0; j < 4; ++j) {
                tmp[j] /= weightSum;
                outData[4 * (y * outWidth + x) + j] = clamp((uint32_t) tmp[j]);
            }
        }
    }
    return outData;
}

double Resampler::weight(double dist) {
    if (abs(dist) > 3)
        return 0;
    else
        return (3 - abs(dist)) / 3.0;
}

uint8_t Resampler::clamp(int32_t value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return (uint8_t) value;
}
