/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_FILES_H
#define C003_FILES_H

#include <string>
#include <vector>
#include <dirent.h>

#include "os.h"

/**
 * Set of useful functions and variables for IO operations
 */
namespace files {

    /**
     * Types of available files.
     * They represent folder names inside data directory.
     */
    namespace type {
        constexpr const char map[] = "map";
        constexpr const char script[] = "scripts";
        constexpr const char shader[] = "shaders";
        constexpr const char texture[] = "textures";
    }

    /**
     * Platform-specific file separator.
     */
    extern const char file_separator;

    /**
     * Get the path of given asset.
     * The usual output is <path to data dir><file_separator><file>.
     * However, the output path might be absolute or not, depending on the platform.
     * @param file path relative to data/ directory
     * @return path relative to application's binary directory, or absolute path to the given file
     */
    std::string path(const std::string &file);

    /**
     * Get the path of given asset.
     * The usual output is <path to data dir><file_separator><type><file_separator><file>.
     * However, the output path might be absolute or not, depending on the platform.
     * @param file path relative to data/<type>/ directory
     * @return path relative to application's binary directory, or absolute path to the given file
     */
    template<const char *type>
    std::string path(const std::string &file) {
        std::string dir(type);
        dir += file_separator;
        return path(dir + file);
    }

    /**
     * Get the list of files in given directory (non-recursive)
     * @param path directory to list
     * @return vector of filenames inside given dir
     */
    std::vector<std::string> list(const char *path);
}

#endif //C003_FILES_H
