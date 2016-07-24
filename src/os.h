//
// Created by dar on 1/29/16.
//

#ifndef C003_OS_H
#define C003_OS_H

enum class OS {
    WIN32 = 0,
    UNIX,
    ANDROID,
    APPLE
};

constexpr const OS OPERATING_SYTEM =
#ifdef _WIN32
    OS::WIN32
#elif __APPLE__
    OS::APPLE
#elif __ANDROID__
    OS::ANDROID
#elif __unix__
    OS::UNIX
#endif
;

constexpr const bool IS_MOBILE = OPERATING_SYTEM == OS::ANDROID || OPERATING_SYTEM == OS::APPLE;

#endif //C003_OS_H
