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

    enum class Data {
        MAP = 0,
        SCRIPT,
        SHADER,
        TEXTURE
    };

    extern const char fileSeparator;

    std::string getFilePath(const std::string &file);

    template<Data data>
    std::string getFilePath(const std::string &fileName) {
        std::string dir;
        switch (data) {
            case Data::MAP:
                dir = "map";
                break;
            case Data::SCRIPT:
                dir = "scripts";
                break;
            case Data::SHADER:
                dir = "shaders";
                break;
            case Data::TEXTURE:
                dir = "textures";
                break;
        }

        dir += fileSeparator;
        return getFilePath(dir + fileName);
    }

    std::vector<std::string> listdir(const char *path);
}

#endif //C003_FILES_H
