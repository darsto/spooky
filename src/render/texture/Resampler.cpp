/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <cstdlib>

#include "Resampler.h"

using namespace texture;

TexData Resampler::downsample(uint8_t *inPixels, uint32_t inWidth, uint32_t inHeight, uint32_t inChannels, uint32_t downscaleRate) {
    uint32_t outWidth = inWidth / downscaleRate;
    uint32_t outHeight = inHeight / downscaleRate;
    TexData outData(outWidth, outHeight, inChannels);

    std::fill_n(outData.getData(), outData.height() * outData.channels(), 0);

    /** temporary buffer to hold non-normalized pixel data */
    double *tmp = new double[inChannels]();

    int64_t samplesCount = downscaleRate;
    for (int y = 0; y < outHeight; ++y) {
        for (int x = 0; x < outWidth; ++x) {

            double weightSum = 0.0;
            for (int sampleNum = 0; sampleNum < samplesCount; ++sampleNum) {
                double weight = Resampler::weight(sampleNum - (downscaleRate - 1) / 2);
                uint32_t inPixelPos = inChannels * ((y * inWidth + x) * downscaleRate + sampleNum);
                for (int curChannel = 0; curChannel < inChannels; ++curChannel) {
                    double val = inPixels[inPixelPos + curChannel] * weight;
                    tmp[curChannel] += val;
                }
                weightSum += weight;
            }

            uint32_t outPixelPos = inChannels * (y * outWidth + x);
            for (int curChannel = 0; curChannel < inChannels; ++curChannel) {
                tmp[curChannel] /= weightSum;
                outData.getData()[outPixelPos + curChannel] = clamp((uint32_t) tmp[curChannel]);
                tmp[curChannel] = 0;
            }
        }
    }

    delete[] tmp;
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
