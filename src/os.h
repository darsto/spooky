//
// Created by dar on 1/29/16.
//

#ifndef C003_OS_H
#define C003_OS_H

enum class OS {
    WIN32 = 0,
    UNIX,
    ANDROID,
    IOS,
    MAC
};

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

constexpr const OS OPERATING_SYTEM =
#ifdef _WIN32
    OS::WIN32
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        OS::IOS
    #elif TARGET_OS_MAC
        OS::MAC
    #else
        #error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    OS::ANDROID
#elif __unix__
    OS::UNIX
#else
    #error "Unknown platform"
#endif
;

constexpr const bool IS_MOBILE = OPERATING_SYTEM == OS::ANDROID || OPERATING_SYTEM == OS::IOS;

#endif //C003_OS_H
