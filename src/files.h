//
// Created by dar on 4/30/16.
//

#ifndef C003_FILES_H
#define C003_FILES_H

#include <string>

namespace IO {

    enum class Data {
        MAP = 0,
        SCRIPT,
        SHADER,
        TEXTURE
    };

    std::string getFilePath(const std::string &file);

    template<Data data>
    std::string getFilePath(const std::string &fileName) {
        std::string ret;
        switch (data) {
            case Data::MAP:
                ret = "map/";
                break;
            case Data::SCRIPT:
                ret = "scripts/";
                break;
            case Data::SHADER:
                ret = "shaders/";
                break;
            case Data::TEXTURE:
                ret = "textures/";
                break;
        }

        return getFilePath(ret + fileName);
    }
}

#endif //C003_FILES_H
