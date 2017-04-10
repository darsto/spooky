/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
    : lastTime(high_resolution_clock::now()) {
}

double Timer::delta() {
    time_point<high_resolution_clock> currTime = high_resolution_clock::now();
    duration<double> delta(currTime - lastTime);

    lastTime = high_resolution_clock::now();
    return delta.count();
}
