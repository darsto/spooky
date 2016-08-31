/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_PROF_H_H
#define C003_PROF_H_H

#ifdef DEBUG

#include <chrono>

namespace util {

    /**
     * Practical interface for precise measuring passed time.
     * Note that this class is available only in debug builds.
     * For simplicity, use functions from the util::prof namespace.
     */
    class Profiler {
    private:
        using clock = std::chrono::high_resolution_clock;
        using time_p = std::chrono::time_point<std::chrono::high_resolution_clock>;
        using duration = std::chrono::duration<double>;

    public:

        /**
         * The constructor.
         */
        Profiler();

        /**
         * Get the time since last time check or object creation (in seconds with nanosecond precision).
         * @return time since last time check or object creation
         */
        duration::rep timeSinceStart();

        /**
         * Get the time since the object creation (in seconds with nanosecond precision).
         * @return time since the object creation
         */
        duration::rep timeSincePrev();

    private:
        /**
         * Helper method to calculate and return time passed since the given time point.
         * It also updates #m_prevTime member.
         * @param since time point to calculate passed time from
         * @return time passed since given time point
         */
        duration::rep timeSince(time_p since);

        const time_p m_startTime;
        time_p m_prevTime;
    };
}

#define PROF_START(name) util::Profiler name
#define PROF_DURATION_PREV(name) name.timeSincePrev()
#define PROF_DURATION_START(name) name.timeSinceStart()

#else

#define PROF_START(name)
#define PROF_DURATION_PREV(name) 1
#define PROF_DURATION_START(name) 1

#endif

#endif //C003_PROF_H_H
