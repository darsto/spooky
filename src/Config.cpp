/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Config.h"

Config::Config(const std::string &fileName) {
    m_config.dofile(util::file::path<util::file::type::conf>(fileName));
}

std::string Config::stringValue(const std::string &key, const std::string &defValue) const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);

    m_config("tmp = " + key);
    return m_config["tmp"];
}

int Config::intValue(const std::string &key, int defValue) const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);

    m_config("tmp = " + key);
    return m_config["tmp"];
}
