//
// Created by dar on 5/1/16.
//

#include "files.h"

std::string getFilePath(const std::string &file) {
#ifdef __ANDROID__
    return "/sdcard/c003/" + file;
#else
    return file;
#endif
}