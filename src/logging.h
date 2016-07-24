//
// Created by dar on 1/23/16.
//

#ifndef C003_LOGGING_H
#define C003_LOGGING_H

namespace Log {
    constexpr const char *LOG_TAG = "SpookyTom";

    template<typename... Args>
    constexpr const void info(Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, std::forward<Args>(args)...)
#else
        printf(std::forward<Args>(args)...);
#endif
    };

    template<typename... Args>
    constexpr const void debug(Args &&...args) {
#ifdef DEBUG
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, std::forward<Args>(args)...)
#else
        printf(std::forward<Args>(args)...);
#endif
#endif
    };

    template<typename... Args>
    constexpr const void warning(Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_WARN, ANDROID_LOG_DEBUG, std::forward<Args>(args)...)
#else
        printf(std::forward<Args>(args)...);
#endif
    };

    template<typename... Args>
    constexpr const void error(Args &&...args) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, std::forward<Args>(args)...)
#else
        printf(std::forward<Args>(args)...);
#endif
    };
};

#endif //C003_LOGGING_H
