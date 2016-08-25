/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_CONFIG_H
#define C003_CONFIG_H

#include <kaguya/kaguya.hpp>
#include <mutex>

#include "util/file.h"

class Config {
public:
    Config(const std::string &fileName);
    std::string stringValue(const std::string &key, const std::string &defValue) const;
    int intValue(const std::string &key, int defValue) const;

private:
    mutable std::mutex m_mutex;
    mutable kaguya::State m_config;
};

#endif //C003_CONFIG_H
