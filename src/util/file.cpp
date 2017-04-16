/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include "file.h"
#include "os.h"

const char util::file::file_separator =
#ifdef DEF_WINDOWS
    '\\';
#else
    '/';
#endif

const char util::file::file_separator_str[] =
#ifdef DEF_WINDOWS
    "\\";
#else
    "/";
#endif

std::string util::file::path(const std::string &file) {
#ifdef DEF_ANDROID
    return "/sdcard/spooky/data/" + file;
#else
    return "data/" + file;
#endif
}

std::vector<std::string> util::file::list(const char *path) {
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
            ret.emplace_back(entry->d_name);
        }
    } catch (std::exception e) {
        closedir(dp);
        throw std::ios_base::failure(std::string("Failed to read directory: ") + path);
    }

    closedir(dp);
    return ret;
}
