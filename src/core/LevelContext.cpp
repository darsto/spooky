//
// Created by dar on 4/29/16.
//

#include "LevelContext.h"

int LevelContext::maxId = 0;

int LevelContext::getNextMaxId() {
    return ++maxId;
}

LevelContext::LevelContext(const std::string &name) : id(getNextMaxId()), name(name) {

}