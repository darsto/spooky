/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_UTIL_OS_H
#define SPOOKY_UTIL_OS_H

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
 * The following macro is being set by the NDK compiler
 */
#undef ANDROID

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

/**
 * Main logic of the platform-specific choices
 */
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

/**
 * Disable particular features if it's a simulation
 */
#ifdef SIMULATION
    #undef USES_SDL
    #undef USES_KEYBOARD
#endif // SIMULATION

#endif //SPOOKY_UTIL_OS_H
