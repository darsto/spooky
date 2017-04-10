/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * TODO: Add log levels to be able to enable/disable particular log entries
 */

#ifndef SPOOKY_UTIL_LOG_H
#define SPOOKY_UTIL_LOG_H

#include "util/os.h"

#ifdef DEF_ANDROID
#include <android/log.h>
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
// disables "format not a string literal and no format arguments" warning at printf(...) lines

namespace util {

    /**
     * Set of useful functions and variables for clogging
     */
    namespace log {

        /**
         * Log entry identifier.
         * On some mobile platforms logs of many different applications are contained within one file.
         * This identifier lets the user identify which application given log entry comes from.
         */
        constexpr const char *LOG_TAG = "Spooky";

        /**
         * Standard log message, lowest priority.
         */
        template<typename... Args>
        constexpr const void info(const char *msg, Args &&...args) {
#ifdef DEF_ANDROID
            __android_log_print(ANDROID_LOG_INFO, LOG_TAG, msg, std::forward<Args>(args)...);
#else
            printf(msg, std::forward<Args>(args)...);
            putchar('\n');
#endif
        };

        /**
         * Debug log message, lowest priority.
         * Enabled only in debug builds
         */
        template<typename... Args>
        constexpr const void debug(const char *msg, Args &&...args) {
#ifdef DEBUG
#ifdef DEF_ANDROID
            __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, msg, std::forward<Args>(args)...);
#else
            printf(msg, std::forward<Args>(args)...);
            putchar('\n');
#endif
#endif
        };

        /**
         * Warning log message, medium priority.
         */
        template<typename... Args>
        constexpr const void warning(const char *msg, Args &&...args) {
#ifdef DEF_ANDROID
            __android_log_print(ANDROID_LOG_WARN, LOG_TAG, msg, std::forward<Args>(args)...);
#else
            printf(msg, std::forward<Args>(args)...);
            putchar('\n');
#endif
        };

        /**
         * Error log message, highest priority.
         */
        template<typename... Args>
        constexpr const void error(const char *msg, Args &&...args) {
#ifdef DEF_ANDROID
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, msg, std::forward<Args>(args)...);
#else
            printf(msg, std::forward<Args>(args)...);
            putchar('\n');
#endif
        };
    }
}

#pragma GCC diagnostic pop

/**
 * Helper namespace to use logging functions.
 */
namespace Log = util::log;

#endif //SPOOKY_UTIL_LOG_H
