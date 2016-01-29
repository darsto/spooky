//
// Created by dar on 1/29/16.
//

#ifndef C003_OS_H
#define C003_OS_H

#define OS_WIN32 0
#define OS_UNIX 1
#define OS_ANDROID 2
#define OS_APPLE 3

#ifdef _WIN32
#define OS OS_WIN32
#elif __APPLE__
#define OS OS_APPLE
#elif __ANDROID__
#define OS OS_ANDROID
#define __DEFMOBILE__ 1
#elif __unix__
#define OS OS_UNIX
#endif

#define MOBILE (OS == OS_ANDROID)

#endif //C003_OS_H
