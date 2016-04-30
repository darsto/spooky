//
// Created by dar on 4/30/16.
//

#ifndef C003_FILES_H
#define C003_FILES_H

#include <string>

std::string getFilePath(const std::string &file) {
#ifdef __ANDROID__
    return "/sdcard/c003/" + file;
#else
    return file;
#endif
}

#endif //C003_FILES_H
