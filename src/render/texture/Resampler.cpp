/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <cstdlib>

#include "Resampler.h"

using namespace texture;

TexData Resampler::downsample(const TexData &inData, uint32_t downscaleRate) {
    uint32_t outWidth = inData.width() / downscaleRate;
    uint32_t outHeight = inData.height() / downscaleRate;
    uint32_t outChannels = inData.channels();
    TexData outData(outWidth, outHeight, outChannels);
    std::fill_n(outData.get(), outData.height() * outData.channels(), 0);

    /** temporary buffer to hold non-normalized pixel data */
    double tmp[outChannels]{};

    int64_t samplesCount = downscaleRate;
    for (int y = 0; y < outHeight; ++y) {
        for (int x = 0; x < outWidth; ++x) {

            double weightSum = 0.0;
            for (int sampleNum = 0; sampleNum < samplesCount; ++sampleNum) {
                double weight = Resampler::weight(sampleNum - (downscaleRate - 1) / 2);
                uint32_t inPixelPos = inData.channels() * ((y * inData.width() + x) * downscaleRate + sampleNum);
                for (int curChannel = 0; curChannel < outChannels; ++curChannel) {
                    tmp[curChannel] += inData[inPixelPos + curChannel] * weight;
                }
                weightSum += weight;
            }

            uint32_t outPixelPos = outChannels * (y * outWidth + x);
            for (int curChannel = 0; curChannel < outChannels; ++curChannel) {
                tmp[curChannel] /= weightSum;
                outData[outPixelPos + curChannel] = clamp((uint32_t) tmp[curChannel]);
                tmp[curChannel] = 0;
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
