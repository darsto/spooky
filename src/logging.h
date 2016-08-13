//
// Created by dar on 1/23/16.
//

#ifndef C003_LOGGING_H
#define C003_LOGGING_H

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

#endif //C003_LOGGING_H
