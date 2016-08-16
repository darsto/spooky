//
// Created by dar on 5/1/16.
//

#include <vector>
#include <iostream>
#include <fstream>

#include "files.h"

const char files::fileSeparator =
#ifdef DEF_WINDOWS
    '\\';
#else
    '/';
#endif

std::string files::getFilePath(const std::string &file) {
#ifdef DEF_ANDROID
    return "/sdcard/c003/data/" + file;
#else
    return "data/" + file;
#endif
}

std::vector<std::string> files::listdir(const char *path) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir");
        throw std::ios_base::failure(std::string("Failed to open directory: ") + path);
    }

    std::vector<std::string> ret;

    try {
        while ((entry = readdir(dp))) {
            ret.push_back(entry->d_name);
        }
    } catch (std::exception e) {
        closedir(dp);
        throw std::ios_base::failure(std::string("Failed to read directory: ") + path);
    }

    closedir(dp);
    return ret;
}
