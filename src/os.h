//
// Created by dar on 1/29/16.
//

#ifndef C003_OS_H
#define C003_OS_H

/**
 * Variables which are conditionally defined by this header
 */
#undef OPERATING_SYSTEM
#undef DEF_WINDOWS
#undef DEF_APPLE
#undef DEF_IOS
#undef DEF_MAC
#undef DEF_ANDROID
#undef DEF_UNIX
#undef IS_MOBILE
#undef USES_SDL
#undef USES_KEYBOARD

/**
 * Operating systems enum
 */
enum class OS {
    WIN32 = 0,
    UNIX,
    ANDROID,
    IOS,
    MAC
};

#ifdef _WIN32
#define DEF_WINDOWS
//------------WINDOWS------------
    #define OPERATING_SYSTEM OS::WIN32
    #define USES_SDL
    #define USES_KEYBOARD


#elif __APPLE__
#define DEF_APPLE
//------------APPLE--------------
#include "TargetConditionals.h"


#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#define DEF_IOS
//------------IOS----------------
    #define OPERATING_SYSTEM OS::IOS


#elif TARGET_OS_MAC
#define DEF_MAC
//------------MAC----------------
    #define OPERATING_SYSTEM OS::MAC
    #define USES_SDL
    #define USES_KEYBOARD


#else
    #error "Unknown Apple platform"
#endif
#elif __ANDROID__
#define DEF_ANDROID
//------------ANDROID------------
    #define OPERATING_SYSTEM OS::ANDROID


#elif __unix__
#define DEF_UNIX
//------------UNIX---------------
    #define OPERATING_SYSTEM OS::UNIX
    #define USES_SDL
    #define USES_KEYBOARD


#else
    #error "Unknown platform"
#endif

#endif //C003_OS_H
