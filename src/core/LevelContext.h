//
// Created by dar on 4/29/16.
//

#ifndef C003_LEVELCONTEXT_H
#define C003_LEVELCONTEXT_H

#include <string>
#include <kaguya/kaguya.hpp>

class LevelContext {

public:
    LevelContext(const std::string &name);

private:
    const int id;
    const std::string name;
    const kaguya::State state;

    static int maxId;
    static int getNextMaxId();
};

#endif //C003_LEVELCONTEXT_H
