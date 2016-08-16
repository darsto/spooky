//
// Created by dar on 4/30/16.
//

#ifndef C003_FILES_H
#define C003_FILES_H

#include <string>
#include <vector>
#include <dirent.h>

#include "os.h"

namespace files {

    namespace type {
        constexpr const char map[] = "map";
        constexpr const char script[] = "scripts";
        constexpr const char shader[] = "shaders";
        constexpr const char texture[] = "textures";
    }

    extern const char fileSeparator;

    std::string getFilePath(const std::string &file);

    template<const char *type>
    std::string getFilePath(const std::string &fileName) {
        std::string dir(type);
        dir += fileSeparator;
        return getFilePath(dir + fileName);
    }

    std::vector<std::string> listdir(const char *path);
}

#endif //C003_FILES_H
