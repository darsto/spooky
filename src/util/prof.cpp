/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "prof.h"

#ifdef DEBUG

util::Profiler::Profiler()
    : m_startTime(clock::now()),
      m_prevTime(m_startTime) {

}

double util::Profiler::timeSinceStart() {
    return timeSince(m_startTime);
}

double util::Profiler::timeSincePrev() {
    return timeSince(m_prevTime);
}

double util::Profiler::timeSince(util::Profiler::time_p since) {
    time_p currTime = clock::now();
    duration delta(currTime - since);
    m_prevTime = clock::now();
    return delta.count();
}

#endif //DEBUG