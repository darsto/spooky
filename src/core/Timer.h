/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_CORE_TIMER_H
#define SPOOKY_CORE_TIMER_H
#pragma once

#include <chrono>

class Timer {
public:
    /**
     * The constructor.
     */
    Timer();

    /**
     * Gets time since last time this function was called (in seconds with nanosecond precision).
     * @return time since last time this function was called (in seconds with nanosecond precision)
     */
    double delta();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
};

#endif //SPOOKY_CORE_TIMER_H
