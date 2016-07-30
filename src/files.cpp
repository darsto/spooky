//
// Created by dar on 5/1/16.
//

#include "files.h"

std::string IO::getFilePath(const std::string &file) {
#ifdef __ANDROID__
    return "/sdcard/c003/data/" + file;
#else
    return "data/" + file;
#endif
}