//
// Created by dar on 4/29/16.
//

#include "LevelData.h"

void LevelData::addLevel(const std::string &name) {
    this->levels.push_back(name);
}

LevelData::type LevelData::getLevels() const {
    return this->levels;
}

