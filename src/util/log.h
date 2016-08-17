/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_UTIL_LOG_H
#define C003_UTIL_LOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
// disables "format not a string literal and no format arguments" warning at printf(...) lines

namespace Log {
    constexpr const char *LOG_TAG = "SpookyTom";

    template<typename... Args>
    constexpr const void info(const char *msg, Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, msg, std::forward<Args>(args)...)
#else
        printf(msg, std::forward<Args>(args)...);
#endif
    };

    template<typename... Args>
    constexpr const void debug(const char *msg, Args &&...args) {
#ifdef DEBUG
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, msg, std::forward<Args>(args)...)
#else
        printf(msg, std::forward<Args>(args)...);
#endif
#endif
    };

    template<typename... Args>
    constexpr const void warning(const char *msg, Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_WARN, ANDROID_LOG_DEBUG, msg, std::forward<Args>(args)...)
#else
        printf(msg, std::forward<Args>(args)...);
#endif
    };

    template<typename... Args>
    constexpr const void error(const char *msg, Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, msg, std::forward<Args>(args)...)
#else
        printf(msg, std::forward<Args>(args)...);
#endif
    };
};

#pragma GCC diagnostic pop

#endif //C003_UTIL_LOG_H
